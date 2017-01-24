package com.example.andrii.labsontabs;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;

public class ChooseActivity extends AppCompatActivity {
    public final static String choosen_option = "com.example.andrii.labsontabs.choosen_option";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_choose);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
    }

    public void onRadioClick(View view) {
        Intent answer_intent = new Intent();
        switch (view.getId()) {
            case R.id.option_1_radio: {
                answer_intent.putExtra(choosen_option, "Option 1");
                break;
            }
            case R.id.option_2_radio: {
                answer_intent.putExtra(choosen_option, "Option 2");
                break;
            }
            case R.id.option_3_radio: {
                answer_intent.putExtra(choosen_option, "Option 3");
                break;
            }
            default: break;
        }
        setResult(RESULT_OK, answer_intent);
        finish();
    }
}
