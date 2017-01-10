<?php
/*
对数据库进行初始化；
*/

//引入配置文件
require_once('config.php');
require_once('functions_calcu.php');

//引入参数
$ROOT_USERD_ID = ROOT_USED_ID;
$ROOT_USER_NAME = ROOT_USED_NAME;
$ROOT_USER_PASSWORD = ROOT_USED_PASS;

$ROOT_USER_REGDATE = date("Y-m-d H:i:s");
if(DEBUG_MODE)
	echo $ROOT_USER_REGDATE;echo "<br>";

//计算密码
$PASS = make_pass($ROOT_USER_NAME,$ROOT_USER_REGDATE,$ROOT_USER_PASSWORD);

//引入表名
$TABLE_USER = NAME_OF_TABLE_USER;
if(DEBUG_MODE){
	echo '$TABLE_USER = ';
	echo $TABLE_USER;
	echo "<br>";
}

$TABLE_SENSOR = NAME_OF_TABLE_SENSOR;
$TABLE_CAPTURE = NAME_OF_TABLE_CAPTURE;
$TABLE_LOG = NAME_OF_TABLE_SENSORLOG;

//初始化SQL语句
$INIT_USER_TABLE = "INSERT INTO $TABLE_USER (user_id,user_name,user_pass,user_regdate) 
				VALUES ('$ROOT_USERD_ID','$ROOT_USER_NAME','$PASS','$ROOT_USER_REGDATE');";
$INIT_SENSOR_TABLE = "INSERT INTO $TABLE_SENSOR (sensor_id,user_id,sensor_type) 
				VALUES ('200000000','100000000','0');";
$INIT_CAPTURE_TABLE = "INSERT INTO $TABLE_CAPTURE (capture_num,sensor_id,capture_datetime,sensor_capture)
				VALUES ('1','200000000',$ROOT_USER_REGDATE,'');";
$INIT_SENSOR_LOG = "INSERT INTO $TABLE_LOG (log_num,sensor_id,sensor_value,log_datetime) 
				VALUES ('1','200000000','0','$ROOT_USER_REGDATE');";

//初始化清空表
$CLEAR_TABLE = "DELETE FROM $TABLE_USER;
				DELETE FROM $TABLE_SENSOR;
				DELETE FROM $TABLE_CAPTURE;
				DELETE FROM $TABLE_LOG;";

//建立连接
$conn = mysqli_connect(DATA_HOST_M,DATA_HOST_USER,DATA_HOST_PASS,DATA_HOST_DBNAME);

//连接情况判断
if(!$conn){
	if(DEBUG_MODE)
		echo "Connection to Server Error.";echo mysqli_connect_error();echo "<br>";

	echo "Connection to Data Server Error.";
}else{
	if(DEBUG_MODE)
		echo "Connection established.";echo "<br>";
	
	//判断清空结果
	$result = mysqli_query($conn,$CLEAR_TABLE);
	
	if(DEBUG_MODE){
		echo '$CLEAR_TABLE = '; echo $CLEAR_TABLE; echo "<br>";
		echo '$result = ';echo $result;echo "<br>";
	}
	
	//判断USER表初始化结果
	$result1 = mysqli_query($conn,$INIT_USER_TABLE);
	
	if(DEBUG_MODE){
		echo '$INIT_USER_TABLE = '; echo $INIT_USER_TABLE; echo "<br>";
		echo '$result = ';echo $result;echo "<br>";
	}
	
	//判断SENSOR表初始化结果
	$result2 = mysqli_query($conn,$INIT_SENSOR_TABLE);
	
	if(DEBUG_MODE){
		echo '$INIT_SENSOR_TABLE = '; echo $INIT_SENSOR_TABLE; echo "<br>";
		echo '$result = ';echo $result;echo "<br>";
	}
	
	//判断CAPTURE表初始化结果
	$result3 = mysqli_query($conn,$INIT_CAPTURE_TABLE);
	
	if(DEBUG_MODE){
		echo '$INIT_CAPTURE_TABLE = '; echo $INIT_CAPTURE_TABLE; echo "<br>";
		echo '$result = ';echo $result;echo "<br>";
	}
	
	//判断LOG表初始化结果
	$result4 = mysqli_query($conn,$INIT_SENSOR_LOG);
	
	if(DEBUG_MODE){
		echo "\$INIT_SENSOR_LOG = $INIT_SENSOR_LOG<br>";
		echo "\$result4 = $result4<br>";
	}
	
	//判断各个操作结果
	if($result1 && $result2 && $result3 && $result4)
		echo "Done<br>";
	else
		echo "Something ERROR happened.Please retray.<br>";
}
//关闭连接
mysqli_close($conn);

//跳转回主页
echo "Jump to the Index in 5 seconds.<br>";
sleep(5);

$domain_name = DOMAIN_NAME;
header("Location:http://$domain_name/"); 
exit;
?>
