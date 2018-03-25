package com.example.gryfe.touchpad;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.util.Pair;
import android.view.MotionEvent;
import android.widget.TextView;

import com.example.gryfe.touchpad.Network.SocketManager;

import java.lang.System;

/**
 * Created by gryfe on 23/03/2018.
 */




public class TouchPadActivity extends AppCompatActivity {

    private final int CLICK_TIMEOUT_MS = 150;
    private final int SCROLL_COOLDOWN_MS = 40;



    private TextView debug1;
    private TextView debug2;

    private int nbFingers = 0;

    private long lastFingerDown;
    private long lastScrolled;

    private boolean rightClicked = false;
    private boolean middleClicked = false;

    private Pair<Integer, Integer> lastTouchCoord = new Pair<>(0,0);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_touchpad);


        debug1 = (TextView)findViewById(R.id.debug1);
        debug2 = (TextView)findViewById(R.id.debug2);
    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {

        int action = event.getAction() & MotionEvent.ACTION_MASK;
        //int pointerIndex = (event.getAction() & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
        //int fingerId = event.getPointerId(pointerIndex);


        switch (action) {
            case MotionEvent.ACTION_DOWN:
                nbFingers++;
                lastFingerDown = System.currentTimeMillis();
                lastTouchCoord = new Pair<>(Math.round(event.getX()), Math.round(event.getY()));

                Log.d("TOUCHEVENT", "action_down " + nbFingers);

                break;
            case MotionEvent.ACTION_POINTER_DOWN:
                nbFingers++;
                //touchScreenStartPtArr[fingerId].x = event.getX(pointerIndex);
                //touchScreenStartPtArr[fingerId].y = event.getY(pointerIndex);
                Log.d("TOUCHEVENT", "action_pointer_down " + nbFingers);

                break;
            case MotionEvent.ACTION_UP:
                nbFingers--;
                Log.d("TOUCHEVENT", "action_up " + nbFingers);

                if (!rightClicked && !middleClicked)
                    if (System.currentTimeMillis() - lastFingerDown < CLICK_TIMEOUT_MS) {
                        Log.d("TOUCHEVENT", "left click " + nbFingers);
                        SocketManager.getInstance().send("L");
                    }
                rightClicked = false;
                middleClicked = false;

                break;
            case MotionEvent.ACTION_POINTER_UP:
                if (System.currentTimeMillis() - lastFingerDown < CLICK_TIMEOUT_MS) {
                    Log.d("TOUCHEVENT", "action_pointer_up " + nbFingers);
                    if (nbFingers == 2 && !middleClicked) {
                        Log.d("TOUCHEVENT", "right click " + nbFingers);
                        rightClicked = true;
                        SocketManager.getInstance().send("R");

                    } else if (nbFingers == 3) {
                        Log.d("TOUCHEVENT", "middle click " + nbFingers);
                        middleClicked = true;
                        SocketManager.getInstance().send("M");
                    }
                }

                nbFingers--;
                Log.d("TOUCHEVENT", "action_pointer_up " + nbFingers);
                break;
            case MotionEvent.ACTION_CANCEL:
                //touchScreenStopPtArr[fingerId].x = event.getX(pointerIndex);
                //touchScreenStopPtArr[fingerId].y  = event.getX(pointerIndex);
                break;
            case MotionEvent.ACTION_MOVE:
                Log.d("TOUCHEVENT", "action_move " + nbFingers);
                if (nbFingers == 2 && System.currentTimeMillis() - lastFingerDown > CLICK_TIMEOUT_MS) {

                    if (System.currentTimeMillis() - lastScrolled > SCROLL_COOLDOWN_MS) {

                        if (event.getY() > lastTouchCoord.second) {
                            Log.d("TOUCHEVENT", "scrolling down" + nbFingers);
                            SocketManager.getInstance().send("D");
                        } else {
                            Log.d("TOUCHEVENT", "scrolling up" + nbFingers);
                            SocketManager.getInstance().send("U");
                        }
                        lastScrolled = System.currentTimeMillis();
                    }

                } else if (nbFingers == 1 && System.currentTimeMillis() - lastFingerDown > CLICK_TIMEOUT_MS) {
                    Log.d("TOUCHEVENT", "moving " + nbFingers);
                    float x = event.getRawX() - lastTouchCoord.first;
                    float y = event.getRawY() - lastTouchCoord.second;
                    SocketManager.getInstance().send("W " + Math.round(x) + " " + Math.round(y));

                    lastTouchCoord = new Pair<> (Math.round(event.getRawX()),  Math.round(event.getRawY()));
                }
                //int pointerCount = event.getPointerCount();
                //for (int i = 0; i < pointerCount; i++) {
                //    touchScreenCurrPtArr[fingerId].x = event.getX(i);
                //    touchScreenCurrPtArr[fingerId].y = event.getY(i);
                //}
                break;
        }

        debug1.setText("Finger Count: " + nbFingers);

        return true;



        /*if (this.mDetector.onTouchEvent(event)) {
            return true;
        }
        return super.onTouchEvent(event);*/


    }

}
