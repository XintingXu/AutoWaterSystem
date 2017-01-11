<?php
	//处理传感器数据请求
	//仅处理3型（图片传感器），每次返回一个，可以指定位置顺序（逆序）
	
	/*
	返回值200代表正常处理，结果正确
	返回值101代表用户信息错误
	返回值201代表传感器信息错误
	返回值301代表内部错误
	*/
	
	//传入的参数
	/*
	POST:
		user_id		//用户ID号
		user_pass	//用户密码
	
	GET:
		sensor_id	//传感器ID
		start_position	//开始的位置,从0开始
	
	*/
	
	//返回的参数
	/*
	RID		结果代码
	SID		传感器编号
	TIME	返回时间
	DATA	数据组
		sensor_capture	数据值
		capture_datetime	数据上传日期
	*/
	
	require_once("config.php");
	$table_user = NAME_OF_TABLE_USER;
	$table_sensor = NAME_OF_TABLE_SENSOR;
	$table_capture = NAME_OF_TABLE_CAPTURE;
	
if(!DEBUG_MODE)
	header('Content-type: text/json; charset=UTF-8');
	
	$sensor_id = $_GET['sensor_id'];
	$start_position = $_GET['start_position'];
	$sensor_type = 0;
	
	if(DEBUG_MODE){
		$user_id = $_GET['user_id'];
		$user_pass = $_GET['user_pass'];
	}else{
		$user_id = $_POST['user_id'];
		$user_pass = $_POST['user_pass'];
	}
	
	$result_number = 0;
	
	$argument_error = true;
	if($sensor_id < 200000000 || $sensor_id >= 300000000 || $user_id < 100000000 || $user_id >= 200000000 || strlen($user_pass) != 40){
		$result_number = 101;
		
		if(DEBUG_MODE){
			echo "Please check the arguments.<br>";
		}
	}else{
		require_once("functions_db.php");
		
		$ROWS = array("user_pass");
		$CONSTRAIN = "$table_user.user_id='$user_id'";
		
		$RESULT = db_select($table_user,$ROWS,$CONSTRAIN);
		
		if(strcmp((string)$RESULT[0]['user_pass'],(string)$user_pass) == 0){
			$ROWS = array("sensor_type");
			$CONSTRAIN = "$table_sensor.sensor_id='$sensor_id' AND $table_sensor.user_id='$user_id'";
				
			$RESULT = db_select($table_sensor,$ROWS,$CONSTRAIN);
			
			$sensor_type = $RESULT[0]['sensor_type'];
			if($sensor_type != '3'){
				$result_number = 201;
				
				if(DEBUG_MODE)
					echo "User ID is not competiable to the Sensor ID.<br>";
			}
			else{
				$ROWS = array("sensor_capture","capture_datetime")
				$CONSTRAIN = "$table_capture.sensor_id='$sensor_id' ORDER BY 
							$table_capture.capture_num DESC LIMIT $start_position,$data_count";
				$table_name = $table_capture;
				
				$RESULT = db_select($table_name,$ROWS,$CONSTRAIN);
				$DATA = json_encode($RESULT[0]);
				$result_number = 200;
			}
		}else{
			$result_number = 101;
			
			if(DEBUG_MODE){
				echo "User Pass Error.<br>";
			}
		}
	}
	
	$DATA = json_encode($DATA);
	$time = date("Y-m-d H:i:s");
	$RESULT_ARRAY = array("RID"=>$result_number,"SID"=>$sensor_id,"TIME"=>$time,
							"DATA"=>$DATA);
	echo json_encode($RESULT_ARRAY);
?>