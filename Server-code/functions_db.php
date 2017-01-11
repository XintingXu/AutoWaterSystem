<?php
/*
数据库操作函数
*/
require_once('config.php');

	//数据库连接函数，返回一个连接，如果连接失败，Debug模式下显示错误信息；正确则返回一个连接
	//参数$MAIN_OR_SLAVE指示连接的是主库还是从库，主库可读写，从库只能读
	//0表示主库，1表示从库
	function db_connect(int $MAIN_OR_SLAVE){
		if(!$MAIN_OR_SLAVE)
			$conn = mysqli_connect(DATA_HOST_M,DATA_HOST_USER,DATA_HOST_PASS,DATA_HOST_DBNAME);
		else
			$conn = mysqli_connect(DATA_HOST_S,DATA_HOST_USER,DATA_HOST_PASS,DATA_HOST_DBNAME);
		
		if(!$conn){
			if(DEBUG_MODE)
				echo "Cannot Connect to data server.".$mysqli_connect_error()."<br>";
			
			return false;
		}else{
			mysqli_set_charset($conn, "utf8");
			return $conn;
		}
	}

	//数据库数据插入函数
	//参数1是数据表的名，参数2是字段、值的关联数组
	//返回值是true 或 false
	function db_insert(string $table_name,array $rows_data_array){
		$rows = "";
		$values = "";
		$i = 0;
		foreach($rows_data_array as $x=>$x_value) {//进行K-V到字符串的转换
			if($i == 0){
				$rows = "$x";
				$values = "'$x_value'";
			}else{
				$rows = $rows.","."$x";
				$values = $values.","."'$x_value'";
			}
			$i++;
		}
		
		$sql = "INSERT INTO $table_name ($rows) VALUES ($values);";
		
		if(DEBUG_MODE){
			echo $sql."<br>";
		}
		
		$conn = db_connect(0);//连接主库进行插入
		
		if($conn){
			mysqli_set_charset($conn, "utf8");
			$result = mysqli_query($conn,$sql);
			mysqli_close($conn);
			return $result;
		}else{
			mysqli_close($conn);
			return false;
		}
	}
	
	//从数据表中查询数据，参数为表名、约束条件(不带WHERE)
	//返回字段、值的关联的二维数组或者false
	function db_select(string $table_name,array $rows,string $constrain){
		$string_rows = "";
		$i = 0;
		foreach($rows as $row){
			if($i == 0){
				$string_rows = $table_name.".".$row;
			}else{
				$string_rows .= ",".$table_name.".".$row;
			}
			$i++;
		}
		
		$sql = "SELECT $string_rows FROM $table_name WHERE $constrain;";
		
		if(DEBUG_MODE)
			echo $sql."<br>";
		
		$conn = db_connect(1);//连接从库进行查询
		
		if(!$conn){
			mysqli_close($conn);
			return false;
		}else{
			mysqli_set_charset($conn, "utf8");
			$result = mysqli_query($conn,$sql);
			while($row = mysqli_fetch_array($result,MYSQLI_ASSOC)){//将结果集转换为二维数组,内层数组按照列名索引
				$result_array[] = $row;
			}
			mysqli_free_result($result);
			mysqli_close($conn);
			return $result_array;
		}
	}
	
	
	//更新数据表
	//参数包括表名、要修改数据的K-V值数组，约束条件字符串(不带WHERE)
	//返回值是影响的行数
	function db_update(string $table_name,array $rows_data_array,string $constrain){
		$sql = "UPDATE $table_name SET ";
		
		$i = 0;
		foreach($rows_data_array as $x=>$x_value) {//进行K-V到字符串的转换
			if($i == 0){
				$sql = $sql.$table_name.".".$x."="."'".$x_value."'";
			}else{
				$sql = $sql.",".$table_name.".".$x."="."'".$x_value."'";
			}
			$i++;
		}
		
		$sql .= " WHERE $constrain;";
		
		if(DEBUG_MODE){
			echo $sql."<br>";
		}
		
		$conn = db_connect(0);//连接主库进行更新
		
		if(!$conn){
			mysqli_close($conn);
			return false;
		}else{
			mysqli_set_charset($conn, "utf8");
			$result = mysqli_query($conn,$sql);
			mysqli_set_charset($conn, "utf8");
			$result = mysqli_affected_rows($conn);
			mysqli_close($conn);
			return $result;
		}
	}
	
	//数据表中删除记录
	//参数表名、条件(不带WHERE);成功返回true，失败返回false
	//
	function db_delete(string $table_name,string $constrain){
		$sql = "DELETE FROM $table_name WHERE $constrain;";
		
		$conn = db_connect(0);//连接主库删除
		
		if(!conn){
			mysqli_close($conn);
			return false;
		}else{
			mysqli_set_charset($conn, "utf8");
			$result = mysqli_query($conn,$sql);
			mysqli_close($conn);
			return $result;
		}
	}
?>