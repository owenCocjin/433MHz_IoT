import socket, serial
con=serial.Serial(f'/dev/ttyUSB{input("Enter device number(/dev/ttyUSB#): ")}')
con.baudrate=9600

def main():
	#Open raw socket for writing to interface
	sock=socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(0x03))  #The 3 is to read all data, incoming & outgoing
	try:
		sock.bind(("wlp2s0", 0))
	except OSError as e:
		print(f"[|X:{vname}:Binding]: Interface {PARSER['host']} doesn't exist!")
		exit(4)
	while True:
		#Wait for data from serial
		# print(con.read())

		print("Waiting for transmission...", flush=True)
		buff=b''
		menu=b''
		while menu==b'':
			menu=con.read()
		#Get first 2 bytes. This is the length
		length=int(menu.hex(),16)<<8
		length+=int(con.read().hex(),16)
		print(f"Reading {length} bytes...")
		#Get bytes equal to the length
		for i in range(length):
			buff+=con.read()
		#Write bytes to socket
		print(prettyHex(buff, ascii=False))
		print("\nWriting to interface... ", end='', flush=True)
		sock.send(buff)
		print("Done!", flush=True)


def prettyHex(h, ascii=False):
	'''Returns a printable hex string.
h is a bytes type.'''
	toret=''
	if h==b'':
		return ''
	for b in h:
		if ascii and 0x21<=b<=0x7e:
			toret+=f"  {chr(b)}  "
		else:
			toret+=f"0x{hex(b)[2:]:>02} "
	toret=toret[:-1]
	return toret



if __name__=="__main__":
	try:
		main()
	except KeyboardInterrupt:
		print('\r\033[K')
