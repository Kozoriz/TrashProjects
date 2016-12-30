package com.example.andrii.labsontabs.Fragments;

import android.app.Fragment;

/**
 * Created by andrii on 17.12.16.
 */



public class FragmentFactory {
    public enum FragmentId {LAB2, LAB3, LAB4, LAB5, LAB6, LAB7, LAB8, LAB9, INDIVIDUAL}
    public static Fragment CreateInstance(FragmentId id) {
        switch (id) {
            case LAB2: {
                return new FragmentLab2();
            }
            case LAB3: {
                return new FragmentLab3();
            }
            case LAB4: {
                return new FragmentLab4();
            }
            case LAB5: {
                return new FragmentLab5();
            }
            case LAB6: {
                return new FragmentLab6();
            }
            case LAB7: {
                return new FragmentLab7();
            }
            case LAB8: {
                return new FragmentLab8();
            }
            case LAB9: {
                return new FragmentLab9();
            }
            case INDIVIDUAL: {
                return new FragmentIndividual();
            }
        }
        return new Fragment();
    }
}
