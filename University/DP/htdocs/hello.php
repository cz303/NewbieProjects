<!doctype html>
<html>
<head>
<meta charset="utf-8">
</head>

<body>
<?php
$title="EDUCLOUD - облачное образование";
?>

<p>
<h3><center>Добро пожаловать!</center></h3>
<?php
if ($_POST)
{
	$filename = './news.txt';
	$contents = $_POST['html'];
	if ( is_writable($filename) ) {
	  $r = fopen($filename, 'w');
	  if ( $r ) {
		fwrite($r, $contents);
		fclose($r);
	  }
	}
header('Location: index.php?content=hello');	
}

require 'db_connect.php';
$db = new DB_CONNECT();
$query = mysql_query("SELECT files.* FROM files ORDER by added DESC");
$num = mysql_num_rows ($query); $max_count=0;
if ($num > 0)
{ 
echo('Последние добавленные материалы:<dd style="font-size:11pt">');

		 while($list = mysql_fetch_assoc($query))
		{
			if($max_count<5){
			echo ($list['added'].' &nbsp;&nbsp;&nbsp;'.$list['name'].'<br>');	
			$max_count++; }
		}

echo '</dd><br><br>';
}

echo('<h3><center>Новости</center></h3><hr>');

$contents = '';
$r = fopen("./news.txt", "r");
if ( $r ) {
  while ( !feof($r) ) {
    $contents.= fread($r, 8192);
  }
  fclose($r);
}
echo $contents;

if (isset($_SESSION['user_id']) && $_SESSION['user_flag'] == 1) 
	{
		echo("<form name=\"edit\"  id=\"edit\" method=\"post\" action=\"./hello.php\" >
               <textarea type=\"text\" name=\"html\" 
			   style=\"width: 100%; height: 400px; margin-left: 15px; margin-right: 15px;\">".$contents."</textarea>
              <p style=\"text-align: center;\">
                <input type=\"submit\" name=\"edit_btm\"   value=\"Изменить новости\" 
                onclick = \"this.style.visibility='hidden'\" />
            </form>
            ");		
	}

?>


</body>

</html>

