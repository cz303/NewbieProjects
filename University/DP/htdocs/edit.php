<!doctype html>
<html>
<head>
<meta charset="utf-8">
</head>

<body>

<?php 
session_start();
if ( !isset($_SESSION['user_id']) ) 
{
echo " <script> alert('Вы не авторизованы как администратор'); </script>";
header('HTTP/1.0 401 Unauthorized'); exit();
}

$mess="";
$f_err="";

if ($_POST)
{
  $randname = $_POST['folder'];
  
  if(empty($_FILES['file']['name']))
  {
	  $pname = NULL;
  }
  else
  {
	$types     = array(
        '.jpg',
        '.JPG',
        '.jpeg',
        '.gif',
        '.bmp',
        '.png'
    ); //поддерживаемые форматы загружаемых файлов
    $max_size  = 5242880; //максимальный размер загружаемого файла (5-МБ)
    $pname     = $_FILES['file']['name'];
    $ext       = substr($pname, strpos($pname, '.'), strlen($pname) - 1); //определяем тип загружаемого файла
	$path      = 'files/'.$randname.'/'; //директория для загрузки
	// $file = date('YmdHis') . 'jpg';
	$uploadfile = $path . $pname;
	// $pic_name = $name . $ext;
	
    //проверка на соответствие формата
    if (!in_array($ext, $types)) {
        $f_err++;
        $mess =  $mess . '<p style="color:red;">Загружаемый файл '.$ext.' не является картинкой.</p>';
    }

    //проверка размера файла
    if ($_FILES['file']['size'] > $max_size) {
        $f_err++;
        $mess =  $mess . '<p style="color:red;">Размер загружаемой картинки превышает 5 Mb.</p>';
    }
	 
	if ($f_err == 0 && !($pname==NULL)){
	 if (move_uploaded_file($_FILES['file']['tmp_name'], iconv("UTF-8","WINDOWS-1251",$uploadfile))) {
	   echo "Изображение успешно загруженно.\n";
	 } else {
	   echo "Ошибка загрузки изображения.\n";
	   $pname = NULL;
	 }
   }   
  }
 
  
  if (isset($_POST['name']) ) $product_name = mysql_real_escape_string($_POST['name']);
  if (isset($_POST['cat']) ) $product_cat = $_POST['cat'];	
  if (isset($_POST['des']) ) $product_des = mysql_real_escape_string($_POST['des']);
  if (isset($_POST['type']) ) $product_type = $_POST['type'];	
  if (isset($_POST['orig_pic']) ) $pname = $_POST['orig_pic'];
  
require 'db_connect.php';
$db = new DB_CONNECT();

$query = mysql_query('UPDATE files SET name="'.$product_name.'", cat_id="'.$product_cat.'", type="'.$product_type.'", 
										description="'.$product_des.'", pic="'.$pname.'" WHERE id="'.$_POST['id'].'"');
	
	if($query) { $mess = $mess . "<p style=\"color:red;\">Запись ".$product_name." успешно отредактирована</p>";
        // если не удачно, то
		}
        else $mess = "<p style=\"color:red;\">Какая-то ошибка</p>";
 }		
echo ($mess);

if( isset( $_GET['id'] ))
{
require 'db_connect.php';
$db = new DB_CONNECT();

$query = mysql_query("SELECT * FROM files WHERE id =".$_GET['id']." ");
$num = mysql_num_rows ($query);
if($num > 0)
{
	$list = mysql_fetch_assoc($query);
	
				
echo('	
	<form name="edit"  id="edit" method="post" action="'.$_SERVER['PHP_SELF'].'" enctype="multipart/form-data" >
	<input type="hidden" name="MAX_FILE_SIZE" value="5242880" />
  ');
  if($list['pic']==NULL){
  echo("
   Добавить изображение: <br>
  <input class=\"fileInput\" type=\"file\" name=\"file\"/> <p> ");}
  else{
  echo(" Изображение: <br>  <img src='/files/".$list['folder']."/".$list['pic']."' width=150 height=\"auto\"><br>
  <a href=\"delpic.php?id=".$list['id']."\">Удалить изображение</a><p>
  ");
  echo("
  <input type=\"hidden\" name=\"orig_pic\" value=\"".$list['pic']."\" />");
  }
  echo("Наименование: <br>
  <input type=\"text\" name=\"name\" size=\"100\" style=\"width: 300px;\" value=\"".$list['name']."\" />
  <p> Категория: <br>
    <Select NAME=\"cat\" >");
	

$query2 = mysql_query("SELECT * FROM category");

	while($list2 = mysql_fetch_assoc($query2))
		{
		echo(' <option value="'.$list2['id'].'"');
		if($list2['id'] == $list['cat_id']) echo(' selected="selected" ');
		echo('>'.$list2['name'].'</option> ');
		}

echo(" 		
    </Select><p>
	Тип: <br>
      <Select NAME=\"type\" >
	    <option value=\"text\" ");  if($list['type'] == "text") {echo("selected=\"selected\"");} echo(' >Текст</option> ');
        echo("<option value=\"audio\" ");  if($list['type'] == "audio") {echo("selected=\"selected\"");} echo(" >Аудио</option>");
		echo("<option value=\"video\" ");  if($list['type'] == "video") {echo("selected=\"selected\"");} echo(" >Видео</option>");
		echo("<option value=\"picture\" ");  if($list['type'] == "picture") {echo("selected=\"selected\"");} echo(" >Изображение</option>
    </Select><p>
	
  <p> Описание: <br>");
echo('<textarea type="text" name="des" style="width: 300px; height: 100px;" >'.$list['description'].'</textarea>');
echo("  <p style=\"text-align: center;\">
    <input type=\"hidden\" name=\"id\" value=\"".$list['id']."\" />
	<input type=\"hidden\" name=\"folder\" value=\"".$list['folder']."\" />
	<input type=\"submit\" name=\"save_btm\" value=\"Сохранить изменения\" 
    onclick = \"this.style.visibility='hidden'\" />
</form>
	");
} else
echo("Не найденно этого товара");
}

?>

</body>


</html>