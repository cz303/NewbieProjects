package com.educloud.app;

import android.app.Activity;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.app.ProgressDialog;
import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
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

import com.educloud.app.JSONParser;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Main2Activity extends Activity {


    private ProgressDialog pDialog;

    // Создаем JSON парсер
    JSONParser jParser = new JSONParser();

    ArrayList<HashMap<String, String>> catList;

    // url получения списка всех категорий
    private static final String url_cat= mainactivity.URL+"/mobile_module/get_cat.php";

    // JSON Node names
    private static final String TAG_SUCCESS = "success";
    private static final String TAG_CATEGORY = "category";
    private static final String TAG_ID = "id";
    private static final String TAG_NAME = "name";
    private static final String TAG_MESSAGE = "message";
    private static final String TAG_DESCRIPTION = "des";
    private String msg="";

    // тут будет хранится список категорий
    JSONArray categories = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        catList = new ArrayList<HashMap<String, String>>();

        new LoadAllCategories().execute();

        ListView lv = (ListView)findViewById(android.R.id.list);

        // на выбор одного продукта
        // запускается другой активити
        lv.setOnItemClickListener(new OnItemClickListener() {

            @Override
            public void onItemClick(AdapterView<?> parent, View view,
                                    int position, long id) {
                // getting values from selected ListItem
                String pid = ((TextView) view.findViewById(R.id.id)).getText()
                        .toString();
                String name = ((TextView) view.findViewById(R.id.name)).getText()
                        .toString();
                String dec = ((TextView) view.findViewById(R.id.des)).getText()
                        .toString();

                // Запускаем новый intent который покажет нам Activity
                Intent in = new Intent(getApplicationContext(), Items.class);
                // отправляем pid в следующий activity
                in.putExtra(TAG_ID, pid);
                in.putExtra(TAG_NAME, name);
                in.putExtra(TAG_DESCRIPTION, dec);

                // запуская новый Activity ожидаем ответ обратно
                startActivity(in);

                overridePendingTransition(R.anim.slide_in_right, R.anim.slide_out_left);
            }
        });


    }


    /**
     * Фоновый Async Task для загрузки всех категорий по HTTP запросу
     * */
    class LoadAllCategories extends AsyncTask<String, String, String> {
    int success;
        /**
         * Перед началом фонового потока Show Progress Dialog
         * */
        @Override
        protected void onPreExecute() {
            super.onPreExecute();
            pDialog = new ProgressDialog(Main2Activity.this);
            pDialog.setMessage("Загрузка категорий. Подождите...");
            pDialog.setIndeterminate(false);
            pDialog.setCancelable(false);
            pDialog.show();
        }

        /**
         * Получаем все продукт из url
         * */
        protected String doInBackground(String... args) {
            // Будет хранить параметры
            List<NameValuePair> params = new ArrayList<NameValuePair>();
            // получаем JSON строк с URL
            JSONObject json = jParser.makeHttpRequest(url_cat, "GET", params);

            Log.d("GET JSON ANSWER: ", json.toString());

            try {
                // Получаем SUCCESS тег для проверки статуса ответа сервера
                success = json.getInt(TAG_SUCCESS);

                if (success == 1) {
                    // Получаем масив
                    categories = json.getJSONArray(TAG_CATEGORY);

                    // перебор
                    for (int i = 0; i < categories.length(); i++) {
                        JSONObject c = categories.getJSONObject(i);

                        // Сохраняем каждый json елемент в переменную
                        String id = c.getString(TAG_ID);
                        String name = c.getString(TAG_NAME);
                        String des = c.getString(TAG_DESCRIPTION);

                        // Создаем новый HashMap
                        HashMap<String, String> map = new HashMap<String, String>();

                        // добавляем каждый елемент в HashMap ключ => значение
                        map.put(TAG_ID, id);
                        map.put(TAG_NAME, name);
                        map.put(TAG_DESCRIPTION, des);

                        // добавляем HashList в ArrayList
                        catList.add(map);
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
         * **/
        protected void onPostExecute(String file_url) {
            // закрываем прогресс диалог после получение все продуктов
            pDialog.dismiss();

                    if(success==0)
                    {
                        Toast toast = Toast.makeText(getApplicationContext(),
                                msg, Toast.LENGTH_SHORT);
                        toast.show();
                    }
                    /**
                     * Обновляем распарсенные JSON данные в ListView
                     * */
                     Log.d("LIST VIEW","ПЕРЕД ВЫВОДОМ");
                     ListAdapter adapter = new SimpleAdapter(
                            Main2Activity.this, catList,
                            R.layout.list_item,
                            new String[] { TAG_ID, TAG_NAME, TAG_DESCRIPTION},
                            new int[] { R.id.id, R.id.name , R.id.des});
                    // обновляем listview

                    ListView myList=(ListView)findViewById(android.R.id.list);
                    Log.d("LIST VIEW","ПЕРЕД АПДЕЙТОМ");
                    myList.setAdapter(adapter);
        }

    }

    @Override
    public void onBackPressed() {
        moveTaskToBack(true);
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
