package com.example.andrii.labsontabs.Fragments;

import android.content.Context;
import android.os.Bundle;
import android.app.Fragment;
import android.os.Handler;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.example.andrii.labsontabs.R;

/**
 * Created by andrii on 17.12.16.
 */


/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentLab8 extends Fragment {
    public View rootView;
    public Context appContext;
    private Handler handler;

    public FragmentLab8() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.lab8_fragment_tabs, container, false);
        appContext = rootView.getContext().getApplicationContext();
        handler = new Handler();
        mainProcessing();

        return rootView;
    }

    private void runInThread() {
        Thread thread = new Thread(null, threadDelegate, "Background");
        thread.start();
    }

    private Runnable threadDelegate = new Runnable() {
        public void run() {
            Context context = rootView.getContext().getApplicationContext();
            String msg = "To open mobile development!";
            int duration = Toast.LENGTH_SHORT;
            Toast.makeText(context, msg, duration).show();
        }
    };

    private void mainProcessing() {
        Thread thread = new Thread(null, doBackgroundThreadProcessing,
                "Background");
        thread.start();
    }

    private Runnable doBackgroundThreadProcessing = new Runnable() {
        public void run() {
            backgroundThreadProcessing();
        }
    };

    private void backgroundThreadProcessing() {
        handler.post(doUpdateGUI);
    }

    // Объект Runnable, который вызывает метод из потока GUI
    private Runnable doUpdateGUI = new Runnable() {
        public void run() {
            Toast toast3 = Toast.makeText(rootView.getContext().getApplicationContext(),
                    "Yo, snigger!!!", Toast.LENGTH_LONG);
            toast3.setGravity(Gravity.CENTER, 0, 0);
            LinearLayout toastContainer = (LinearLayout) toast3.getView();
            ImageView catImageView = new ImageView(rootView.getContext().getApplicationContext());
            catImageView.setImageResource(R.drawable.brutal_cat);
            toastContainer.addView(catImageView, 0);
            toast3.show();
        }
    };
}