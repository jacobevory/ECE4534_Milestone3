import socket
import os

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
			#printheader()
			#printdata(dataL, dataR)
			#dataL = dataL + 1
			#dataR = dataR + 1
			print ('dataReceived:', data)
			
client.close()
