# CIT595
CIT 595: Arduino Server
This is the project for CIT 595.
temperature folder contains temperature.ino which decides the operation of arduino
Server.c is used to start a server.
read_usb.c and read_usb.h are used for reading data from arduino
projectClient.js and projectClient.html are showing the front end.

Here are the steps to start the project:
1, connect arduino sensor to your computer and get correct file name.
2, In terminal, enter the folder and type 'make' to create server file.
3, run './server 1306 'file_name' ' here 1306 is the port of our project. We have a same port number in .js file so don't mofidy it.
And 'file_name' is the file name of your own arduino file.
4, if it connects to a server, then open html file. Then you can do some operations and see the detailed temperatures.
