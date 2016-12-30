package com.example.andrii.labsontabs.Fragments;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import com.example.andrii.labsontabs.AboutActivity;
import com.example.andrii.labsontabs.ChooseActivity;
import com.example.andrii.labsontabs.R;
import com.example.andrii.labsontabs.Tabs;

/**
 * Created by andrii on 17.12.16.
 */


/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentLab5 extends Fragment {
    public Integer SECOND_ACTIVITY = 0;
    public View rootView;
    public FragmentLab5() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.lab5_fragment_tabs, container, false);

        Button about_button = (Button) rootView.findViewById(R.id.about_button);
        Button choose_button = (Button) rootView.findViewById(R.id.choose_button);

        about_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getActivity(), AboutActivity.class);
                startActivity(intent);
            }
        });
        choose_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getActivity(), ChooseActivity.class);
                startActivityForResult(intent, SECOND_ACTIVITY);
            }
        });

        return rootView;
    }
    @Override
    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        TextView infoTextView = (TextView) rootView.findViewById(R.id.textView4);

        if (requestCode == SECOND_ACTIVITY) {
            if (resultCode == -1) {
                String result = data.getStringExtra(ChooseActivity.choosen_option);
                infoTextView.setText("Choosen : " + result);
            }else {
                infoTextView.setText(""); // стираем текст
            }
        }
    }
}