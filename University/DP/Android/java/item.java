package com.educloud.app;

import android.annotation.TargetApi;
import android.app.DownloadManager;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Build;
import android.os.Environment;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import org.apache.http.NameValuePair;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;


public class item extends ActionBarActivity {
    private String pid;

    String id, name, des, type, date, author, folder, pic, file;
    Bitmap bmp = null; URL url;

    private ProgressDialog pDialog;

    // Создаем JSON парсер
    JSONParser jParser = new JSONParser();
    JSONObject json;

    ArrayList<HashMap<String, String>> itemsList;

    // url получения списка всех материалов из категории
    private static final String url_cat = mainactivity.URL + "/mobile_module/get_item.php";

    // JSON Node names
    private static final String TAG_SUCCESS = "success";
    private static final String TAG_ITEM = "item";
    private static final String TAG_ID = "id";
    private static final String TAG_NAME = "name";
    private static final String TAG_DES = "description";
    private static final String TAG_TYPE = "type";
    private static final String TAG_DATE = "added";
    private static final String TAG_AUTHOR = "at";
    private static final String TAG_PATCH = "folder";
    private static final String TAG_PIC_URL = "pic";
    private static final String TAG_FILE_URL = "file";

    private static final String TAG_MESSAGE = "message";
    private String msg = "";

    // тут будет хранится список материалов
    JSONArray items = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item);

        Intent i = getIntent();
        pid = i.getStringExtra(TAG_ID);

        new LoadItem().execute();

        Button bt = (Button) findViewById(R.id.button);
        bt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                new DowndlowdItem().execute();
                //    Intent intent = new Intent(getApplicationContext(),Main2Activity.class);
                //    startActivity(intent);

            }
        });
    }

    class DowndlowdItem extends AsyncTask<String, String, String> {

        /**
         * Перед началом фонового потока Show Progress Dialog
         */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(item.this);
            pDialog.setMessage("Скачивание материала. Подождите...");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(false);
            pDialog.show();
        }

        /**
         * Получаем все продукт из url
         */
        @TargetApi(Build.VERSION_CODES.GINGERBREAD)
        protected String doInBackground(String... args) {

            String root = Environment.getExternalStorageDirectory().toString();
            File myDir = new File(root + "/eduCloud/"+name);
            myDir.mkdirs();

            File Info = new File(root + "/eduCloud/"+name+"/info.txt");

            try {
                FileWriter fw = new FileWriter(Info);
                fw.write(json.toString());
                fw.close();
                Log.d("Save json","OK");
            } catch (IOException e) {
                e.printStackTrace();
            }


            if( !(pic.equals("NULL")) )
            {
                File file = new File (root + "/eduCloud/"+name+"/img.jpg");
                try {
                    FileOutputStream out = new FileOutputStream(file);
                    bmp.compress(Bitmap.CompressFormat.JPEG, 90, out);
                    out.flush();
                    out.close();

                } catch (Exception e) {
                    e.printStackTrace();
                }
            }


            String url = mainactivity.URL+"files/"+folder+"/"+file;
            DownloadManager.Request request = new DownloadManager.Request(Uri.parse(url));
            request.setDescription("Скачивание");
            request.setTitle(name);
        // in order for this if to run, you must use the android 3.2 to compile your app
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
                request.allowScanningByMediaScanner();
                request.setNotificationVisibility(DownloadManager.Request.VISIBILITY_VISIBLE_NOTIFY_COMPLETED);
            }
            request.setAllowedNetworkTypes(DownloadManager.Request.NETWORK_MOBILE|DownloadManager.Request.NETWORK_WIFI);
            request.setDestinationInExternalPublicDir("/eduCloud/"+name, file);

        // get download service and enqueue file
            DownloadManager manager = (DownloadManager) getSystemService(Context.DOWNLOAD_SERVICE);
            manager.enqueue(request);


/*           String path = root + "/eduCloud/"+name;
            Log.d("Files", "Path: " + path );
            File f = new File(path);
            File file[] = f.listFiles();
            Log.d("Files", "Size: "+ file.length);
            for (int i=0; i < file.length; i++)
            {
                Log.d("Files", "FileName:" + file[i].getName());
            }*/

            return null;
        }

        /**
         * После завершения фоновой задачи закрываем прогрес диалог
         * *
         */
        protected void onPostExecute(String result) {
            // закрываем прогресс диалог после получение все продуктов
            pDialog.dismiss();

            if (result != null)
                Toast.makeText(getApplicationContext(),"Download error: "+result, Toast.LENGTH_LONG).show();
            else
                Toast.makeText(getApplicationContext(),"Скачивание продолжилось в фоновом режиме", Toast.LENGTH_SHORT).show();
            }

        }


    class LoadItem extends AsyncTask<String, String, String> {
        int success;

        /**
         * Перед началом фонового потока Show Progress Dialog
         */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(item.this);
            pDialog.setMessage("Загрузка материала. Подождите...");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(false);
            pDialog.show();
        }

        /**
         * Получаем все продукт из url
         */
        protected String doInBackground(String... args) {
            // Будет хранить параметры
            List<NameValuePair> params = new ArrayList<NameValuePair>();
            params.add(new BasicNameValuePair("id", pid));

            Log.d("Param", params.toString());

            // получаем JSON строк с URL
            json = jParser.makeHttpRequest(url_cat, "POST", params);

            Log.d("GET JSON ANSWER: ", json.toString());

            try {
                // Получаем SUCCESS тег для проверки статуса ответа сервера
                success = json.getInt(TAG_SUCCESS);

                if (success == 1) {
                    // Получаем масив
                    items = json.getJSONArray(TAG_ITEM);

                        JSONObject c = items.getJSONObject(0);

                        // Сохраняем каждый json елемент в переменную
                        id = c.getString(TAG_ID);
                        name = c.getString(TAG_NAME);
                        des = c.getString(TAG_DES);
                        type = c.getString(TAG_TYPE);
                        date = c.getString(TAG_DATE);
                        author = c.getString(TAG_AUTHOR);
                        folder = c.getString(TAG_PATCH);
                        pic = c.getString(TAG_PIC_URL);
                        file = c.getString(TAG_FILE_URL);

                    if(pic != "" || pic != "NULL") {
                        try {
                            Log.d("IMG URL",mainactivity.URL + "files/" + folder + "/" + pic);
                            url = new URL(mainactivity.URL + "files/" + folder + "/" + pic);
                            bmp = BitmapFactory.decodeStream(url.openConnection().getInputStream());
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }

                } else {
                    // категорий нет
                    msg = json.getString(TAG_MESSAGE);
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

            if (success == 0 || success == 2) {
                Toast toast = Toast.makeText(getApplicationContext(),
                        msg, Toast.LENGTH_SHORT);
                toast.show();
            }
            else
            {
                TextView txtName = (TextView) findViewById(R.id.textName);
                TextView txtType = (TextView) findViewById(R.id.textType);
                TextView txtDes = (TextView) findViewById(R.id.textDes);
                TextView txtDate = (TextView) findViewById(R.id.textDate);
                TextView txtAuthor = (TextView) findViewById(R.id.textAuthor);

                ImageView imageView = (ImageView) findViewById(R.id.imageView);
                if( !(pic.equals("NULL")) ) {
                    imageView.setImageBitmap(bmp);
                }
                else{
                    Log.d("PIC NONE","ok");
                    Resources resources = getResources();
                    imageView.setImageDrawable(resources.getDrawable(R.drawable.none));
                }
                Log.d("PIC NAME",pic);

                txtName.setText(name);
                txtType.setText(type);
                txtDes.setText(des);
                txtDate.setText(date);
                txtAuthor.setText(author);
            }

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
