<html>
	<head>
		<meta http-equiv="content-type" content="text/html; charset=UTF-8">
		<title>
			Please Log in
		</title>
	</head>
	
	<body>
		<form action="login.php" method="post">
			Name: <input type="text" name="UNAME"><br>
			Password: <input type="password" name="UPASS"><br>
			<input type="submit" value="登陆">
		</form>
	</body>
</html>

<?php
	require_once("config.php");
	require_once("functions_db.php");
	require_once("functions_calcu.php");
	
	function test_input($data) {
		$data = trim($data);
		$data = stripslashes($data);
		$data = htmlspecialchars($data);
		return $data;
	}
	
	$UNAME = $_POST['UNAME'];
	$UPASS = $_POST['UPASS'];
	
	if(strlen($UNAME) == 0 || strlen($UNAME) == 0){
		echo "Please input the information<br>";
	}else{
		$UNAME = test_input($UNAME);
		$UPASS = test_input($UPASS);
		
		$table_name = NAME_OF_TABLE_USER;
		$ROWS = array("user_id","user_pass","user_regdate");
		$CONSTRAIN = "$table_name.user_name='$UNAME'";
		
		$RESULT = db_select($table_name,$ROWS,$CONSTRAIN);
		
		if(strlen($RESULT[0]['user_id']) != 9){
			echo "Please check the user name.<br>";
		}else{
			$pass_calcu = make_pass($UNAME,$RESULT[0]['user_regdate'],$UPASS);
			if(DEBUG_MODE)
				echo "pass_calcu = '$pass_calcu'<br>";
			if(strcmp($RESULT[0]['user_pass'],$pass_calcu) == 0){
				setcookie("UNAME",$UNAME,time()+600);
				setcookie("UID",$RESULT[0]['user_id'],time()+600);
				setcookie("UPASS",$RESULT[0]['user_pass'],time()+600);
				
				$domain_name = DOMAIN_NAME;
				header("Location:http://$domain_name/administrator.php");
			}else{
				echo "Please check the password.<br>";
			}
		}
	}
?>