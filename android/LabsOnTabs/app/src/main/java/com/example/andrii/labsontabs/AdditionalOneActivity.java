package com.example.andrii.labsontabs;

import android.graphics.Color;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

public class AdditionalOneActivity extends AppCompatActivity {
    private Snackbar mSnackbar;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_additional_one);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mSnackbar = Snackbar.make(view, "Покормил кота?", Snackbar.LENGTH_INDEFINITE)
                        .setAction("Да", snackbarOnClickListener);

                View snackbarView = mSnackbar.getView();
                snackbarView.setBackgroundColor(Color.BLUE);
                TextView snackTextView = (TextView) snackbarView.findViewById(android.support.design.R.id.snackbar_text);
                snackTextView.setTextColor(Color.RED);
                mSnackbar.show();
            }
        });
        Button dismissButton = (Button) findViewById(R.id.buttonDismiss);
        dismissButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mSnackbar.dismiss();
            }
        });
    }
    View.OnClickListener snackbarOnClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View view) {
            Toast.makeText(getApplicationContext(), "Молодец!", Toast.LENGTH_LONG).show();
        }
    };

}
