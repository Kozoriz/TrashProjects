package com.example.andrii.labsontabs;

import android.icu.util.Currency;
import android.support.v4.util.ArrayMap;
import android.support.v4.util.ArraySet;

import com.example.andrii.labsontabs.Fragments.CurrencyAPIProcessor;

import java.util.Map;

/**
 * Created by andrii on 22.12.16.
 */

public class Converter {
     public enum Currency {
        AUD,
        BGN,
        BRL,
        CAD,
        CHF,
        CNY,
        CZK,
        DKK,
        EUR,
        GBP,
        HKD,
        HRK,
        HUF,
        IDR,
        ILS,
        INR,
        JPY,
        KRW,
        MXN,
        MYR,
        NOK,
        NZD,
        PHP,
        PLN,
        RON,
        RUB,
        SEK,
        SGD,
        THB,
        TRY,
        USD,
        ZAR
     }

    private CurrencyAPIProcessor api_processor;

    public Converter() {
        api_processor = new CurrencyAPIProcessor();
    }


    public Map<String, Float> GetRatesFor(Currency cur) {
        return api_processor.GetRatesFor(cur.name());
    }

    public Float GetRateFromTo(Currency from, Currency to) {
        if (from == to ) {return 1.f;}
        Map<String, Float> rates = GetRatesFor(from);

        return (rates.containsKey(to.name())) ? rates.get(to.name()) : 1.f ;
    }

    public Float ConvertCurrency(Float value, Currency from, Currency to) {
        Float rate = GetRateFromTo(from, to);
        return value * rate;
    }

    public String[] GetSupportedCurrencies() {
        Currency[] states = Currency.values();
        String[] out_array = new String[states.length];

        for (int i = 0; i < states.length; i++) {
            out_array[i] = states[i].name();
        }

        return out_array;
    }
}