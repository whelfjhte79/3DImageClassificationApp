package com.example.deepcnnapptest;

import androidx.appcompat.app.AppCompatActivity;

import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.example.deepcnnapptest.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'deepcnnapptest' library on application startup.
    static {
        System.loadLibrary("deepcnnapptest");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        // Example of a call to a native method
        AssetManager assetManager = getAssets();
        String filename = "bitmap1.bmp";

        Log.d("테스트","테스트");


        TextView tv = binding.sampleText;
        tv.setText(String.valueOf(resultIntDataFromJNI(assetManager, filename)));

    }


    public native String stringFromJNI();

    public native int resultIntDataFromJNI(AssetManager assetManager, String filename);
}