package com.fengbiaoedu.cy.myapplication;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {
    static {

        System.loadLibrary("native");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        String s=GetStrFromJNI();
        Log.i(this.getClass().getName(),s);

    }

    public native String GetStrFromJNI();
}
