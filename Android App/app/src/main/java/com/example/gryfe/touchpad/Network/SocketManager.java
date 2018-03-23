package com.example.gryfe.touchpad.Network;

import android.util.Log;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.ByteBuffer;

/**
 * Created by gryfe on 23/03/2018.
 */



public class SocketManager {

    private static class SocketManagerHolder {
        private static final SocketManager instance = new SocketManager();
    }

    public static SocketManager getInstance() {
        return SocketManager.getInstance();
    }

    private SocketManager() {}

    private Socket socket;
    private DataOutputStream dos;
    private String serverIP;
    private int serverPort;

    //private SendRunnable sendRunnable;
    //private Thread sendThread;
    //byte[] dataToSend;

    public void init(String addr, int port) {
        serverIP = addr;
        serverPort = port;
    }

    public void connect() {
        try {
            socket = new Socket(serverIP, serverPort);
            dos = new DataOutputStream(socket.getOutputStream());
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    public void disconnect() {
        try {
            dos.close();
            socket.close();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    public void send(String msg) {
        try {
            dos.writeUTF(msg);
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    /*public void connect() {
        new Thread(new ConnectRunnable()).start();
    }

    public void disconnect() {
        stopSending();
        try {
            socket.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

    public boolean isConnected() {
        return socket != null && socket.isConnected() && !socket.isClosed();
    }

    public void sendCommand(String data) {
        if (isConnected()) {
            startSending();
            sendRunnable.sendCommand(data.getBytes());
        }
    }

    private void startSending() {
        sendRunnable = new SendRunnable(socket);
        sendThread = new Thread(sendRunnable);
        sendThread.start();
    }

    private void stopSending() {
        if (sendThread != null)
            sendThread.interrupt();
    }

    public class ConnectRunnable implements Runnable {

        public void run() {
            try {
                InetAddress serverAddr = InetAddress.getByName(serverIP);
                //Create a new instance of Socket
                socket = new Socket();
                //Start connecting to the server with 5000ms timeout
                //This will block the thread until a connection is established
                socket.connect(new InetSocketAddress(serverAddr, serverPort), 5000);

                Log.d("SOCKET", "Connected!");

            } catch (Exception e) {
                //Catch the exception that socket.connect might throw
                e.printStackTrace();
            }
            Log.d("SOCKET", "Connection thread stopped");
        }
    }

    public class SendRunnable implements Runnable {
        byte[] data;
        private OutputStream out;
        private boolean hasMessage = false;

        public SendRunnable(Socket server) {
            try {
                this.out = server.getOutputStream();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }


        public void sendCommand(byte[] bytes) {
            this.data = bytes;
            this.hasMessage = true;
        }

        @Override
        public void run() {
            Log.d("SOCKET", "Sending started");
            if (this.hasMessage) {
                try {
                    //Send the length of the data to be sent
                    this.out.write(ByteBuffer.allocate(4).putInt(data.length).array());
                    //Send the data
                    this.out.write(data, 0, data.length);
                    //Flush the stream to be sure all bytes has been written out
                    this.out.flush();
                } catch (IOException e) {
                    e.printStackTrace();
                }

                this.hasMessage = false;
                this.data =  null;
                Log.d("SOCKET", "Command has been sent!");
            }

        }
    }*/


}
