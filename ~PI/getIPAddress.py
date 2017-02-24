import socket
import fcntl
import struct

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(s.fileno(),0x8915,struct.pack('256s',ifname[:15]))[20:24])
res = '{"key":"ClientIP","value":{"ip":"%s"}}' %get_ip_address('eth0')
output = open('/home/pi/getIPAddress.txt','w')
output.write(res);
output.close
