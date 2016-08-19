package com.rootming.autocar;

import android.content.pm.ActivityInfo;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.WindowManager;

import io.github.controlwear.virtual.joystick.android.*;

public class ControlActivity extends AppCompatActivity {

    private JoystickView jyvLeft, jyvRight;


    private final int scanSpeed = 17;
    private final int speedLimit = 255;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        //set screen land
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,  WindowManager.LayoutParams.FLAG_FULLSCREEN);
        //set fullscreeen
        getSupportActionBar().hide();
        //set no title
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);
        init();



    }

    private void init() {
        jyvLeft = (JoystickView)findViewById(R.id.jyvLeft);
        jyvRight = (JoystickView)findViewById(R.id.jyvRight);

        jyvLeft.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                MotorSpeed test = getMotorSpeed(angle, strength);
                System.out.println("@LEFT, Angle is:" + angle + ", Strength is:" + strength);
                System.out.println("@LEFT Motor:" + test.leftMotorSpeed + ", @RIGHT Motor:" + test.rightMotorSpeed);
            }
        }, scanSpeed);

        jyvRight.setOnMoveListener(new JoystickView.OnMoveListener() {
            @Override
            public void onMove(int angle, int strength) {
                System.out.println("@RIGHT, Angle is:" + angle + ", Strength is:" + strength);
            }
        }, scanSpeed);

    }

    class MotorSpeed{
        int leftMotorSpeed = 0;
        int rightMotorSpeed = 0;
//        MotorSpeed(int left, int right){
//            leftMotorSpeed = left;
//            rightMotorSpeed = right;
//        }
//        MotorSpeed(){
//
//        }
    }

    private MotorSpeed getMotorSpeed(int angle, int strength){
        MotorSpeed tmp = new MotorSpeed();
        double left, right;
        double deg;
        double speedPre  = strength / 100.0 * speedLimit;
        if(angle < 180) {
            deg = Math.toRadians(angle / 2);
            left =  Math.cos(deg);
            right = Math.sin(deg);
            tmp.leftMotorSpeed = (int)(left * speedPre);
            tmp.rightMotorSpeed = (int)(right * speedPre);
        }
        else{
            deg = Math.toRadians(angle / 2 - 90);
            left =  Math.sin(deg);
            right = Math.cos(deg);
            tmp.leftMotorSpeed = -(int)(left * speedPre);
            tmp.rightMotorSpeed = -(int)(right * speedPre);
        }
//        System.out.println("Left:" + left + ", Right:" + right);
        return tmp;
    }


}
