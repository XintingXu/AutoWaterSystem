<?php
	//处理传感器数据请求
	
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
		data_count	//要获取的数据个数
		start_position	//开始的位置,从0开始
	
	*/
	
	//返回的参数
	/*
	RID		结果代码
	COUNT	返回结果个数（0<= COUNT <=10）
	SID		传感器编号
	STYPE	传感器类型
	TIME	返回时间
	DATA	数据组
		sensor_value,sensor_status,sensor_capture	数据值
		capture_datetime,log_datetime	数据上传日期(只针对查询多个数据时)
	*/
	
	require_once("config.php");
	$table_user = NAME_OF_TABLE_USER;
	$table_sensor = NAME_OF_TABLE_SENSOR;
	$table_capture = NAME_OF_TABLE_CAPTURE;
	$table_log = NAME_OF_TABLE_SENSORLOG;
	
if(!DEBUG_MODE)
	header('Content-type: text/json; charset=UTF-8');
	
	$sensor_id = $_GET['sensor_id'];
	$data_count = $_GET['data_count'];
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
			if($sensor_type == '0'){
				$result_number = 201;
				
				if(DEBUG_MODE)
					echo "User ID is not competiable to the Sensor ID.<br>";
			}
			else{
				if($sensor_type == '1'){
					$ROWS = array("sensor_value",);
				}
				if($sensor_type == '2'){
					$ROWS = array("sensor_status");
				}
				if($sensor_type == '3'){
					$ROWS = array("sensor_capture");
				}
				if($data_count <= '1')
					$CONSTRAIN = "$table_sensor.sensor_id='$sensor_id'";
				else
					$CONSTRAIN = "$table_capture.sensor_id='$sensor_id' ORDER BY 
								$table_capture.capture_num DESC LIMIT $start_position,$data_count";
				
				$RESULT = db_select($table_sensor,$ROWS,$CONSTRAIN);
				
				$GET_NUMBER = 0;
				foreach($RESULT as $K=>$V){
					$GET_NUMBER++;
				}
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
	$RESULT_ARRAY = array("RID"=>$result_number,"COUNT"=>$GET_NUMBER,"SID"=>$sensor_id,"STYPE"=>$sensor_type,"TIME"=>$time,
							"DATA"=>$DATA);
	echo json_encode($RESULT_ARRAY);
?>