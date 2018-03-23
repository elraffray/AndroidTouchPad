package com.example.gryfe.touchpad;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import com.example.gryfe.touchpad.Network.SocketManager;

import java.net.Socket;

public class ConnectActivity extends AppCompatActivity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_connect);
    }


    @Override
    protected void onStop() {
        super.onStop();
        SocketManager.getInstance().disconnect();
    }

    public void connect(View v) {
        String ipaddr = ((EditText)findViewById(R.id.editIP)).getText().toString();
        int port = Integer.parseInt(((EditText)findViewById(R.id.editPort)).getText().toString());
        SocketManager.getInstance().init(ipaddr, port);
        SocketManager.getInstance().connect();
    }

    public void sendMsg(View v) {
        SocketManager.getInstance().send("yolo");
    }
}
