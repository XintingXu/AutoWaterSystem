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
require_once("functions_calcu")

function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

$UPASS = $_POST['UPASS'];
$UNAME = $_POST['UNAME'];

$loged = true;
if(strlen((string)$UID) != 9)
	$loged = false;

	if(!$loged){
		echo "<html>
				<body>
				<form action=\"administrator.php\" method=\"post\">
				User Name: <input type=\"text\" name=\"UNAME\"><br>
				Password: <input type=\"password\" name=\"UPASS\"><br>
				<input type=\"submit\">
				</form>
				</body>
			</html>";
	}else{
		$UPASS = test_input($UPASS);
		$UNAME = test_input($UNAME);
		
		$log_checked = false;
		$table_name = NAME_OF_TABLE_USER;
		$ROWS = array("user_pass","user_id","user_regdate");
		$CONSTRAIN = "$table_name.user_name='$UNAME'";
		
		$RESULT = db_select($table_name,$ROWS,$CONSTRAIN);
		
		if((strlen((string)$RESULT[0]["user_id"]) != 0) && (strcmp((string)$RESULT[0]['user_pass'],(string)make_pass((string)$UNAME,(string)$UPASS,(string)$RESULT[0]['user_regdate'])) == 0)){
			$table_name = NAME_OF_TABLE_SENSOR;
			$ROWS = array("sensor_id","sensor_name","sensor_type","last_modified","sensor_value","sensor_status","sensor_capture");
			$CONSTRAIN = "$table_name.user_id='$UID'";
			
			$RESULT = db_select($table_name,$ROWS,$CONSTRAIN);
			
			echo "<table width='80%' border=1 align='center' cellpadding=5 cellspacing=0>";
			echo '<tr align="center"><td>编号</td><td>名称</td><td>值</td><td>修改时间</td></tr>';
			
			foreach($RESULT as $K=>$V){
				echo '<tr align="center">';
				echo "<td>$V['sensor_id']</td><td>$V['sensor_name']</td>";
				
				if($V['sensor_type'] == '1'){
					echo "<td>$V['sensor_value']</td>";
				}
				if($V['sensor_type'] == '2'){
					if($V['sensor_status'] == '1'){
						echo "<td>开</td>";
					}else{
						echo "<td>关</td>";
					}
				}
				if($V['sensor_type'] == '3'){
					$img = base64_decode($V['sensor_capture']);
					header('Content-type: image/jpg');
					echo "<br>$content<br>";
				}
				
				echo "<td>$V['last_modified']<td>";
				echo '</tr>';
			}
			
			echo '</table>';
		}else{
			$UID = "";
			$domain_name = DOMAIN_NAME;
			header("Location:http://$domain_name/administrator.php"); 
		}
	}
?>