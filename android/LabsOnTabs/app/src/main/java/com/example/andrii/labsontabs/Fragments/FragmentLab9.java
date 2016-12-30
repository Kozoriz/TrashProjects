package com.example.andrii.labsontabs.Fragments;

import android.content.Intent;
import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.andrii.labsontabs.AboutActivity;
import com.example.andrii.labsontabs.AdditionalOneActivity;
import com.example.andrii.labsontabs.R;

/**
 * Created by andrii on 17.12.16.
 */


/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentLab9 extends Fragment {
    public FragmentLab9() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View rootView = inflater.inflate(R.layout.lab9_fragment_tabs, container, false);
        Intent intent = new Intent(getActivity(), AdditionalOneActivity.class);
        startActivity(intent);
        return rootView;
    }
}