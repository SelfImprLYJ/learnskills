package com.example.user.jnistudy;

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.os.Environment;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.net.URI;

public class MainActivity extends AppCompatActivity {

    private String filePath;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_main);

            MainActivity.this.getSystemService().

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        JniUtil util = new JniUtil();
        int sum = util.accessMethod();

        JniUtil.accessStaticFiled();
        tv.setText(JniUtil.stringFromJNI() +
                "   \n" + JniUtil.stringFromC() +
                " \n" + JniUtil.myJNIEnv() +
             "\n" + util.accessFiled() +
             "\n" + "count: " + JniUtil.count +"\n" + "sum: " + sum);

        verifyStoragePermissions(MainActivity.this);
        if (Environment.getExternalStorageState().endsWith(Environment.MEDIA_MOUNTED)){
            filePath = Environment.getExternalStorageDirectory().getPath()+"/";
            JniUtil.accessStaticMethod(filePath);
            JniUtil.accessConstructor(filePath);
        }


    }

    // Storage Permissions
    private static final int REQUEST_EXTERNAL_STORAGE = 1;
    private static String[] PERMISSIONS_STORAGE = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE};

    /**
     * Checks if the app has permission to write to device storage
     * If the app does not has permission then the user will be prompted to
     * grant permissions
     *
     * @param activity
     */
    public static void verifyStoragePermissions(Activity activity) {
        // Check if we have write permission
        int permission = ActivityCompat.checkSelfPermission(activity,
                Manifest.permission.WRITE_EXTERNAL_STORAGE);

        if (permission != PackageManager.PERMISSION_GRANTED) {
            // We don't have permission so prompt the user
            ActivityCompat.requestPermissions(activity, PERMISSIONS_STORAGE,
                    REQUEST_EXTERNAL_STORAGE);
        }
    }



}
