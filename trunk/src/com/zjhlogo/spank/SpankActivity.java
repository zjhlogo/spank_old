package com.zjhlogo.spank;

import android.app.Activity;
import android.os.Bundle;

public class SpankActivity extends Activity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(new SpankView(getApplicationContext()));
    }
}
