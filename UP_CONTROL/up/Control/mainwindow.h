#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QGroupBox>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QMap>

#include "def.h"


class ControlPushButton: public QPushButton
{
    Q_OBJECT
public:
    ControlPushButton()
    {
        qDebug() << "Connected Contorl Button Signal.";
        connect(this, SIGNAL(clicked()), this,  SLOT(myClickEmit()));
    }

signals:
    void myClicked(ControlPushButton *);


private slots:
    void myClickEmit()
    {
        emit myClicked(this);
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QGridLayout *rxLayout, *setLayout, *top, *control;
    QWidget *m;
    QLabel *send;
    QLabel *recv;
    QLabel *choosePort;
    QLabel *chooseSpeed;
    QTextEdit *dataText;
    QLineEdit *sendText;
    QPushButton *sendButton;
    QPushButton *clearButton;
    QPushButton *connectButton;
    QComboBox *porstList;
    QComboBox *speedList;
    QGroupBox *controlPanel;
    ControlPushButton *controlButton;

    QSerialPort serial;
    QString Bitspeed;
    QTimer *autoScanTimer;
    QStringList  BitSpeedList ;
    QStringList  ComList ;
    int portsCount;
    bool locked;
    bool connected;

    QString *commandStr;
    QMap<QString, Package> commandList;

    void initSeialPort();
    void connectSeialPort();
    void commandInit();

private slots:
    void serialRead();
    void rescanSeialPort();
    void resetState();
    void connectSerial();
    void sendData();
    void commandSender(ControlPushButton *sender);
};



#endif // MAINWINDOW_H
