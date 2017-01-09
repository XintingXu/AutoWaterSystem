<?php

/*
纯计算的函数
*/

	//存储密码计算方法
	function make_pass($user_name,$user_regdate,$user_password){
		$salt = SHA1((string)$user_name.(string)$user_regdate);
		$pass = SHA1($salt.(string)$user_password.$salt);
		$pass = SHA1($salt.$pass);
		return $pass;
	}

?>