package com.educloud.app;

import android.app.ProgressDialog;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Environment;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;


public class Saved extends ActionBarActivity {

    private ProgressDialog pDialog;
    private File file;
    private ArrayList<String> myList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_saved);


        new Scan().execute();


        ListView lv = (ListView)findViewById(android.R.id.list);

        // на выбор одного продукта
        // запускается другой активити
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, View view,
                                    int position, long id) {
                // getting values from selected ListItem
                String folder = ((TextView) view.findViewById(R.id.name)).getText()
                        .toString();

                // Запускаем новый intent который покажет нам Activity
                Intent in = new Intent(getApplicationContext(), item_saved.class);
                // отправляем pid в следующий activity
                in.putExtra("folder", folder);

                // запуская новый Activity ожидаем ответ обратно
                startActivityForResult(in, 100);

                overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            }
        });

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        // если результующий код равен 100
        if (resultCode == 100) {
            // если полученный код результата равен 100
            // значит пользователь удалил какой то материал
            // обновляем данные
            new Scan().execute();
        }

    }

    class Scan extends AsyncTask<String, String, String> {

        /**
         * Перед началом фонового потока Show Progress Dialog
         */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(Saved.this);
            pDialog.setMessage("Сканирование папки. Подождите...");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(false);
            pDialog.show();
        }


        protected String doInBackground(String... args) {

            myList = new ArrayList<String>();

            String root_sd = Environment.getExternalStorageDirectory().toString();
            file = new File( root_sd + "/eduCloud" ) ;
            if(file.exists()) {
                File list[] = file.listFiles();

                for (int i = 0; i < list.length; i++) {
                    myList.add(list[i].getName());
                }
            }
            return null;
        }

        /**
         * После завершения фоновой задачи закрываем прогрес диалог
         * *
         */
        protected void onPostExecute(String file_url) {
            // закрываем прогресс диалог после получение все продуктов
            pDialog.dismiss();

            ArrayAdapter<String> adapter = new ArrayAdapter<String>(Saved.this, R.layout.list_item3, R.id.name, myList);

            ListView List = (ListView) findViewById(android.R.id.list);
            List.setAdapter(adapter);

            }

        }

}
