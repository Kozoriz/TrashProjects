package com.example.andrii.labsontabs.Fragments;

import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.content.pm.ApplicationInfo;
import android.content.res.Configuration;
import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.example.andrii.labsontabs.R;

import java.io.Console;

/**
 * Created by andrii on 17.12.16.
 */


/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentLab6 extends Fragment {
    public View rootView;
    public TextView text;
    public String landscape = "landscape";
    public String portrait = "portrait";
    public FragmentLab6() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.lab6_fragment_tabs, container, false);

        Button landscape_button = (Button) rootView.findViewById(R.id.landscape_button);
        Button portrait_button = (Button) rootView.findViewById(R.id.portrait_button);

        text = (TextView) rootView.findViewById(R.id.crown_count_text);

        if (getActivity().getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
            text.setText(portrait);
        } else {
            text.setText(landscape);
        }

        landscape_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                getActivity().setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
            }
        });

        portrait_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                getActivity().setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
            }
        });
        return rootView;
    }
}