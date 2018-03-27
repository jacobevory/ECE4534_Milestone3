import socket
import os
import json

def printheader():
	os.system('cls')
	print ('Welcome to Milestone 2 Demo #4\n\n')
	return

def printdata ( spl, spr, dil, dir ):
	print ('Left Encoder RPM:', spl  )
	if dil == '1':
		print ('\nLeft Encoder Direction: Reverse')
	else:
		print ('\nLeft Encoder Direction: Forward')
	print ('\nRight Encoder RPM:', spr )
	if dir == '1':
		print ('\nRight Encoder Direction: Reverse')
	else:
		print ('\nRight Encoder Direction: Forward')
	print ('\nMessage Type:', msgTyp)
	print ('\nSequence Number:', seq)
	
	
host = ''
port = 4000
backlog = 5
size = 1024

msgTyp = 'x'
seq = 0
spl = ' '
spr = ' '
dir = ' '
dil = ' '


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((host, port))
s.listen(backlog)

print ('server started and listening')
while True:
	client, address = s.accept()
	while True:
		data = client.recv(size)
		if data:
			try:
				jdata = data.decode('ascii')
				j = json.loads(jdata)
				if(j['spl'] != ' '):
					spl = j['spl']
				if(j['spr'] != ' '):
					spr = j['spr']
				if(j['dil'] != ' '):
					dil = j['spl']
				if(j['dir'] != ' '):
					dir = j['dir']
				if(j['typ'] != ' '):
					msgTyp = j['typ']
				if(j['seq'] != ' '):
					seq = j['seq']
				
				printheader()
				printdata(spl, spr, dil, dir)
			except:
				pass
			#print ('dataReceived:', data)
			
			
client.close()
