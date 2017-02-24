#!/bin/bash
sudo python /home/pi/tempdata1.py
curl --request POST --data-binary @"/home/pi/tempdata1.txt" --header "U-ApiKey:372ff6f73d10b192449d1c95dbaecff0" http://api.yeelink.net/v1.1/device/353664/sensor/399674/datapoints