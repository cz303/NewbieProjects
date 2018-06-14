<?php

session_start();
$percent = 0;
$data = array();

if(isset($_SESSION['upload_progress_test']) and is_array($_SESSION['upload_progress_test'])) {
    $percent = ($_SESSION['upload_progress_test']['bytes_processed'] * 100 ) / $_SESSION['upload_progress_test']['content_length'];
    $percent = round($percent,2);
    $data = array(
         'percent' => $percent,
         'content_length' => $_SESSION['upload_progress_test']['content_length'],
         'bytes_processed' => $_SESSION['upload_progress_test']['bytes_processed']
  );
}
echo json_encode($data);
?>