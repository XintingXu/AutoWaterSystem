<?php
/*
进行项目管理，网页版

只有限定的初始管理员可以进行用户的操作；
用户可以对自己的传感器进行操作
*/

/*
POST
	UPASS	用户密码
	UID		用户ID
	UNAME	用户名
*/

header('Content-type: text/html; charset=UTF-8');

require_once("config.php");
require_once("functions_db.php");
require_once("functions_calcu.php");

function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

$UPASS = $_COOKIE['UPASS'];
if(DEBUG_MODE)
	echo "UPASS = $UPASS<br>";
$UNAME = $_COOKIE['UNAME'];
if(DEBUG_MODE)
	echo "UNAME = $UNAME<br>";
$UID = $_COOKIE['UID'];
if(DEBUG_MODE)
	echo "UID = $UID<br>";

	$loged = true;
	if(strlen($UID) != 9)
		$loged = false;

	if(!$loged){
		$domain_name = DOMAIN_NAME;
		header("Location:http://$domain_name/login.php"); 
		exit;
	}else{
		$UPASS = test_input($UPASS);
		if(DEBUG_MODE)
			echo "UPASS = $UPASS<br>";
		$UNAME = test_input($UNAME);
		if(DEBUG_MODE)
			echo "UPASS = $UPASS<br>";
		
		$log_checked = false;
		$table_name = NAME_OF_TABLE_USER;
		$ROWS = array("user_pass","user_id","user_regdate");
		$CONSTRAIN = "$table_name.user_name='$UNAME'";
		
		$RESULT = db_select($table_name,$ROWS,$CONSTRAIN);
		
		if((strlen((string)$RESULT[0]["user_id"]) != 0) && (strcmp((string)$RESULT[0]["user_pass"],$UPASS) == 0)){
			$table_name = NAME_OF_TABLE_SENSOR;
			$ROWS = array("sensor_id","sensor_name","sensor_type","last_modified","sensor_value","sensor_status","sensor_capture");
			$CONSTRAIN = "$table_name.user_id='$UID'";
			
			$RESULT = db_select($table_name,$ROWS,$CONSTRAIN);
			
			echo "<table width='80%' border=1 align='center' cellpadding=5 cellspacing=0>";
			echo '<tr align="center"><td>编号</td><td>名称</td><td>值</td><td>修改时间</td></tr>';

			foreach($RESULT as $K=>$V){
				echo '<tr align="center">';
				foreach($V as $x=>$x_value){
					if($x == 'sensor_id')
						$sensor_id = $x_value;
					if($x == 'sensor_name')
						$sensor_name = $x_value;
					if($x == 'sensor_type')
						$sensor_type = $x_value;
					if($x == 'sensor_value')
						$sensor_value = $x_value;
					if($x == 'sensor_status')
						$sensor_status = $x_value;
					if($x == 'sensor_capture')
						$sensor_capture = $x_value;
					if($x == 'last_modified')
						$last_modified = $x_value;
					echo "$x=>$x_value<br>";
				}

				echo '<tr align="center">';
				echo "<td>$sensor_id</td><td>$sensor_name</td>";
				
				if($sensor_type == '1'){
					echo "<td>$sensor_value</td>";
				}
				if($sensor_type == '2'){
					if($sensor_status == '1'){
						echo "<td>开</td>";
					}else{
						echo "<td>关</td>";
					}
				}
				if($sensor_type == '3'){
					$img = base64_decode($sensor_capture);
					header('Content-type: image/jpg');
					echo "<td>$img</td>";
				}
				if($sensor_type == '0'){
					echo "<td>NULL</td>";
				}
				
				echo "<td>$last_modified</td>";
				echo '</tr>';
			}
			echo '</table>';
		}else{
			$UID = "";
			setcookie("UNAME","",time()-100);
			setcookie("UPASS","",time()-100);
			setcookie("UID","",time()-100);
			$domain_name = DOMAIN_NAME;
			header("Location:http://$domain_name/login.php"); 
		}
	}
?>