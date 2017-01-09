<?php
/*
*配置文件，在使用前修改
*
**/

//定义数据库服务器域名
define('DATA_HOST_M','localhost:3306'); //主库
define('DATA_HOST_S','localhost:3306'); //从库

//定义数据库服务器用户名
define('DATA_HOST_USER','autowatersystem');

//定义数据库服务器密码
define('DATA_HOST_PASS','VliPhMbj4oCVv5B3');

//定义数据库名
define('DATA_HOST_DBNAME','AutoWaterSystem');

//定义图片存储路径
define('STO_PATH',"localhost/AutoWaterSystem/upload");

//定义是否采用云存储，
define('STO_SINACLOUD','NO');

//云存储用户名
define('STO_USERPASS','');

//云存储密码
define('STO_USERID','');

//是否显示错误信息
define('DEBUG_MODE',true);

//定义数据表的名
define('NAME_OF_TABLE_USER','user_info');
define('NAME_OF_TABLE_SENSOR','sensor_info');
define('NAME_OF_TABLE_CAPTURE','capture_info');
define('NAME_OF_TABLE_SENSORLOG','sensor_log');

//定义初始的占位用户ID编号
define('ROOT_USED_ID','100000000');
