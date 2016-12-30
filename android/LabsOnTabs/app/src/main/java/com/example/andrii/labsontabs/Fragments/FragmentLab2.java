package com.example.andrii.labsontabs.Fragments;

import android.os.Bundle;
import android.app.Fragment;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

import com.example.andrii.labsontabs.R;

/**
 * Created by andrii on 17.12.16.
 */


/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentLab2 extends Fragment {
    public View rootView;
    public EditText editable_text_field;
    public FragmentLab2() {
    }
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.lab2_fragment_tabs, container, false);
        editable_text_field = (EditText) rootView.findViewById(R.id.editText);
        editable_text_field.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {

            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                TextView label = (TextView) rootView.findViewById(R.id.textView);
                String name = editable_text_field.getText().toString();
                String new_text = (name.length() > 0)? "Hello, " + name : "English mthrfck, do you speak it? ";
                label.setText(new_text);
            }

            @Override
            public void afterTextChanged(Editable editable) {

            }
        });
        return rootView;
    }
}