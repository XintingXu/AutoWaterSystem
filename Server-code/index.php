<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>The Auto Water System</title>
	</head>
	
	<body>
		<h2>
			The Auto Water System
		</h2>
		
		<p>
			This project is designed to build a system that can be used to water flowers through Enthernet control.<br>
			It contains three parts,the server side built of PHP,the control board based on RaspberryPI 3 Model B and the client designed by QT.<br>
			Three kinds of sensors are designed,including switch,picture and figure.<br>
			To use the system,you should regist and config the sensors.After that,you can modify the control board to connect to the server.No recast is needed of the client.<br>
		</p>

		
<?php

/*
判断数据库是否初始化过，如果已经初始化，不跳转，否则提示跳转到初始化界面
*/

	require_once('config.php');
	
	if(DEBUG_MODE)
		echo "This is the test part.<br>";
	
	$conn = mysqli_connect(DATA_HOST_M,DATA_HOST_USER,DATA_HOST_PASS,DATA_HOST_DBNAME);
	mysqli_set_charset($conn, "utf8");
		
	if(!$conn){
		echo "Cannot connect to data server.Please check your config.<br>";
		if(DEBUG_MODE){
			echo mysqli_connect_error();
			echo "<br>";
		}
	}
	else{
		$table_user = NAME_OF_TABLE_USER;
		$table_sensor = NAME_OF_TABLE_SENSOR;
		$table_capture = NAME_OF_TABLE_CAPTURE;
		$table_log = NAME_OF_TABLE_SENSORLOG;
		
		//判断数据库中是否已经存在初始化记录
		$check = "SELECT COUNT($table_user.user_id) FROM $table_user WHERE $table_user.user_id='100000000';";
		mysqli_set_charset($conn, "utf8");
		$result_user = mysqli_query($conn,$check);
		
		$check = "SELECT COUNT($table_sensor.sensor_id) FROM $table_sensor WHERE $table_sensor.sensor_id='200000000';";
		mysqli_set_charset($conn, "utf8");
		$result_sensor = mysqli_query($conn,$check);
		
		$check = "SELECT COUNT($table_capture.capture_num) FROM $table_capture WHERE $table_capture.capture_num='1';";
		mysqli_set_charset($conn, "utf8");
		$result_capture = mysqli_query($conn,$check);
		
		$check = "SELECT COUNT($table_log.log_num) FROM $table_log WHERE $table_log.log_num='1';";
		mysqli_set_charset($conn, "utf8");
		$result_log = mysqli_query($conn,$check);
		
		//如果返回值中存在FALSE
		if(!$result_user || !$result_sensor || !$result_capture || !$result_log){
			if(DEBUG_MODE)
				echo "Init Check Failed.<br>";
			echo "Please turn to the <a href = \"init.php\">Init page.</a><br>";
			mysqli_close($conn);
			$domain_name = DOMAIN_NAME;
			sleep(2);
			header("Location:http://$domain_name/init.php");
			exit;
		}
		else{//返回值需要进一步判断
			$checkPass = false;
			if($result_user instanceof mysqli_result && $result_sensor instanceof mysqli_result && $result_capture instanceof mysqli_result 
				&& $result_log instanceof mysqli_result){//如果返回值是可读的数据类型
				//将返回的数据格式化为数组
				$result1 = $result_user->fetch_array();
				$result2 = $result_sensor->fetch_array();
				$result3 = $result_capture->fetch_array();
				$result4 = $result_log->fetch_array();
				
				//判断，如果数据库中是否存在一个未初始化的表
				if($result1[0] == '0' || $result2[0] == '0' || $result3[0] == '0' || $result4[0] == '0'){
					$checkPass = false;
				}
				
				//判断是否已经全部初始化
				if($result1[0] == '1' && $result2[0] == '1' && $result3[0] == '1' && $result4[0] == '1')
					$checkPass = true;
			}
			if(!$checkPass){//判断结果的处理，跳转到初始化页面
				if(DEBUG_MODE)
					echo "Init Check Failed.<br>";
				echo "Please turn to the <a href = \"init.php\">Init page.</a>";
				mysqli_close($conn);
			}
			else{
				echo "Init check done.<br>";
			}
		}
		
		//释放返回值空间
		mysqli_free_result($result_user);
		mysqli_free_result($result_sensor);
		mysqli_free_result($result_capture);
		mysqli_free_result($result_log);
	}
	
	//关闭连接
	mysqli_close($conn);
?>
		
		<p>
			designed and modified by XuXinting.<br>
			Copyright©<?php echo date("Y"); ?>
		</p>
		
		<p><a href = "administrator.php">LogIn</a></p>
	</body>
	
</html>