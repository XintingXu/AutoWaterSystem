<?php
/*
sensor_type 为3，表示图像型传感器。

图像原始数据经过BASE64编码后传输，
*/
require_once('config.php');
if(!DEBUG_MODE)
	header('Content-type: text/json; charset=UTF-8');
else
	header('Content-type: text/html; charset=UTF-8');

	//获取POST和GET的数据参数
	$sensor_id = $_GET['sensor_id'];
	if(DEBUG_MODE){
		$user_id = $_GET['user_id'];
		$user_key = $_GET['user_key'];
		$captute_img = $_GET['capture'];
	}else{
		$user_id = $_POST['user_id'];
		$user_key = $_POST['user_key'];
		//$content = $GLOBALS['HTTP_RAW_POST_DATA'];
		$captute_img = isset($GLOBALS['HTTP_RAW_POST_DATA'])? $GLOBALS['HTTP_RAW_POST_DATA'] : '';
		if(empty($captute_img)){
			$captute_img = file_get_contents('php://input');
		}
	}
	
	//状态返回值参数
	$result_number = 0;
	
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
				else{
					if(strlen($captute_img) == 0)
						$argument_error = true;
					else
						$argument_error = false;
				}
			}
		}
	}
	
	if($argument_error){
		$result_number = 101;
		
		if(DEBUG_MODE)
			echo "Please check the input arguments.<br>";
	}
	else{
		$table_user = NAME_OF_TABLE_USER;
		$table_sensor = NAME_OF_TABLE_SENSOR;
		$table_capture = NAME_OF_TABLE_CAPTURE;
		$table_log = NAME_OF_TABLE_SENSORLOG;
		
		$upload_time = date("Y-m-d H:i:s");
		
		$ROWS = array("user_pass");
		$CONSTRAIN = "$table_user.user_id='$user_id'";
		
		$RESULT = db_select($table_user,$ROWS,$CONSTRAIN);
		
		if(strcmp((string)$RESULT[0]['user_pass'],(string)$user_key) == 0){
			if(DEBUG_MODE){
				echo "User Pass Checked.Pass<br>";
			}
			
			$ROWS = array("sensor_id");
			$CONSTRAIN = "$table_sensor.sensor_id='$sensor_id' AND $table_sensor.user_id='$user_id' AND $table_sensor.sensor_type='3';";
			
			$RESULT = db_select($table_sensor,$ROWS,$CONSTRAIN);
			
			if(strcmp((string)$RESULT[0]['sensor_id'],(string)$sensor_id) == 0){
				if(DEBUG_MODE){
					echo "User ID and User Sensor checked.<br>";
				}
				
				$ROWS = array("sensor_capture"=>"$captute_img");
				$CONSTRAIN = "$table_sensor.sensor_id='$sensor_id'";
				$RESULT = db_update($table_sensor,$ROWS,$CONSTRAIN);
				
				if(!$RESULT){
					$result_number = 302;
					
					if(DEBUG_MODE)
						echo "Sensor table is not updated";
				}else{
					$ROWS = array("sensor_id"=>"$sensor_id",
					"capture_datetime"=>"$upload_time",
					"sensor_capture"=>"$captute_img");
					
					$RESULT = db_insert($table_capture,$ROWS);
					
					if(!$RESULT){
						$result_number = 301;
						
						if(DEBUG_MODE)
							echo "Sensor table is updated BUT log table is not inserted.<br>";
					}else{
						$result_number = 200;
						
						if(DEBUG_MODE)
							echo "All the data is updated.<br>";
					}
				}
			}else{
				$result_number = 201;
				
				if(DEBUG_MODE){
					echo "Please check the user_id and sensor_id.<br>";
					echo "sensor_id=$sensor_id doesn't belong to user=$user_id<br>";
				}
			}
		}else{
			$result_number = 101;
			
			if(DEBUG_MODE){
				echo "Please check the input arguments.<br>";
				echo "User Pass or User ID Error.<br>";
			}
		}
	}
	
	require_once("response_json.php");
	
	echo response_upload($result_number,$sensor_id,$user_id);
?>