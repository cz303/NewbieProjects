<!doctype html>
<html>
<head>
<meta charset="utf-8">
</head>

<body>


  <?php
$title="Карта сайта";
require 'db_connect.php';
$db = new DB_CONNECT();
?>
  

<div style="margin-left: 150px; width: 300; line-height: 25px;">
Главная
  <ul>
	    <li ><a href="index.php?content=hello">Новости</a></li>
        <li ><a href="index.php?content=trade">Обучающие материалы</a></li>
        <li ><a href="index.php?content=map">Карта сайта</a></li>
        <li ><a href="index.php?content=about">О нас</a></li>
        <li ><a href="index.php?content=callback">Обратная связь</a></li>
  </ul>
EduCloud
  <ul>
  <?php
  $query2 = mysql_query("SELECT * FROM category");
  
	while($list2 = mysql_fetch_assoc($query2))
	{
	echo('<li ><a href="trade_content.php?product='.$list2['name'].'&cat_id='.$list2['id'].'">Раздел "'.$list2['name'].'"</a></li>');
	}
	
  ?>
  </ul>
    
 </div>
</body>




</html>
