from datetime import datetime
def main():
	with open("alerts.ind", 'rb') as f:
		print("Started...")
		while True:
			psize=f.read(4).strip(b';')
			if psize==b'':
				continue
			message=f.read(int(psize.hex(),16))
			print(f"[{datetime.now().strftime('%H:%M:%S')}]:Heard message: {message.decode()}")

if __name__=="__main__":
	try:
		main()
	except KeyboardInterrupt:
		print("\r\033[K", end='')
