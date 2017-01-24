package com.example.andrii.labsontabs.Fragments;

import android.support.v4.util.ArrayMap;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Map;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Created by andrii on 23.12.16.
 */

public class CurrencyAPIProcessor {
    private String USER_AGENT = "Mozilla/5.0";

    private String result;
    private JSONObject json_result;
    private Lock result_lock;

    private Thread thread;

    public CurrencyAPIProcessor() {
        result_lock = new ReentrantLock();
    }

    public void GetAPICurrenciesResponseString(String currency) throws Exception {
        result_lock.lock();

        String url = "http://api.fixer.io/latest?base=" + currency;
        System.out.println(url);
        URL obj = new URL(url);
        HttpURLConnection con = (HttpURLConnection) obj.openConnection();

        con.setRequestMethod("GET");
        con.setRequestProperty("User-Agent", USER_AGENT);

//        int responseCode = con.getResponseCode();
//        System.out.println("\nSending 'GET' request to URL : " + url);
//        System.out.println("Response Code : " + responseCode);

        BufferedReader in = new BufferedReader(
                new InputStreamReader(con.getInputStream()));
        String inputLine;
        StringBuffer response = new StringBuffer();

        while ((inputLine = in.readLine()) != null) {
            response.append(inputLine);
        }
        in.close();

        result = response.toString();
        result_lock.unlock();
    }

    public Map<String, Float> GetRatesFor (final String currency) {
        thread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    GetAPICurrenciesResponseString(currency);
                } catch (Exception ex) {
                    System.out.println(ex.toString());
                    ex.printStackTrace();
                }
            }
        });
        thread.start();

        Map<String, Float> map = new ArrayMap<String, Float>();
        try {
            thread.join();

            json_result = new JSONObject(result);
            JSONObject rates_obj = json_result.getJSONObject("rates");
            JSONArray names = rates_obj.names();

            for (int i = 0; i < names.length(); i++) {
                String name = names.getString(i);
                Float value = (float) rates_obj.getDouble(name);

//                System.out.println(name + ":" + value.toString());
                map.put(name, value);
            }


        } catch (Exception ex) {
            System.out.println(ex.toString());
            ex.printStackTrace();
        } finally {
            return map;
        }


    }


}
