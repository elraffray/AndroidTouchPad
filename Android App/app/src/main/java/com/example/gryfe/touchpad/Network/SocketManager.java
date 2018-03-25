package com.example.gryfe.touchpad.Network;

import android.os.AsyncTask;
import android.util.Log;

import java.io.DataOutputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.concurrent.ExecutionException;

/**
 * Created by gryfe on 23/03/2018.
 */



public class SocketManager {

    private Socket socket;
    private OutputStream outputStream;
    private String serverIP;
    private int serverPort;


    private SocketManager() {}
    private static class SocketManagerHolder {
        private static final SocketManager instance = new SocketManager();
    }
    public static SocketManager getInstance() {
        return SocketManagerHolder.instance;
    }


    private class ConnectTask extends AsyncTask<Void, Void, Boolean> {
        @Override
        protected Boolean doInBackground(Void... voids) {
            try {
                socket = new Socket();
                socket.connect(new InetSocketAddress(serverIP, serverPort), 5000);
                outputStream = socket.getOutputStream();
            } catch(Exception e) {
                return false;
            }
            return true;
        }
    }

    private class SendTask extends AsyncTask<String, Void, Boolean> {
        @Override
        protected Boolean doInBackground(String... strings) {

            try {
                outputStream.write(strings[0].getBytes());
                Log.d("NETWORK", "Message " + strings[0] + " sent");
            } catch(Exception e) {
                e.printStackTrace();
                return false;
            }
            return true;
        }
    }

    public boolean connect() {
        try {
            return new ConnectTask().execute().get();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
        return false;
    }


    public boolean send(String data) {
        try {
            return new SendTask().execute(data).get();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
        return false;
    }



    public void init(String addr, int port) {
        serverIP = addr;
        serverPort = port;
    }


    public void disconnect() {
        try {
            if (outputStream != null) outputStream.close();
            if (socket != null) socket.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }


}
