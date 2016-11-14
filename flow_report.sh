#!/bin/bash
#sar命令来实现实时检测
interfacename=tap0
url="http://localhost/traffic"

#网卡总的收发量
Txtotal=`cat /proc/net/dev |grep $interfacename|awk -F ':' {'print $2'}|awk {'print $9'}`
Rxtotal=`cat /proc/net/dev |grep $interfacename|awk -F ':' {'print $2'}|awk {'print $1'}`

#组成json格式的数据并传输
Time=`date|awk {'print $4'}`
json_traffic=`echo $json_traffic | sed 's/$/&{"Time": \"'"$Time"'\","Txtotal": \"'"$Txtotal"'\","Rxtotal": \"'"$Rxtotal"'\"}/g'`
echo $json_traffic
curl -d "$json_traffic" $url
echo $? >> /etc/openvpn/traffic_record




