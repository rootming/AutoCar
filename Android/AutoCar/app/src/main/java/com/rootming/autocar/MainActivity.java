package com.rootming.autocar;

import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.InputFilter;
import android.util.Log;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Toast;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;


public class MainActivity extends AppCompatActivity {

    private static final String tag="logOut";
    Button btnConnect;
    Button btnSend;
    Button btnChangeActivity;
    EditText inputIP;
    EditText inputPort;
    EditText inputCMD;
    EditText outputText;
    CheckBox autoConnect;
    MyThread connectServer;
    SendThread sender;
    Socket socket;
    String data;
    boolean connected;

    private final Handler msgHandler = new Handler(){
        public void handleMessage(Message msg) {
            switch (msg.arg1) {
                case 0:
                    Toast.makeText(getApplicationContext(), "successful", Toast.LENGTH_SHORT).show();
                    btnConnect.setText("disconnect");
                    inputIP.setEnabled(false);
                    inputPort.setEnabled(false);
                    btnSend.setEnabled(true);
                    connected = true;
                    break;
                case 1:
                    Toast.makeText(getApplicationContext(), "fail", Toast.LENGTH_SHORT).show();
                    btnConnect.setText("connect");
                    inputIP.setEnabled(true);
                    inputPort.setEnabled(true);
                    btnSend.setEnabled(false);
                    connected = false;
                    break;
                case 2:
                    outputText.append(data);
                    break;
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        inputIP = (EditText)findViewById(R.id.inputIP);
        inputPort = (EditText)findViewById(R.id.inputPort);
        inputCMD = (EditText)findViewById(R.id.inputCMD);
        outputText = (EditText)findViewById(R.id.outputText);
        btnConnect = (Button)findViewById(R.id.btnConnect);
        btnSend = (Button)findViewById(R.id.btnSend);
        btnChangeActivity = (Button)findViewById(R.id.btnChangeActivity);
        autoConnect = (CheckBox)findViewById(R.id.autoConnect);
        inputIP.setFilters(new InputFilter[]{new InputFilter.LengthFilter(15)});
        connected = false;
        btnSend.setEnabled(false);

        btnConnect.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v){
                if(!connected) {
                    connectServer = new MyThread();
                    connectServer.start();
                }
                else{
                    try {
                        socket.close();
                        btnConnect.setText("connect");
                        inputIP.setEnabled(true);
                        inputPort.setEnabled(true);
                        btnSend.setEnabled(false);
                        connected = false;
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        btnSend.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                sender = new SendThread();
                sender.start();
            }
        });

        btnChangeActivity.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setClassName(getApplicationContext(), "com.rootming.autocar.ControlActivity");
                startActivity(intent);
            }
        });

        autoConnect.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                if(autoConnect.isChecked()){
                    inputIP.setEnabled(false);
                    inputPort.setEnabled(false);
                    btnConnect.setEnabled(false);
//                    TODO:
                }
                else{
                    inputIP.setEnabled(true);
                    inputPort.setEnabled(true);
                    btnConnect.setEnabled(true);

                }
            }
        });
    }
    public class MyThread extends Thread{
            public void run(){
                socket = new Socket();
                try {
                    socket.connect(new InetSocketAddress(inputIP.getText().toString(), Integer.parseInt(inputPort.getText().toString())), 5000);
                    Message msg = msgHandler.obtainMessage();
                    msg.arg1 = 0;
                    msgHandler.sendMessage(msg);
                }
                catch(IOException e){
                    Message msg = msgHandler.obtainMessage();
                    msg.arg1 = 1;
                    msgHandler.sendMessage(msg);
                    e.printStackTrace();
                }
            }
    }
    public class SendThread extends Thread{
            public void run(){
                    DataOutputStream out;
                    DataInputStream in;

                    Log.d(tag, "Press");
                    try {
                        out = new DataOutputStream(socket.getOutputStream());
                        in = new DataInputStream(socket.getInputStream());
                        out.write(inputCMD.getText().toString().getBytes());;
                        out.flush();
                        byte buffer [] = new byte[1024];
                        int length;
                        while((length = in.read(buffer)) != -1){
                            data = new String(buffer, 0, length);
                            Message msg = msgHandler.obtainMessage();
                            msg.arg1 = 2;
                            msgHandler.sendMessage(msg);
                        }
                    }
                    catch(IOException e) {
                        e.printStackTrace();
                    }
                }
            }
}
