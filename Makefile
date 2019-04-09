<<<<<<< HEAD

=======
>>>>>>> df936d5e1ed52d198aafe6e850830c96587c0c7c
all: read_usb server

read_usb: read_usb.c
	clang -g read_usb.c -c


server: server.c read_usb
	clang -g server.c read_usb.o -o server

clean:
<<<<<<< HEAD
	rm -rf *.o
=======
	rm -rf *.o
>>>>>>> df936d5e1ed52d198aafe6e850830c96587c0c7c
