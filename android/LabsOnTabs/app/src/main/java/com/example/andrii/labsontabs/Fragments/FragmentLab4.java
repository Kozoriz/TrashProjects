package com.example.andrii.labsontabs.Fragments;

import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.example.andrii.labsontabs.R;

import org.w3c.dom.Text;

/**
 * Created by andrii on 17.12.16.
 */


/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentLab4 extends Fragment {
    public View rootView;
    public TextView text_;

    public FragmentLab4() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.lab4_fragment_tabs, container, false);

        text_ = (TextView) rootView.findViewById(R.id.textView2);

        Button red_button = (Button) rootView.findViewById(R.id.red_button);
        Button green_button = (Button) rootView.findViewById(R.id.green_button);
        Button yellow_button = (Button) rootView.findViewById(R.id.yellow_button);

        red_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                text_.setText(R.string.red);
                rootView.setBackgroundColor(getResources().getColor(R.color.colorRed));
            }
        });

        green_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                text_.setText(R.string.green);
                rootView.setBackgroundColor(getResources().getColor(R.color.colorGreen));
            }
        });

        yellow_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                text_.setText(R.string.yellow);
                rootView.setBackgroundColor(getResources().getColor(R.color.colorYellow));
            }
        });

        return rootView;
    }
}