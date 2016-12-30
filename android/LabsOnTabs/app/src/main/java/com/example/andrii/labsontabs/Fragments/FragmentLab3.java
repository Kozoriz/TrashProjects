package com.example.andrii.labsontabs.Fragments;

import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.example.andrii.labsontabs.R;

/**
 * Created by andrii on 17.12.16.
 */


/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentLab3 extends Fragment {
    public View rootView;
    public FragmentLab3() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.lab3_fragment_tabs, container, false);

        Button hello_button = (Button) rootView.findViewById(R.id.hello_button);
        hello_button.setOnClickListener(new View.OnClickListener() {
            private boolean clicked_ = false;
            @Override
            public void onClick(View view) {
                clicked_ = !clicked_;
                TextView label = (TextView) rootView.findViewById(R.id.hello_text);
                String text = (clicked_) ? "Hello, mthrfckr!" : "";
                label.setText(text);
            }
        });

        Button crown_count_button = (Button) rootView.findViewById(R.id.crowns_count_button);
        crown_count_button.setOnClickListener(new View.OnClickListener() {
            private Integer crown_count = 0;
            @Override
            public void onClick(View view) {
                ++crown_count;
                TextView label = (TextView) rootView.findViewById(R.id.crown_count_text);
                label.setText("Crowns count : " + crown_count.toString());
            }
        });

        return rootView;
    }
}