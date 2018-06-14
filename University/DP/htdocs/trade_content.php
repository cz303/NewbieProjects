<!doctype html>
<html>
<head>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type">

<style> 
.title_h3
{
	text-align:center;
}

</style>
<link rel="stylesheet" href="./css/style.css"	   media="screen" type="text/css">
<script type="text/javascript" src="/js/highslide/highslide-full.js"></script>
<link rel="stylesheet" type="text/css" href="/js/highslide/highslide.css" />

 <script type="text/javascript">
	hs.graphicsDir = '/js/highslide/graphics/';
	hs.align = 'center';
	hs.transitions = ['expand'];
	hs.fadeInOut = true;	
	hs.outlineType = 'rounded-white';
	hs.preserveContent = false;
	hs.loadingOpacity = 1;
	hs.cacheAjax = false;
	hs.dimmingOpacity = .75;
	hs.fullExpandOpacity = 1;
	hs.showCredits = false;
	hs.wrapperClassName = 'draggable-header';
</script>


</head>

<body>
<p>
<?php
 if(!isset($_SESSION)){
 session_start(); }
?>
  
<?php
if ( isset( $_GET['product'] ) ){ 
 $product = $_GET['product'];
 echo ("<h3 class=\"title_h3\">".$product."</h3>");
}
?>
  
  
<?php
$msg = "";

function deleteDirectory($dir) {
    if (!file_exists($dir)) return true;
    if (!is_dir($dir)) return unlink($dir);
    foreach (scandir($dir) as $item) {
        if ($item == '.' || $item == '..') continue;
        if (!deleteDirectory($dir.DIRECTORY_SEPARATOR.$item)) return false;
    }
    return rmdir($dir);
}

require 'db_connect.php';
 
$db = new DB_CONNECT();

if ( isset( $_GET['del']  ) )
{
	$query = mysql_query("SELECT * FROM files WHERE id =".$_GET['del']." ");
	$num = mysql_num_rows ($query);
	if($num > 0)
	{
	$list = mysql_fetch_assoc($query);
	mysql_query("DELETE FROM files WHERE id = ".$_GET['del']."");
	deleteDirectory("./files/".$list['folder']."");
	echo " <script> alert('".$list['name']." удален!'); </script>";
		$query = "SELECT `id` FROM `files` WHERE user_id=".$_SESSION['user_id']."";
		$sql = mysql_query($query) or die(mysql_error()); 
		$_SESSION['my_files'] = mysql_num_rows($sql);
	}
	else {
	echo " <script> alert('Такой записи в базе данных не найдено'); </script>";
	}
 echo " <script>'$(\"#content\").load(\"trade_content.php?\")' </script>";
}
if ( isset($_SESSION['findText'])  ) 
{
 $findstring = $_SESSION['findText'];
 $findstring = strtoupper($findstring); 
 $findstring = strip_tags($findstring); 
 $findstring = trim ($findstring); 
 unset($_SESSION['findText']); 
 
$query = mysql_query("SELECT files.*,personal.name AS athor FROM files JOIN personal USING(user_id) WHERE files.name LIKE'%".$findstring."%'");

$num = mysql_num_rows ($query);
echo "<strong><center>Количество найденного материала:
     ".$num."</strong></center><br>";
	 
if ($num > 0)
	{}
else $msg = "<strong><center><br>Материалов не найдено!</center></strong>";

}
else{
if ( !isset( $my_files ) ) $my_files=0;
if($my_files==1 ){
 if(isset($_SESSION)){$query = mysql_query("SELECT files.*,personal.name AS athor FROM files JOIN personal USING(user_id) WHERE files.user_id=".$_SESSION['user_id']." ORDER by id DESC");
			$num = mysql_num_rows ($query);
			if ($num > 0)
			{ $title = "Мои добавления"; }
			else $msg = "<strong><center><br>У вас нету добавленных материалов.</center></strong>";	
			}else $msg = "<strong><center><br>Вы не авторизованны.</center></strong>";
}
else{
if ( isset( $_GET['cat_id'] ) ){ 
 $query = mysql_query("SELECT files.*,personal.name AS athor FROM files JOIN personal USING(user_id) WHERE files.cat_id=".$_GET['cat_id']." union SELECT files.*,'удален' FROM files WHERE files.user_id is NULL AND files.cat_id=".$_GET['cat_id']." ORDER by added DESC");
 $query2 = mysql_query("SELECT * FROM category WHERE id=".$_GET['cat_id']."");
 $list2 = mysql_fetch_assoc($query2);
 echo('<center>'.$list2['description'].'</center><br>');
}
else
{
	$query = mysql_query("SELECT files.*,personal.name AS athor FROM files JOIN personal USING(user_id) union SELECT files.*,'удален' FROM files WHERE files.user_id is NULL ORDER by added DESC");
}
$num = mysql_num_rows ($query);
if ($num > 0)
{ }
else $msg = "<strong><center><br>В данной категории нет материалов!</center></strong>";
}
}
if(isset($query)){
	echo "<strong><center>Показано материалов:
     ".$num."</strong></center><br>";
	
		echo "<table cellpadding=5 cellspacing=3 align=center width=100% style=\"font-size:13px;\">";
		echo("<tr style=\"text-align:center;font-size:17px;font-weight: bold;\" bgcolor=#82C2FF><td><td>Наименование<td>Описание<td>Добавил</tr>");
		 while($list = mysql_fetch_assoc($query))
		{    
			if($list['pic']==Null)
			{
			echo "<tr bgcolor=#EFEFEF ><td>
			<a  href='/img/product/none.jpg' onclick='return hs.expand(this)'>
			<img src='/img/product/none.jpg' width=50 height='auto' /></a></td>";
			}
			else{
			echo ("<tr bgcolor=#EFEFEF ><td>
			<a  href='/files/".$list['folder']."/".$list['pic']."' onclick='return hs.expand(this)'>
			<img src='/files/".$list['folder']."/".$list['pic']."' width=50 height='auto' /></a></td>");
			}
			echo "<td><a href='/product.php?id=".$list['id']."' onclick=\"return hs.htmlExpand(this, 
					{ objectType: 'iframe', width:600,height:700, headingText: 'Полная информация об материале' } )\" style=\"font-size:13px;\">".$list['name']."</a></td>";
			if (strlen($list['description']) > 150){
			$list['description'] = mb_substr($list['description'], 0, 150,'utf-8')."...";}
			echo ("<td>".$list['description']."</td>");
			echo "<td style=\"font-size:15px;\">".$list['athor']."<br>";

			if (isset($_SESSION['user_id'])) 
			{
			if ($_SESSION['user_flag'] == 1 || $_SESSION['user_id'] == $list['user_id'])
			echo("
					<a href=\"edit.php?id=".$list['id']."\" 
					onclick=\"return hs.htmlExpand(this, { objectType: 'iframe', width:500,height:620, headingText: 'Форма редактирования'})\" 
					title=\"Редактирование товара\">Изменить</a><br>
				<a href='#' onClick='if(confirm(\"Удалить?\")){ $(\"#content\").load(\"trade_content.php?del=".$list['id']."\")}'>Удалить</a>	
					");
			}

			echo "</td></tr>";
		}
		echo "</table>"; 
		}
echo($msg);

?> 
  
  
</p>
<p>&nbsp;</p>
</body>


</html>