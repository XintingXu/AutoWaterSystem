<?php
/*
sensor_type 为1，表示数值型传感器。
*/
require_once('config.php');

if(!DEBUG_MODE)
	header('Content-type: text/json; charset=UTF-8');
	//获取POST和GET的数据参数
	
	$sensor_id = $_GET['sensor_id'];
	$sensor_value = $_GET['sensor_value'];
	if(DEBUG_MODE){
		$user_id = $_GET['user_id'];
		$user_key = $_GET['user_key'];
	}else{
		$user_id = $_POST['user_id'];
		$user_key = $_POST['user_key'];
	}
	
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
	
	$result_number = 0;
	
	if($argument_error){
		$result_number = 101;
		
		if(DEBUG_MODE)
			echo "Please check the input arguments.<br>";
		else
			;
	}
	else{
		$table_user = NAME_OF_TABLE_USER;
		$table_sensor = NAME_OF_TABLE_SENSOR;
		$table_capture = NAME_OF_TABLE_CAPTURE;
		$table_log = NAME_OF_TABLE_SENSORLOG;
		
		$upload_time = date("Y-m-d H:i:s");
		
		$ROWS = array("user_pass");
		$CONSTRAIN = "$table_user.user_id=$user_id";
		
		$RESULT = db_select($table_user,$ROWS,$CONSTRAIN);
		
		if(strcmp((string)$RESULT[0]['user_pass'],(string)$user_key) == 0){
			$ROWS_sensor_info = array("sensor_value"=>$sensor_value);
			$ROWS_sensor_log = array("sensor_id"=>$sensor_id,"sensor_value"=>$sensor_value,
			"log_datetime"=>$upload_time);
			
			$RESULT = db_update($table_sensor,$ROWS_sensor_info,
				"$table_sensor.sensor_id='$sensor_id' AND $table_sensor.user_id='$user_id' AND $table_sensor.sensor_type='1'");
				
			if(DEBUG_MODE){
				echo "UPDATE Sensor \$RESULT = $RESULT<br>";
			}
			
			if(!$RESULT){
				$result_number = 302;
				
				if(DEBUG_MODE){
					echo "Cannot update sensor info.<br>";
				}
			}else{
				$RESULT = db_insert($table_log,$ROWS_sensor_log);
				if(!$RESULT){
					$result_number = 301;
					
					if(DEBUG_MODE){
						echo "Sensor is updated but cannot write log.<br>";
					}
				}else{
					$result_number = 200;
					
					if(DEBUG_MODE){
						echo "All the informations are updated.<br>";
					}
				}
			}
		}else{
			$result_number = 101;
			if(DEBUG_MODE){
				echo "User Pass or User ID Error.<br>";
				echo "Please check the input arguments.<br>";
			}
		}
	}
	
	require_once("response_json.php");
	
	echo response_upload($result_number,$sensor_id,$user_id);
?>