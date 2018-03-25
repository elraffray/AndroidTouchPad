package com.example.gryfe.touchpad;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import com.example.gryfe.touchpad.Network.SocketManager;

import java.net.Socket;
import java.util.concurrent.ExecutionException;

public class ConnectActivity extends AppCompatActivity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connect);
    }


    @Override
    protected void onStop() {
        super.onStop();
        //SocketManager.getInstance().disconnect();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        SocketManager.getInstance().disconnect();
    }

    public void connect(View v) {
        String ipaddr = ((EditText)findViewById(R.id.editIP)).getText().toString();
        int port = Integer.parseInt(((EditText)findViewById(R.id.editPort)).getText().toString());
        SocketManager.getInstance().init(ipaddr, port);

        if (SocketManager.getInstance().connect()) Log.d("NETWORK", "Connected");
        else Log.d("NETWORK", "Failed to connect");

        Intent myIntent = new Intent(this, TouchPadActivity.class);
        //myIntent.putExtra("key", value); //Optional parameters
        this.startActivity(myIntent);
    }

    public void sendMsg(View v) {
        SocketManager.getInstance().send("yolo");
    }
}
