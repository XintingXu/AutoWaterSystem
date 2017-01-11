<?php

//HTTP 请求的返回JSON数据

	//上传传感器数据的返回
	/*
	返回值200代表接受，运行正确
	返回值101代表用户信息错误
	返回值201代表传感器信息错误
	返回值301代表内部错误
	返回值302代表无法更新
	*/
	/*
	RID		结果代码
	SID		传感器编号
	UID		用户编号
	TIME	返回日期
	*/
	function response_upload(int $result_number,string $sensor_id,string $user_id){
		$response_datetime = date("Y-m-d H:i:s");
		
		$res_array = array("RID"=>"$result_number","SID"=>"$sensor_id",
							"UID"=>"$user_id","TIME"=>"$response_datetime");
		return json_encode($res_array);
	}
	
	
	//请求数据的返回
	/*
	包含两层JSON
	顶层包含请求的结果，返回结果的个数，返回时间，传感器编号，传感器类型
	二层包含传感器的数据
		数据编号（从0开始），数据值，数据日期
	*/
	//传入的数组是二维数组，按照二层格式
	
	/*
	返回值200代表正常处理，结果正确
	返回值101代表用户信息错误
	返回值201代表传感器信息错误
	返回值301代表内部错误
	返回值302代表无法更新
	*/
	
	/*
	RID		结果代码
	COUNT	返回结果个数（0<= COUNT <=10）
	SID		传感器编号
	STYPE	传感器类型
	TIME	返回时间
	DATA	数据组
		NUMBER	数据编号，从0开始
		VALUE	数据值
		TIME	数据上传日期
	*/
	function response_download(int $result_number,int $result_count,string $sensor_id,int $sensor_type,array $row_value_array){
		$response_datetime = date("Y-m-d H:i:s");
		
		$response_download = array("RID"=>"$result_number","COUNT"=>"$result_count",
								"SID"=>"$sensor_id","STYPE"=>"$sensor_type","TIME"=>"$response_datetime",
								"DATA"=>json_encode($row_value_array));
		
		return json_encode($response_download);
	}

?>