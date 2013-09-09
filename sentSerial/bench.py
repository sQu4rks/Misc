import serial
import time

time.sleep(10)
print "Fire"
ser = serial.Serial('/dev/cu.usbmodem1411',9600)
for i in range(1,50,1):
	print str(i)
	ser.write('t')
	time.sleep(2)
