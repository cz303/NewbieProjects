<!doctype html>
<html>
<head>
<meta charset="utf-8">
<link href="/css/trade_page_css.css" rel="stylesheet" type="text/css">
<link rel="stylesheet" href="./css/style.css?v=9"	   media="screen" type="text/css">
<link href="/jQueryAssets/jquery.ui.core.min.css" rel="stylesheet" type="text/css">
<link href="/jQueryAssets/jquery.ui.theme.min.css?v=78" rel="stylesheet" type="text/css">
<link href="/jQueryAssets/jquery.ui.accordion.min.css" rel="stylesheet" type="text/css">

<script src="/jQueryAssets/jquery-ui-1.9.2.accordion.custom.min.js" type="text/javascript"></script>


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

<script type="text/javascript"> 
jQuery(document).ready(function(){
        $(".Accordion1:first").accordion({ active: 99999 });
});
 </script>
 
 <script type="text/javascript">
function validatesearch(searchForm)
{
var errors="";
var x=searchForm.findText.value;

if (x==null || x=="" || x.length == 0 || x=="undefined")
  {
  errors+="Строка поиска пуста!\n";
  }
  
if(errors=="")
return true;
else
{
alert(errors);
return false;
}
}
</script>
 
</head>

<body onLoad='$("#content").load("trade_content.php")'>
<?php $title="Центр облачного образования";
require 'db_connect.php';
 ?>
<div></div>
<div class="colum_left"> <p align="center" style="font-size:18px; font-weight:bold;">Категории</p>
 <?php
 if (isset($_SESSION['user_id']) && $_SESSION['user_flag'] == 1) 
{
  echo("
    <div class=\"highslide-body\" align=center> 
	<a href='add_cat.php' onclick=\"return hs.htmlExpand(this, { objectType: 'iframe', width:500,height:300, headingText:'Форма добавления категории' } )\" alt=\"Добавить новый обучающий метериал\">
	<input type=\"button\" style=\"text-align: right;\" class=\"button\" title=\"Добавить новую категорию\" value=\"Добавить\"> 
	</a>
	</div>
  
  ");
  }
?>

<div id="Accordion1" class="Accordion1">
<?php
  
	$db = new DB_CONNECT();
	$query2 = mysql_query("SELECT * FROM category");
  
    while($list2 = mysql_fetch_assoc($query2))
	{
    
	echo("<h3 onClick='$(\"#content\").load(\"trade_content.php?product=");
	echo(urlencode($list2['name']));
	echo("&cat_id=");
	echo($list2['id']);
	echo("\")'>");
	echo('<a href="#" >'.$list2['name'].'</a></h3> <div>');
	
    if (isset($_SESSION['user_id']) && $_SESSION['user_flag'] == 1) echo("
	<a href=\"edit_cat.php?id=".$list2['id']."\" 
					onclick=\"return hs.htmlExpand(this, { objectType: 'iframe', width:500,height:300, headingText: 'Форма редактирования'})\" 
					>Изменить раздел</a><br><br>
	<a href=\"#\" onClick=' if(confirm(\"Удалить?\")){ $(\"#content\").load(\"del_cat.php?del=".$list2['id']."\") }'>Удалить разрел</a>");
	
	echo("</div>"); 

	
	}
	
	
?>
  </div>

</div>
<div style="clear: right;min-height: 0px;height: 0px;line-height: 0px;width: 0px;font-size: 0px;"></div> 
<div class="colum_right" >
<?php
 if (isset($_SESSION['user_id'])) 
{
  echo("
    <div class=\"highslide-body\" style=\"text-align: right;\"> 
	<a href='add.php' onclick=\"return hs.htmlExpand(this, { objectType: 'iframe', width:500,height:690, headingText:'Форма добавления материала' } )\" alt=\"Добавить новый обучающий метериал\">
	<input type=\"button\" style=\"text-align: right;\" class=\"button\" title=\"Добавить новый обуччающий материал\" value=\"Добавить\"> 
	</a>
	</div>
  
  ");
  
  		$query = "SELECT `id` FROM `files` WHERE user_id=".$_SESSION['user_id']."";
		$sql = mysql_query($query) or die(mysql_error()); 
		$_SESSION['my_files'] = mysql_num_rows($sql);	
}
?>


<form action="index.php" name="search" method="post" style="text-align: center;" onsubmit='return validatesearch(this);'>
<input type="text" name="findText" id="searchField" value="" placeholder="Поиск в облаке" style="width: 300px;">
<input class="button" type="submit" name="" alt="Найти" value="Найти" >
</form>
<br>

<div id="content" > 

Контент

</div>
</div>


<script type="text/javascript">

$(function() {
	$( "#Accordion1" ).accordion({
		heightStyle:"content"
	}); 
});
</script>

</body>
</html>