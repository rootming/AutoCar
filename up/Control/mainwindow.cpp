#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Serial Tool");
    this->m = new QWidget(this);

    this->rxLayout = new QGridLayout;
    this->setLayout = new QGridLayout;
    this->top = new QGridLayout(m);
    this->control = new QGridLayout;

    this->send = new QLabel(QWidget::tr("Send:"), m);
    this->recv = new QLabel(QWidget::tr("Receive:"), m);

    this->choosePort = new QLabel(QWidget::tr("Choose Port:"), m);
    this->chooseSpeed = new QLabel(QWidget::tr("Choose Speed:"),m);
    this->dataText = new QTextEdit(m);
    this->sendText = new QLineEdit(m);
    this->sendButton = new QPushButton(QWidget::tr("Send"), m);
    this->clearButton = new QPushButton(QWidget::tr("Clear"), m);
    this->connectButton = new QPushButton(QWidget::tr("Connect"), m);
    this->porstList = new QComboBox;
    this->speedList = new QComboBox;
    this->controlPanel = new QGroupBox(QWidget::tr("Control Panel"), m);
    this->controlButton = new ControlPushButton[COMMAND_COUNT]();

    commandStr = new QString[COMMAND_COUNT];

    commandStr[0] = "GL";
    commandStr[1] = "Forward";
    commandStr[2] = "GR";
    commandStr[3] = "LEFT";
    commandStr[4] = "Brake";
    commandStr[5] = "RIGHT";
    commandStr[6] = "BL";
    commandStr[7] = "Back";
    commandStr[8] = "BR";
    for(uint8_t i = 0 ; i < COMMAND_COUNT; i++)
        controlButton[i].setText(commandStr[i]);


    for(int i = 2, k = 0; i >= 0; i--)
        for(int j = 0 ; j < 3; j++)
            controlButton[k++].setShortcut(Qt::Key_1 + 3 * i + j);

    rxLayout->addWidget(recv, 0, 0, 1, 1);
    rxLayout->addWidget(dataText, 1, 0, 1, 2);
    rxLayout->addWidget(send, 2, 0, 1, 1);
    rxLayout->addWidget(sendText, 3, 0, 1, 2);
    rxLayout->addWidget(sendButton, 4, 0, 1, 1);
    rxLayout->addWidget(clearButton, 4, 1, 1, 1);

    setLayout->addWidget(choosePort, 0, 0, 1, 1);
    setLayout->addWidget(porstList, 0, 1, 1, 1);
    setLayout->addWidget(chooseSpeed, 1, 0, 1, 1);
    setLayout->addWidget(speedList, 1, 1, 1, 1);
    setLayout->addWidget(connectButton, 2, 0, 1, 2);
    setLayout->addWidget(controlPanel, 3, 0, 1, 2);

    controlPanel->setLayout(control);
    for(int y = 0, i = 0 ; y < 3; y++){
        for(int x = 0 ; x < 3; x++){
            control->addWidget(&controlButton[i++], y, x, 1, 1);
        }
    }
    //control->setEnabled(false);

    top->addLayout(rxLayout, 0, 0);
    top->addLayout(setLayout, 0, 2, Qt::AlignTop);

    setCentralWidget(m);

    locked = false;
    connected = false;
    Bitspeed = "4800,9600,14400,19200,38400,57600,115200";  //定义速率
    BitSpeedList = Bitspeed.split(",");
    ComList << "a" << "b" << "c" << "d" << "e" << "f" << "g";
    autoScanTimer = new QTimer(this);
    autoScanTimer->setInterval(1000);
    autoScanTimer->start();
    this->sendButton->setDisabled(true);


    QObject::connect(clearButton, SIGNAL(clicked()), sendText, SLOT(clear()));
    connect(&serial, SIGNAL(readyRead()), this, SLOT(serialRead()));
    connect(autoScanTimer, SIGNAL(timeout()), this, SLOT(rescanSeialPort()));
    connect(connectButton, SIGNAL(clicked()), this, SLOT(connectSerial()));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendData()));

    for(int i = 0 ; i < COMMAND_COUNT; i++)
        connect(&controlButton[i], SIGNAL(myClicked(ControlPushButton *)), this, SLOT(commandSender(ControlPushButton *)));

    initSeialPort();
    commandInit();


}

MainWindow::~MainWindow()
{

}

void MainWindow::initSeialPort()
{


    this->speedList->addItems(BitSpeedList);
    this->speedList->setCurrentIndex(1);   //默认波特率

    QList<QSerialPortInfo>  infos = QSerialPortInfo::availablePorts();
    portsCount = infos.count();
    if(infos.isEmpty()){
        this->porstList->addItem("None Device");
        return;
    }
    this->porstList->addItem("Choose Port");
    foreach (QSerialPortInfo info, infos) {
        this->porstList->addItem(info.portName()+"("+info.description()+")");
    }
}

void MainWindow::resetState()
{
    qDebug()<<"Function has been called";
    locked = false;
    connected = false;
    this->porstList->setEnabled(true);
    this->speedList->setEnabled(true);
    this->sendButton->setDisabled(true);
    //this->control->setEnabled(false);
    this->connectButton->setText(QWidget::tr("Connect"));
    //设备意外断开，释放按钮
}

void MainWindow::rescanSeialPort()
{
    if(locked)
        return;
    QList<QSerialPortInfo>  infos = QSerialPortInfo::availablePorts();
    if(portsCount == infos.count())
        return;
    portsCount = infos.count();
    this->porstList->clear();
    if(infos.isEmpty())
    {
        this->porstList->addItem("None Device");
        return;
    }
    this->porstList->addItem("Choose Port");
    foreach (QSerialPortInfo info, infos) {
        this->porstList->addItem(info.portName()+"("+info.description()+")");
    }
}

void MainWindow::serialRead()
{
    QByteArray data;
    data = serial.readAll();
    dataText->setTextColor(QColor(0, 200, 100));
    this->dataText->insertPlainText(data);
    this->dataText->moveCursor(QTextCursor::End);
    this->dataText->insertPlainText("\r\n");
}

void MainWindow::connectSerial()
{
//    if(!ui->checkBox->isChecked()){
//        qDebug() << "Disconnect signal";
//        disconnect(&serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(resetState()));
//        serial.close();
//        resetState();
//    }
//    else{
        //ui->State->setText("尝试连接");
    if(!connected){
        QString arg1 = this->porstList->currentText();
        QString arg2 = arg1.left(arg1.indexOf("("));
        QSerialPortInfo info;
        QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();

        int i = 0;
        foreach (info, infos) {
            if(info.portName() == arg2) break;
            i++;
        }

        qDebug() << i << " " <<infos.size();
        if(i != infos.size()){
            //ui->State->setText("已连接,波特率:"+ui->BitSpeed->currentText());
            serial.close();
            serial.setBaudRate(this->speedList->currentText().toInt());
            serial.setPort(info);
            serial.open(QIODevice::ReadWrite);
            locked = true;
            connected = true;
            this->porstList->setEnabled(false);
            this->speedList->setEnabled(false);
            this->connectButton->setText(QWidget::tr("Disconnect"));
            this->sendButton->setEnabled(true);
            this->control->setEnabled(true);
            qDebug()<<"Connect signal";
            connect(&serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(resetState()));

        }
        else{
            qDebug()<<"Disconnect signal";
            disconnect(&serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(resetState()));
            serial.close();
            resetState();
        }
    }
    else{
        qDebug()<<"Disconnect signal";
        disconnect(&serial, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(resetState()));
        serial.close();
        resetState();
    }
}

void MainWindow::sendData()
{
    dataText->setTextColor(QColor(255, 0, 0));
    dataText->setAlignment(Qt::AlignRight);
    dataText->insertPlainText(this->sendText->text() + "\r\n");
    serial.write(this->sendText->text().toLatin1());
    dataText->setAlignment(Qt::AlignLeft);
}

void MainWindow::commandInit()
{
    for(uint8_t i = 0; i < COMMAND_COUNT; i++){
        commandList[commandStr[i]].start = _PKGSTART;
        commandList[commandStr[i]].command = i;
        commandList[commandStr[i]].value = '\0';
        commandList[commandStr[i]].end = _PKGEND;
    }
}

void MainWindow::commandSender(ControlPushButton *sender)
{
    //serial.writeData((char *)&commandList[sender.text()], sizeof(Package));
    dataText->setTextColor(QColor(255, 0, 0));
    dataText->setAlignment(Qt::AlignRight);
    this->dataText->insertPlainText((char *)&commandList[sender->text()].start);
    this->dataText->insertPlainText((char *)&commandList[sender->text()].command);
    this->dataText->insertPlainText((char *)&commandList[sender->text()].value);
    this->dataText->insertPlainText((char *)&commandList[sender->text()].end);
    this->dataText->insertPlainText("\n");
    this->dataText->moveCursor(QTextCursor::End);
    dataText->setAlignment(Qt::AlignLeft);

    serial.write((char *)&commandList[sender->text()].start);
    serial.write((char *)&commandList[sender->text()].command);
    serial.write((char *)&commandList[sender->text()].value);
    serial.write((char *)&commandList[sender->text()].end);

}



