<?php

require_once('config.php');

	//文件上传函数，通过读取配置文件的设置确定上传的方式
	//传入纯文件名，带拓展名
	function file_upload(string $file_name,$file){
		$upload_url = "";

		if(STO_SINACLOUD){//采用云存储
			;
		}else{//采用代码空间存储
			$upload_url = STO_PATH.$file_name;
			
			file_put_contents($upload_url, $img);
		}
	}

?>