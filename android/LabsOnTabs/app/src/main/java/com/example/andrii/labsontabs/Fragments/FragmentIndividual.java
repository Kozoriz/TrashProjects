package com.example.andrii.labsontabs.Fragments;

import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;

import com.example.andrii.labsontabs.Converter;
import com.example.andrii.labsontabs.R;

/**
 * Created by andrii on 17.12.16.
 */


/**
 * A placeholder fragment containing a simple view.
 */
public class FragmentIndividual extends Fragment {
    public View rootView;
    public Spinner spinner_1;
    public Spinner spinner_2;
    public EditText currency_value_field;
    public EditText currency_converted_field;
    public Spinner curency_from_spinner;
    public Spinner curency_to_spinner;
    public Button currency_convert_button;

    public Converter converter_;


    public FragmentIndividual() {
    }


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.individual_fragment_tabs, container, false);

        GetViewMembers();
        Init();

        return rootView;
    }

    private void GetViewMembers() {
        spinner_1 = (Spinner) rootView.findViewById(R.id.currency_1_spinner);
        spinner_2 = (Spinner) rootView.findViewById(R.id.currency_2_spinner);

        currency_value_field = (EditText) rootView.findViewById(R.id.currency_value_1_field);
        currency_converted_field = (EditText) rootView.findViewById(R.id.currency_value_2_field);

        curency_from_spinner = (Spinner) rootView.findViewById(R.id.currency_1_spinner);
        curency_to_spinner = (Spinner) rootView.findViewById(R.id.currency_2_spinner);

        currency_convert_button = (Button) rootView.findViewById(R.id.currency_convert_button);
    }

    private void Init() {
        converter_ = new Converter();

        ArrayAdapter adapter = new ArrayAdapter(rootView.getContext(),
                android.R.layout.simple_spinner_item, converter_.GetSupportedCurrencies());

        spinner_1.setAdapter(adapter);
        spinner_2.setAdapter(adapter);

        currency_convert_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String string_value = currency_value_field.getText().toString();
                if (string_value.isEmpty()) {
                    ProcessError();
                    return;
                }

                float value_for_convert = Float.parseFloat(string_value);

                if (0 >= value_for_convert) {
                    ProcessError();
                    return;
                }

                Converter.Currency curency_from = Converter.Currency.valueOf(
                        curency_from_spinner.getSelectedItem().toString());
                Converter.Currency curency_to = Converter.Currency.valueOf(
                        curency_to_spinner.getSelectedItem().toString());

                Float converted_value = converter_.ConvertCurrency(value_for_convert, curency_from, curency_to);

                currency_converted_field.setText(converted_value.toString());
            }
        });
    }

    private void ProcessError() {
        Toast toast3 = Toast.makeText(rootView.getContext().getApplicationContext(),
            "Some error occurred!", Toast.LENGTH_SHORT);
        toast3.show();
    }

}