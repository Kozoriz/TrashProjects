package com.example.andrii.labsontabs.Fragments;

import android.content.Intent;
import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.example.andrii.labsontabs.AboutActivity;
import com.example.andrii.labsontabs.R;

/**
 * Created by andrii on 17.12.16.
 */


/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentLab7 extends Fragment {
    public View rootView;
    public FragmentLab7() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.lab7_fragment_tabs, container, false);

        Button about_button = (Button) rootView.findViewById(R.id.about_button);
        about_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getActivity(), AboutActivity.class);
                startActivity(intent);
            }
        });

        return rootView;
    }
}