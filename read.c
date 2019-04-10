#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <pthread.h> 
// #include "read_demo.h"
float temperature[3600];
float max_temp = -INFINITY;
float min_temp = INFINITY;
float avg_temp;
float current_temp;
int temp_cur = 0; 
int temp_size = 0;
float sum_temp = 0;
/*
This code configures the file descriptor for use as a serial port.
*/
void configure(int fd) {
  struct termios pts;
  tcgetattr(fd, &pts);
  cfsetospeed(&pts, 9600);
  cfsetispeed(&pts, 9600);

  /*
  // You may need to un-comment these lines, depending on your platform.
  pts.c_cflag &= ~PARENB;
  pts.c_cflag &= ~CSTOPB;
  pts.c_cflag &= ~CSIZE;
  pts.c_cflag |= CS8;
  pts.c_cflag &= ~CRTSCTS;
  pts.c_cflag |= CLOCAL | CREAD;
  pts.c_iflag |= IGNPAR | IGNCR;
  pts.c_iflag &= ~(IXON | IXOFF | IXANY);
  pts.c_lflag |= ICANON;
  pts.c_oflag &= ~OPOST;
  */

  tcsetattr(fd, TCSANOW, &pts);

}

int temprature_change(char* s){
  int i = 0;
  while(s[i]){
    if(isdigit(s[i])){
      char* k = &s[i];
      // float cur_temperature = atof(k);
      current_temp = atof(k);
      if(temp_size < 3600){
        temperature[temp_cur] = current_temp;
        sum_temp += current_temp;
        
        if(current_temp > max_temp){max_temp = current_temp;}
        if(current_temp < min_temp){min_temp = current_temp;}
        temp_size ++;
        avg_temp = sum_temp / temp_size;
        temp_cur = (temp_cur + 1) % 3600;

      }
      else{
        sum_temp = sum_temp + current_temp - temperature[temp_cur];
        if(current_temp > max_temp){max_temp = current_temp;}
        if(current_temp < min_temp){min_temp = current_temp;}
        temperature[temp_cur] = current_temp;
        
        avg_temp = sum_temp / 3600;

        
        temp_cur = (temp_cur + 1) % 3600;
      }
      printf("The temperature now is %f degrees C\n",current_temp);
      printf("Average: %f degrees ; Max: %f degrees ; Min : %f degrees \n\n",avg_temp,max_temp,min_temp);
      return 0;
    }
    i++;
  }
  return 1;
}

// /*
int main(int argc, char* argv[]) {

  if (argc < 2) {
    printf("Please specify the name of the serial port (USB) device file!\n");
    exit(0);
  }

  // get the name from the command line
  char* filename = argv[1];
  int fd = -1;
  // try to open the file for reading and writing
  // you may need to change the flags depending on your platform
  while(fd < 0 ){
  fd = open(filename, O_RDWR | O_NOCTTY | O_NDELAY);
  
  if (fd < 0) {
    perror("Could not open file\n");
    // exit(1);
  }
  else {
    printf("Successfully opened %s for reading and writing\n", filename);
    configure(fd);
  }
}
  // configure(fd);
  int i = 0;
  char arr[100];
  int start = 0;
  int arr_pos = 0;
  int disconnected = 0;
  // char buf[10];
  while(1){
    while(disconnected == 0){
      char buf[1];
      int bytes_read = read(fd,buf,1);
      // int err = errno;
      // printf("%d",err);
      
      if(errno == 6 || errno == 9){
        printf("error\n");
        printf("EAGAIN = %d\n", ENXIO);
        printf("EBADF = %d\n",EBADF);
        disconnected = 1;
      }
      else{
        if(bytes_read > 0){
        printf("%s",buf);
        }
      }
    }
    fd = open(filename, O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd < 0){
      // printf("disconnected");
    }else{
      disconnected = 0;
      printf("reconnect");
    }

  }
}
  
  


