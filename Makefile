all: read_usb server

read_usb: read_usb.c
	clang -g read_usb.c -c


server: server.c read_usb
	clang -g server.c read_usb.o -o server

clean:

	rm -rf *.o

