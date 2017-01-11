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
$INIT_SENSOR_TABLE = "INSERT INTO $TABLE_SENSOR (sensor_id,user_id,sensor_type,sensor_name) 
				VALUES ('200000000','100000000','0','初始传感器');";
$INIT_CAPTURE_TABLE = "INSERT INTO $TABLE_CAPTURE (capture_num,sensor_id,capture_datetime,sensor_capture)
				VALUES ('1','200000000','$ROOT_USER_REGDATE','SGVsbG8gV29ybGQ=');";
$INIT_SENSOR_LOG = "INSERT INTO $TABLE_LOG (log_num,sensor_id,sensor_value,log_datetime) 
				VALUES ('1','200000000','0','$ROOT_USER_REGDATE');";

//删除所有表
$DELETE_TABLE = "DROP TABLE $TABLE_CAPTURE;DROP TABLE $TABLE_LOG;DROP TABLE $TABLE_SENSOR;DROP TABLE $TABLE_USER;";

				
//创建表
$CREATE_TABLE_USER = "CREATE TABLE IF NOT EXISTS `user_info` (
  `user_id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '用户的ID标识，自增，从100000000开始',
  `user_name` varchar(50) NOT NULL COMMENT '用户名',
  `user_pass` varchar(255) NOT NULL COMMENT '加密后的密文',
  `user_regdate` datetime NOT NULL COMMENT '用户的注册时间，用于和用户名生成盐',
  PRIMARY KEY (`user_id`),
  UNIQUE KEY `user_id` (`user_id`),
  KEY `user_pass` (`user_pass`)
) AUTO_INCREMENT=100000000 DEFAULT CHARSET=utf8 COMMENT='用户信息存储表，用于身份验证';";

$CREATE_TABLE_SENSOR = "CREATE TABLE IF NOT EXISTS `sensor_info` (
  `sensor_id` int(11) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '传感器编号，自增，从200000000开始',
  `user_id` int(11) UNSIGNED NOT NULL COMMENT '传感器所属的用户ID',
  `sensor_name` varchar(40) DEFAULT NULL COMMENT '传感器的名称',
  `sensor_type` int(4) UNSIGNED NOT NULL DEFAULT '0' COMMENT '传感器类型，1表示数值型，2表示开关型，3表示图像型',
  `last_modified` datetime NOT NULL COMMENT '上次修改时间',
  `sensor_value` int(5) NOT NULL DEFAULT '0' COMMENT '传感器数值，默认0，只针对1-数值型',
  `sensor_status` int(1) UNSIGNED NOT NULL DEFAULT '0' COMMENT '传感器状态，默认0，只针对2-开关型，1表示开',
  `sensor_capture` longtext COMMENT '传感器捕获的图片文件，默认为空',
  PRIMARY KEY (`sensor_id`),
  UNIQUE KEY `sensor_id` (`sensor_id`),
  KEY `user_id` (`user_id`)
)AUTO_INCREMENT=200000005 DEFAULT CHARSET=utf8 COMMENT='传感器信息定义表';";

$CREATE_TABLE_LOG = "CREATE TABLE IF NOT EXISTS `sensor_log` (
  `log_num` int(11) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '顺序编号，从1开始',
  `sensor_id` int(11) UNSIGNED NOT NULL COMMENT '传感器编号，不为空，外键',
  `sensor_value` int(1) UNSIGNED NOT NULL COMMENT '传感器数值，数值型与开关型统一记录',
  `log_datetime` datetime NOT NULL COMMENT '传感器数据上传日期时间',
  PRIMARY KEY (`log_num`),
  KEY `sensor_id` (`sensor_id`)
)AUTO_INCREMENT=32 DEFAULT CHARSET=utf8 COMMENT='传感器数据历史记录表';";

$CREATE_TABLE_CAPTURE = "CREATE TABLE IF NOT EXISTS `capture_info` (
  `capture_num` int(11) UNSIGNED NOT NULL AUTO_INCREMENT COMMENT '捕获的顺序编号，从1开始自增编号',
  `sensor_id` int(11) UNSIGNED NOT NULL COMMENT '传感器的编号，和sensor_info表对应',
  `capture_datetime` datetime NOT NULL COMMENT '图片的捕获时间',
  `sensor_capture` longtext NOT NULL COMMENT '传感器捕获的图片文件(BASE64编码)，默认非空',
  PRIMARY KEY (`capture_num`),
  UNIQUE KEY `capture_num` (`capture_num`),
  KEY `sensor_id` (`sensor_id`)
)AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;";

$CREATE_TABLE_KEYS = "ALTER TABLE `capture_info`
  ADD CONSTRAINT `sensor_constrain` FOREIGN KEY (`sensor_id`) REFERENCES `sensor_info` (`sensor_id`) ON DELETE CASCADE ON UPDATE CASCADE;
  ALTER TABLE `sensor_info`
  ADD CONSTRAINT `user_constrains` FOREIGN KEY (`user_id`) REFERENCES `user_info` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE;
  ALTER TABLE `sensor_log`
  ADD CONSTRAINT `sensor_id` FOREIGN KEY (`sensor_id`) REFERENCES `sensor_info` (`sensor_id`) ON DELETE CASCADE ON UPDATE CASCADE";

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
	$result = mysqli_query($conn,$DELETE_TABLE);
	$result = mysqli_query($conn,$CREATE_TABLE_USER);
	$result = mysqli_query($conn,$CREATE_TABLE_SENSOR);
	$result = mysqli_query($conn,$CREATE_TABLE_LOG);
	$result = mysqli_query($conn,$CREATE_TABLE_CAPTURE);
	$result = mysqli_query($conn,$CREATE_TABLE_KEYS);
	
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

sleep(2);
$domain_name = DOMAIN_NAME;
header("Location:http://$domain_name/"); 
exit;
?>
