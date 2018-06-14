package com.educloud.app;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.webkit.WebView;


public class Registration extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_registration);

        /* Get the WebView */
        WebView WebViewTest = (WebView) findViewById(R.id.WebViewTest);

        /* Activate JavaScript */
        WebViewTest.getSettings().setJavaScriptEnabled(true);

        WebViewTest.loadUrl(mainactivity.URL+"regform.php");
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        // Inflate the menu; this adds items to the action bar if it is present.

            getMenuInflater().inflate(R.menu.mainactivity, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        if (id == R.id.action_exit) {
            SharedPreferences login_ck = getSharedPreferences("login", MODE_PRIVATE);
            SharedPreferences.Editor edit = login_ck.edit();
            edit.putInt("login_ok", 0);
            edit.commit();
            getSharedPreferences("login", 0).edit().clear().commit();
            Intent i = new Intent(getApplicationContext(),mainactivity.class); // Your list's Intent
            i.setFlags(i.getFlags() | Intent.FLAG_ACTIVITY_NO_HISTORY); // Adds the FLAG_ACTIVITY_NO_HISTORY flag
            startActivity(i);
            finish();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

}
