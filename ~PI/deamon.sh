#!/bin/bash
#判断进程是否存在，如果不存在就启动它
PIDS=`ps -ef |grep AutoWaterSystem |grep -v grep | awk '{print $2}'`
if [ "$PIDS" != "" ]; then
echo "myprocess is runing!"
else
cd /home/pi/AutoWaterSystem/build-AutoWaterSystem-Desktop-Release/
./AutoWaterSystem
#运行进程
fi