<!doctype html>
<html>
<head>
<meta charset="utf-8">

<style type="text/css">
.ui-progressbar-value { 
    background-image: 
    url(img/pbar-ani.gif);
    padding-left:10px;
    font-weight:normal;
}

#upload_form {
    display:block;
}
#progress {
    display: none;
}

#progress #bar {
    height: 22px;
    width: 300px;
}
</style>

<script type="text/javascript" src="jQueryAssets/jquery-1.6.2.min.js"></script>
<script type="text/javascript" src="jQueryAssets/jquery-ui-1.8.14.custom.min.js"></script>
<script type="text/javascript" src="jQueryAssets/jquery.form.js"></script>
<link href="jQueryAssets/jquery-ui-1.8.14.custom.css" rel="stylesheet" type="text/css" />


<script type="text/javascript">
function validate(Form)
{
var errors="";
var x=Form.name.value;
var y=Form.des.value;

if (x==null || x=="" || x.length == 0 || x=="undefined")
  {
  errors+="Строка имени пуста!\n";
  }
if (y==null || y=="" || y.length < 10 || y=="undefined")
  {
  errors+="Недостаточно описания!\n";
  }
    
if(errors==""){ 
return true;
}
else
{ 
alert(errors);
Form.add_btm.style.visibility='visible';
return false;
}
}
</script>

<script type="text/javascript">
var t;
var echo = "";
/* Функция получения информации о процессе загрузки по AJAX */
progress = function(){
    $.ajax({
        url: 'upload.php',
        dataType: 'json',
        success: function(data){
            if(data.percent) {
                	$("#bar").progressbar({
                    value: Math.ceil(data.percent), // Заполняем прогресс бар
                });
                $('.ui-progressbar-value').text(data.percent+'%'); // Отображаем на прогресс баре процент загрузки
            }
        }
    });
}
$(document).ready(function() {
    /* Отправка формы загрузки по AJAX */  
    $('#add').ajaxForm({
        type: 'POST',
        success: function(responseText) { 
           clearTimeout(t); echo+=responseText;
           $('#info').html(echo);
		   $('#progress').hide();		   
        },
        beforeSubmit: function() {
            /*  Перед отправкой данных на сервер прячем форму, показываем прогресс бар и запускаем таймер */
            $("#add").hide();
			$('#progress').show();
			$('#info').html('Идет загрузка файлов...');
            t = setInterval("progress()", 100);
        }
   });

});

</script>


</head>

<body bgcolor="#FFFFFF">

<?php

function deleteDirectory($dir) {
    if (!file_exists($dir)) return true;
    if (!is_dir($dir)) return unlink($dir);
    foreach (scandir($dir) as $item) {
        if ($item == '.' || $item == '..') continue;
        if (!deleteDirectory($dir.DIRECTORY_SEPARATOR.$item)) return false;
    }
    return rmdir($dir);
}

session_start();

$up_id = uniqid();

if ( !isset($_SESSION['user_id']) ) 
{
echo " <script> alert('Вы не авторизованы'); </script>";
header('HTTP/1.0 401 Unauthorized'); exit();
}

if ($_POST)
{
 $randname      = base_convert(time(), 10, 36).base_convert(rand(0,2000000000), 10, 36);
 $f_err     = 0; //вспомогательная переменная
 $mess = "";
 
 if(!empty($_FILES['file']['name'][0]))
  {
    $max_size  = 124857600; //максимальный размер загружаемого файла (120-МБ)
    $fname     = $_FILES['file']['name'][0];
    $ext       = substr($fname, strpos($fname, '.'), strlen($fname) - 1); //определяем тип загружаемого файла
	$path      = 'files/'.$randname.'/'; //директория для загрузки
	// $file = date('YmdHis') . 'jpg';
	$uploadfile = $path . $fname;
	// $pic_name = $name . $ext;
	
    //проверка размера файла
    if ($_FILES['file']['size'][0] > $max_size) {
        $f_err++;
        $mess =  $mess . '<p style="color:red;">Размер загружаемого файла превышает 120 Mb.</p>';
    }
	 
	if ($f_err == 0){
	mkdir("files/".$randname);
	 if (move_uploaded_file($_FILES['file']['tmp_name'][0], iconv("UTF-8","WINDOWS-1251",$uploadfile))) {
	 if ($_FILES['file']['error'][0] === UPLOAD_ERR_OK) {
	   echo (" <br>Файл успешно загружен. <br>") ;
	   
  
  
  if(empty($_FILES['file']['name'][1]))
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
    $pname     = $_FILES['file']['name'][1];
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
    if ($_FILES['file']['size'][1] > $max_size) {
        $f_err++;
        $mess =  $mess . '<p style="color:red;">Размер загружаемой картинки превышает 5 Mb.</p>';
    }
	 
	if ($f_err == 0 && !($pname==NULL)){
	 if (move_uploaded_file($_FILES['file']['tmp_name'][1], iconv("UTF-8","WINDOWS-1251",$uploadfile))) {
	   echo "Изображение успешно загруженно.\n";
	 } else {
	   echo "Ошибка загрузки изображения.\n";
	   $pname = NULL;
	 }
   }   
  }
  		require 'db_connect.php';
		 
		  $db = new DB_CONNECT();
		  

		  if (isset($_POST['name']) ) $product_name = mysql_real_escape_string($_POST['name']);
		  if (isset($_POST['cat']) ) $product_cat = $_POST['cat'];	
		  if (isset($_POST['des']) ) $product_des = mysql_real_escape_string($_POST['des']);
		  if (isset($_POST['type']) ) $product_type = $_POST['type'];	
		  $date = date("Y-m-d");
		  $product_user = $_SESSION['user_id'];
		  $product_folder = $randname;
		  
		  
		  $query = mysql_query(" INSERT INTO files  
				(name,description,type,added,user_id,folder,pic,file,cat_id) 
				VALUES(\"".$product_name."\",
						\"".$product_des."\",
						\"".$product_type."\",
						\"".$date."\",
						\"".$product_user."\",
						\"".$product_folder."\",
						\"".$pname."\",
						\"".$fname."\",
						\"".$product_cat."\")
				");

				
			if($query) { $mess = $mess . '<p style=\"color:red;\">Запись <b>'.$_POST['name'].'</b> успешно добавлена.</p>';
				$query = "SELECT `id` FROM `files` WHERE user_id=".$_SESSION['user_id']."";
				$sql = mysql_query($query) or die(mysql_error()); 
				$_SESSION['my_files'] = mysql_num_rows($sql);
				}
				else $mess = "<p style=\"color:red;\">Какая-то ошибка.</p>";
		 
		 echo ($mess);

    }  else { if ($_FILES["file"]["error"][0] == 1 || 2)
        {    echo ("Размер файла превышает 110 мегабайт"); } }
   } else { deleteDirectory("./files/".$randname.""); 
			if ($_FILES["file"]["error"][0] == 1 || 2) {    
			echo ("Размер файла превышает 110 мегабайт");  }
		  }
 }
 }
 else
 echo ('<p style="color:red;">Файлы для загрузки не указаны.</p>');
 }		
?>


<?php
if (!$_POST)
{

echo ('

<div id="info"></div>
  <div id="progress">
  <div id="bar"></div>
  </div><br>
<form name="add"  id="add" method="post" action="'.$_SERVER['PHP_SELF'].'" enctype="multipart/form-data" onsubmit="return validate(this);">
   
   <input type="hidden" name="'.ini_get("session.upload_progress.name").'" value="test" />
   <input type="hidden" name="MAX_FILE_SIZE" value="124857600" />

   Добавить файл: <br>
   <input class="fileInput" type="file" id="file1" name="file[]"/> <p>
   
  Добавить изображение: <br>
  <input class="fileInput" type="file" id="file2" name="file[]"/> <p>
  <p> Тип материала: <br>
    <Select NAME="type" >
        <option value="text" selected="selected">Текст</option>
        <option value="picture">Изображения</option>
		<option value="video">Видео</option>
		<option value="audio">Аудио</option>
    </Select><p>
  Наименование: <br>
  <input type="text" name="name" size="100" id="name" style="width: 300px;"/>
  <p> Категория: <br>
    <Select NAME="cat" >');	
	
require 'db_connect.php';	
$db = new DB_CONNECT();
$query2 = mysql_query("SELECT * FROM category");

	while($list2 = mysql_fetch_assoc($query2))
		{
		echo(' <option value="'.$list2['id'].'">'.$list2['name'].'</option> ');
		}
 
echo('
 </Select><p>
  <p> Описание: <br>
    <textarea type="text" name="des" id="des" style="width: 300px; height: 133px;"> </textarea>
    <p style="text-align: center;">
    <input type="submit" name="add_btm" id="add_btm"  value="Добавить" 
    onclick = "this.style.visibility=hidden" />
</form>

');
}
?>

</body>
</html>