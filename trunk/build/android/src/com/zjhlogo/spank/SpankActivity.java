package com.zjhlogo.spank;

import android.app.Activity;
import android.os.Bundle;

public class SpankActivity extends Activity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        // set the resource package path
		String packageName = getPackageResourcePath();
        SpankLibrary.setPackagePath(packageName);
        
        setContentView(new SpankView(getApplicationContext()));
    }
}
