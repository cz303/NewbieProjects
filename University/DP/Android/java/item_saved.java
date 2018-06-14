package com.educloud.app;

import android.app.ProgressDialog;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Environment;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.webkit.MimeTypeMap;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;


public class item_saved extends ActionBarActivity {

    private ProgressDialog pDialog;
    String name, des, type, date, author, folder, pic, file;

    JSONParser jParser = new JSONParser();
    JSONObject json;
    JSONArray items = null;
    File imgFile; Bitmap myBitmap;

    private static final String TAG_SUCCESS = "success";
    private static final String TAG_ITEM = "item";
    private static final String TAG_NAME = "name";
    private static final String TAG_DES = "description";
    private static final String TAG_TYPE = "type";
    private static final String TAG_DATE = "added";
    private static final String TAG_AUTHOR = "at";
    private static final String TAG_FILE_URL = "file";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item_saved);

        Intent i = getIntent();
        folder = i.getStringExtra("folder");

        new LoadItem().execute();

        Button bt = (Button) findViewById(R.id.button);
        Button bt2 = (Button) findViewById(R.id.button2);

        bt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String root = Environment.getExternalStorageDirectory().toString();
                String path = root+"/eduCloud/"+folder+"/"+file;

                Log.d("Путь до файла",path);

                File file1 = new File(path);
                if(file1.exists()) {
                    MimeTypeMap map = MimeTypeMap.getSingleton();
                    String ext = MimeTypeMap.getFileExtensionFromUrl(file1.getName());
                    String type = map.getMimeTypeFromExtension(ext);

                    if (type == null)
                        type = "*/*";

                    Intent intent = new Intent(android.content.Intent.ACTION_VIEW);
                    Uri data = Uri.fromFile(file1);

                    intent.setDataAndType(data, type);

                    startActivity(intent);
                }
                else
                {
                    Toast toast = Toast.makeText(getApplicationContext(),
                            "Файл не найден", Toast.LENGTH_SHORT);
                    toast.show();
                }

            }
        });

        bt2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String root = Environment.getExternalStorageDirectory().toString();
                String path = root+"/eduCloud/"+folder;

                File file1 = new File(path);
                DeleteRecursive(file1);

                Intent i = getIntent();
                // отправляем результирующий код 100 для уведомления об удалении продукта
                setResult(100, i);
                finish();

                finish();
            }
        });


    }

    void DeleteRecursive(File fileOrDirectory) {
        if (fileOrDirectory.isDirectory())
            for (File child : fileOrDirectory.listFiles())
                DeleteRecursive(child);

        fileOrDirectory.delete();
    }


    class LoadItem extends AsyncTask<String, String, String> {
          /**
         * Перед началом фонового потока Show Progress Dialog
         */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(item_saved.this);
            pDialog.setMessage("Загрузка материала. Подождите...");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(false);
            pDialog.show();
        }


        protected String doInBackground(String... args) {


            Log.d("Folder", folder);
            String root = Environment.getExternalStorageDirectory().toString();
            String path = root+"/eduCloud/"+folder;
            Log.d("Path", folder);

            File file_info = new File(path+"/info.txt");
            StringBuilder text = new StringBuilder();
            BufferedReader br = null;

            try {
                br = new BufferedReader(new FileReader(file_info));
                String line;

                while ((line = br.readLine()) != null) {
                    text.append(line);
                    text.append('\n');
                }
            } catch (IOException e) {
                // do exception handling
            } finally {
                try { json = new JSONObject(text.toString()); br.close(); } catch (Exception e) { }
            }

            Log.d("GET JSON ANSWER: ", json.toString());

            try {
                // Получаем SUCCESS тег для проверки статуса ответа сервера

                    // Получаем масив
                    items = json.getJSONArray(TAG_ITEM);

                    JSONObject c = items.getJSONObject(0);

                    // Сохраняем каждый json елемент в переменную
                    name = c.getString(TAG_NAME);
                    des = c.getString(TAG_DES);
                    type = c.getString(TAG_TYPE);
                    date = c.getString(TAG_DATE);
                    author = c.getString(TAG_AUTHOR);
                    file = c.getString(TAG_FILE_URL);

                imgFile = new  File(path+"/img.jpg");
                if(imgFile.exists()) {
                    myBitmap = BitmapFactory.decodeFile(imgFile.getAbsolutePath());
                }


                } catch (JSONException e) {
                e.printStackTrace();
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

                TextView txtName = (TextView) findViewById(R.id.textName);
                TextView txtType = (TextView) findViewById(R.id.textType);
                TextView txtDes = (TextView) findViewById(R.id.textDes);
                TextView txtDate = (TextView) findViewById(R.id.textDate);
                TextView txtAuthor = (TextView) findViewById(R.id.textAuthor);

                ImageView myImage = (ImageView) findViewById(R.id.imageView);

                if(imgFile.exists()){
                    myImage.setImageBitmap(myBitmap);
                }
                else
                {
                    Resources resources = getResources();
                    myImage.setImageDrawable(resources.getDrawable(R.drawable.none));
                }


                txtName.setText(name);
                txtType.setText(type);
                txtDes.setText(des);
                txtDate.setText(date);
                txtAuthor.setText(author);

            }

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
}
