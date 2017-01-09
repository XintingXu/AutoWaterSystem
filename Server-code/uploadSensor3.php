<?php
/*
sensor_type 为3，表示图像型传感器。

图像原始数据经过BASE64编码后传输，
*/

header('Content-type: text/json; charset=UTF-8');

$base64 = $_POST["image"]; // 得到文件参数
$img = base64_decode($base64); // 将格式为base64的字符串解码

//$path = "md5(uniqid(rand()))".".jpg"; // 产生随机唯一的名字作为文件名
//file_put_contents($path, $img); // 将图片保存到相应位置

	//获取POST和GET的数据参数
	$sensor_id = $_GET['sensor_id'];
	if(DEBUG_MODE){
		$user_id = $_GET['user_id'];
		$user_key = $_GET['user_key'];
	}else{
		$user_id = $_POST['user_id'];
		$user_key = $_POST['user_key'];
	}
	
	require_once('config.php');
	require_once('functions_db.php');
	
	//进行参数判断
	$argument_error = true;
	if(!$sensor_id || !$user_id || !$user_key){
		$argument_error = true;
	}else{
		if(!($sensor_id <= 299999999 && $sensor_id >= 200000000)){
			$argument_error = true;
		}
		else{
			if(!($user_id <= 199999999 && $user_id >= 100000000))
				$argument_error = true;
			else{
				if(strlen($user_key) != 40)
					$argument_error = true;
				else
					$argument_error = false;
			}
		}
	}
	
	if($argument_error)
		echo "Please check the input arguments.<br>";
	else{
		$table_user = NAME_OF_TABLE_USER;
		$table_sensor = NAME_OF_TABLE_SENSOR;
		$table_capture = NAME_OF_TABLE_CAPTURE;
		$table_log = NAME_OF_TABLE_SENSORLOG;
		
		$upload_time = date("Y-m-d H:i:s");
		
		$ROWS = array("user_pass");
		$CONSTRAIN = "$table_user.user_id=$user_id";
		
		$RESULT = db_select($table_user,$ROWS,$CONSTRAIN);
		
		if(strcmp($RESULT[0],$user_key) == 0){
			require_once('functions_file.php');
			$file_name = (string)$sensor_id.(string)$upload_time.".jpg";
			function file_upload($file_name,$img);
		}else{
			echo "Please check the input arguments.<br>";
			if(DEBUG_MODE){
				echo "User Pass or User ID Error.<br>";
			}
		}
	}
?>