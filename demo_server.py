import socket
import os
import json

def printheader():
	os.system('cls')
	print ('Welcome to the Motor Encoder Demo\n\n')
	return

def printdata ( left, right ):
	print (  ' Left Encoder RPM:', left  )
	print ('\nRight Encoder RPM:', right )
	
	
host = ''
port = 2000
backlog = 5
size = 1024
dataL = 0
dataR = 0

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host, port))
s.listen(backlog)

print ('server started and listening')

while True:
	client, address = s.accept()
	while True:
		data = client.recv(size)
		if data:
			#print(data)
			jdata = data.decode('ascii')
			"""
			if jdata[0:6] == "*HELLO*":
				jdata = jdata[7:]
				"""
			
			if len(jdata) < 33 and len(jdata) > 7:
				j = json.loads(jdata)
				dataL = j['left']
				dataR = j['right']
				printheader()
				printdata(dataL, dataR)
				#print ('dataReceived:', data)
			
			
client.close()
