package com.educloud.app;

import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.AsyncTask;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.List;


public class mainactivity extends ActionBarActivity {

    // Для авторизации
    EditText login, Password;

    private ProgressDialog pDialog;

    JSONParser jsonParser = new JSONParser();
    public  static final String URL = "http://ita109.no-ip.org/";
    private static final String url_auth = URL+"/mobile_module/auth.php";
    private static final String TAG_SUCCESS = "success";
    private static final String TAG_MESSAGE = "message";
    private String msg="";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.layoutmainactivity);

        Button bt = (Button) findViewById(R.id.button2);
        Button btReg = (Button) findViewById(R.id.button);
        login = (EditText)findViewById(R.id.EditText1);
        Password = (EditText)findViewById(R.id.EditText2);

        bt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // Авторизация

                if (login.length() < 1 || Password.length() < 1)
                {
                    Toast toast = Toast.makeText(getApplicationContext(),
                            "Поля не заполнены!", Toast.LENGTH_SHORT);
                    toast.show();
                }
                else {
                    new Auth().execute();
                }

                //    Intent intent = new Intent(getApplicationContext(),Main2Activity.class);
                //    startActivity(intent);

            }
        });

        btReg.setOnClickListener(new View.OnClickListener()
        {
            public void onClick(View v)
            {
                Intent i = new Intent(getApplicationContext(),
                        Registration.class);
                i.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                startActivity(i);
            }
        });

        (findViewById(R.id.textView)).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Uri address = Uri.parse(URL);
                Intent openlink = new Intent(Intent.ACTION_VIEW, address);
                startActivity(openlink);
            }
        });

    }


    class Auth extends AsyncTask<Void, Integer, Integer> {

        /**
         * Перед началом показать в фоновом потоке прогресс диалог
         **/
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(mainactivity.this);
            pDialog.setMessage("Выполняется вход...");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(true);
            pDialog.show();
        }

        protected Integer doInBackground(Void... params) {

            List<NameValuePair> param = new ArrayList<NameValuePair>();
            login = (EditText) findViewById(R.id.EditText1);
            Password = (EditText) findViewById(R.id.EditText2);
            String Login = login.getText().toString();
            String Pass = Password.getText().toString();
            param.add(new BasicNameValuePair("login", Login));
            param.add(new BasicNameValuePair("pas", Pass));

            int success=-1;

            // получаем ответ по HTTP запросу
            Log.d("Param", param.toString());
            JSONObject json = jsonParser.makeHttpRequest(url_auth, "POST", param);
            try {
                success = json.getInt(TAG_SUCCESS); msg = json.getString(TAG_MESSAGE);
            } catch (JSONException e) {
                success =-1; e.printStackTrace();
            }

            Log.d("PHP MESSAGE", json.toString() );

            return success;
        }


        protected void onPostExecute(Integer result) {

            if (result == 1) {
                // Успешно
                //   Intent i = getIntent();
                //   setResult(100, i);
                Toast toast = Toast.makeText(getApplicationContext(),
                        msg, Toast.LENGTH_SHORT);
                toast.show();

                pDialog.dismiss();

                login = (EditText) findViewById(R.id.EditText1);
                String Login = login.getText().toString();
                SharedPreferences login_ck = getSharedPreferences("login", MODE_PRIVATE);
                SharedPreferences.Editor edit = login_ck.edit();
                edit.putInt("login_ok", 1);
                edit.putString("login_name", Login);
               Log.d("Login", Login);
                edit.commit();
                Password = (EditText)findViewById(R.id.EditText2);
                Password.setText("");

                Intent intent = new Intent(getApplicationContext(),Main2Activity.class);
                startActivity(intent);
            }
            if (result == 3 || result == 4) {
                // юзер не найден
                Toast toast = Toast.makeText(getApplicationContext(),
                        msg, Toast.LENGTH_SHORT);
                toast.show();
                pDialog.dismiss();
            }
            if (result == 5 || result == -1) {
                // ошибка
                Toast toast = Toast.makeText(getApplicationContext(),
                        msg, Toast.LENGTH_SHORT);
                toast.show();
                pDialog.dismiss();
            }
        }
    }


    protected void onDestroy()
    {
        SharedPreferences login_ck = getSharedPreferences("login", MODE_PRIVATE);
        SharedPreferences.Editor edit = login_ck.edit();
        edit.putInt("login_ok", 0);
        edit.commit();
        getSharedPreferences("login", 0).edit().clear().commit();

        android.os.Process.killProcess(android.os.Process.myPid());
        super.onDestroy();
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        // Inflate the menu; this adds items to the action bar if it is present.
        SharedPreferences login_ck = getSharedPreferences("login", MODE_PRIVATE);
        int login_ok = login_ck.getInt("login_ok", 0);
        if(login_ok==1)
            getMenuInflater().inflate(R.menu.mainactivity_on, menu);
        else
            getMenuInflater().inflate(R.menu.mainactivity, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_fav) {
            Intent intent = new Intent(getApplicationContext(),Items_favor.class);
            startActivity(intent);

            return true;
        }

        if (id == R.id.action_down) {
            Intent intent = new Intent(getApplicationContext(),Saved.class);
            startActivity(intent);

            return true;
        }

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

    @Override
    public void onResume()
    {
        SharedPreferences login_ck = getSharedPreferences("login", MODE_PRIVATE);
        int login_ok = login_ck.getInt("login_ok", 0);

        if(login_ok==1)
        {
            Intent intent = new Intent(getApplicationContext(),Main2Activity.class);
            startActivity(intent);
        }

        super.onResume();
    }


}
