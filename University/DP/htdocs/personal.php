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
echo " <script> alert('Вы не авторизованны'); </script>";
header('HTTP/1.0 401 Unauthorized'); exit();
}
require 'db_connect.php';
$mess="";

if ($_POST)
{
$db = new DB_CONNECT();

  if (isset($_POST['name']) ) $user_name = mysql_real_escape_string($_POST['name']);
  if (isset($_POST['email']) ) $user_email = mysql_real_escape_string($_POST['email']);
 //  if (isset($_POST['fav']) ) $user_fav = mysql_real_escape_string($_POST['fav']);	
	
	$user_fav = "";
	$query2 = mysql_query("SELECT * FROM category");
		while($list2 = mysql_fetch_assoc($query2))
		  {
		  if(isset($_POST['chk'.$list2['id'].''])) $user_fav = $user_fav . $list2['id'] . ",";
		  }

$query = mysql_query('UPDATE personal SET name="'.$user_name.'", email="'.$user_email.'", favotite="'.$user_fav.'" WHERE user_id="'.$_POST['id'].'"');
	
	if($query) { $mess = $mess . "<p style=\"color:red;\">Информация пользователя ".$user_name." успешно обновлена</p> 
								<br><a href='personal.php'>Вернуться</a>";
		}
        else $mess = "<p style=\"color:red;\">Какая-то ошибка</p>";
echo ($mess);
}	else{

if( isset($_SESSION['user_id']) )
{
$db = new DB_CONNECT();

$query = mysql_query("SELECT * FROM personal WHERE user_id=".$_SESSION['user_id']." ");
$query2 = mysql_query("SELECT * FROM category");

$num = mysql_num_rows ($query);
if($num > 0)
{
$list = mysql_fetch_assoc($query);
echo('	
<form name="add"  id="add" method="post" action="'.$_SERVER['PHP_SELF'].'" enctype="multipart/form-data" onsubmit="return validate(this);">
  Имя: <br>
  <input type="text" name="name" size="35" id="name" value="'.$list['name'].'" style="width: 300px;"/>
  <p> Email: <br>
  <input type="text" name="email" size="35" id="email" value="'.$list['email'].'" style="width: 300px;"/>
  <p> Любимое: <br>');

  $array = split(',',$list['favotite']);
  
  while($list2 = mysql_fetch_assoc($query2))
  {
  echo(' <label><input type="checkbox" name="chk'.$list2['id'].'"'); if(in_array($list2['id'],$array)) echo('checked="checked"'); echo('/>'.$list2['name'].'</label><br> ');
  }
  echo('
  <input type="hidden" name="id" value="'.$_SESSION['user_id'].'" />
<br>  <input type="submit" name="add_btm" id="add_btm"  value="Изменить"  />
</form>
');	
	
}
}
}

?>


</body>


</html>