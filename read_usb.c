// #include <sys/types.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <signal.h>
// #include <string.h>
// #include <termios.h>
// #include <unistd.h>
// #include <string.h>
// #include <ctype.h>
// #include <math.h>
// #include <pthread.h> 
// #include <float.h>
// // #include "read_demo.h"
// float temperature[3600];
// float max_temp = -FLT_MIN;
// float min_temp = FLT_MAX;
// float avg_temp;
// float current_temp;
// int temp_cur = 0; 
// int temp_size = 0;
// float sum_temp = 0;
// int control = 1;
// /*
// This code configures the file descriptor for use as a serial port.
// */
// void configure(int fd) {
//   struct termios pts;
//   tcgetattr(fd, &pts);
//   cfsetospeed(&pts, 9600);
//   cfsetispeed(&pts, 9600);

//   /*
//   // You may need to un-comment these lines, depending on your platform.
//   pts.c_cflag &= ~PARENB;
//   pts.c_cflag &= ~CSTOPB;
//   pts.c_cflag &= ~CSIZE;
//   pts.c_cflag |= CS8;
//   pts.c_cflag &= ~CRTSCTS;
//   pts.c_cflag |= CLOCAL | CREAD;
//   pts.c_iflag |= IGNPAR | IGNCR;
//   pts.c_iflag &= ~(IXON | IXOFF | IXANY);
//   pts.c_lflag |= ICANON;
//   pts.c_oflag &= ~OPOST;
//   */

//   tcsetattr(fd, TCSANOW, &pts);

// }

// int temprature_change(char* s){
//   int i = 0;
//   while(s[i]){
//     if(isdigit(s[i])){
//       char* k = &s[i];
//       // float cur_temperature = atof(k);
//       current_temp = atof(k);
//       if(temp_size < 3600){
//         temperature[temp_cur] = current_temp;
//         sum_temp += current_temp;
        
//         if(current_temp > max_temp){max_temp = current_temp;}
//         if(current_temp < min_temp){min_temp = current_temp;}
//         temp_size ++;
//         avg_temp = sum_temp / temp_size;
//         temp_cur = (temp_cur + 1) % 3600;

//       }
//       else{
//         sum_temp = sum_temp + current_temp - temperature[temp_cur];
//         if(current_temp > max_temp){max_temp = current_temp;}
//         if(current_temp < min_temp){min_temp = current_temp;}
//         temperature[temp_cur] = current_temp;
        
//         avg_temp = sum_temp / 3600;

        
//         temp_cur = (temp_cur + 1) % 3600;
//       }
//       // printf("The temperature now is %f degrees C\n",current_temp);
//       // printf("Average: %f degrees ; Max: %f degrees ; Min : %f degrees \n\n",avg_temp,max_temp,min_temp);
//       return 0;
//     }
//     i++;
//   }
//   return 1;
// }

// void* read_from_arduino(void* arg){
//   int fd = *(int*)arg;
//   int i = 0;
//   char arr[100];
//   int start = 0;
//   int arr_pos = 0;
//   while(control){
//     char buf[1];

//     int bytes_read = read(fd,buf,1);
//     // printf("%s",buf);
//     if(bytes_read <= 0){
//       continue;
//     }
//     else{
//         // printf("%s",buf);
//         if(start == 0){
//             if(buf[0] == 'T'){
//                 start = 1;
//                 arr[arr_pos] = buf[0];
//                 arr_pos ++;
//             }
//         }
//         else{
//             arr[arr_pos] = buf[0];
//             arr_pos ++;
//             if(buf[0] == '\n'){

//                 if(arr_pos >= 34){
//                     temprature_change(arr);
                    
//                     arr_pos = 0;
//                     start = 0;
//                 }
//                 arr_pos = 0;
//             memset(arr,0,100);
//             }
//         }
//     }
    
 
//   }
  
// }

// void* print_tempareture(void* arg){
//   char input[100];
//   printf("Do you want to read current temperature? Y/y to read\n");
//   scanf("%s",input);
//   while((strcmp(input,"Y") == 0) || (strcmp(input,"y") == 0)){
//     int pos = (3600 + temp_cur - 1) % 3600;
//     printf("The temperature now is %f degrees C\n",current_temp);
//     printf("Average: %f degrees ; Max: %f degrees ; Min : %f degrees \n\n",avg_temp,max_temp,min_temp);
//     printf("Do you want to read current temperature? Y/y to read");
//     scanf("%s",input);
//   }
// } 

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
#include <float.h>
#include "read_usb.h"
float temperature[3600];
float max_temp = -FLT_MIN;
float min_temp = FLT_MAX;
float avg_temp;
float current_temp;
int temp_cur = 0; 
int temp_size = 0;
float sum_temp = 0;
int control;
int arduino;
// 0 means not disconnected
// 1 means disconnected
int connected = 1;
int is_c = 1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
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
  printf("%s\n",s);
  int i = 0;
  while(s[i]){
    if(isdigit(s[i])){
      char* k = &s[i];
      // float cur_temperature = atof(k);
      current_temp = atof(k);
      printf("%f\n",current_temp);
      // if(current_temp < 5){
      //   printf("%d\n",current_temp);
      //   continue;
      // }
      if(is_c == 0){
        current_temp = (current_temp - 32) * 5 / 9;
      }
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
      // printf("The temperature now is %f degrees C\n",current_temp);
      // printf("Average: %f degrees ; Max: %f degrees ; Min : %f degrees \n\n",avg_temp,max_temp,min_temp);
      return 0;
    }
    i++;
  }
  return 1;
}

void* read_from_arduino(void* arg){

  char* filename = (char*)arg;
  printf("%s\n",filename);
  arduino = open(filename, O_RDWR | O_NOCTTY | O_NDELAY);
  if (arduino < 0) {
        perror("Could not open file\n");
        exit(1);
    }
    else {
        printf("Successfully opened %s for reading and writing\n", filename);
    }
     
    configure(arduino);
  // int fd = *(int*)arg;
  int i = 0;
  char arr[100];
  int start = 0;
  int arr_pos = 0;
  while(control == 1){
    char buf[1];
    while(connected == 1){
      if(control == 0){
        break;
      }
    int bytes_read = read(arduino,buf,1);
    // printf("%s",buf);
    if(errno == ENXIO || errno == EBADF){
      connected = 0;
      continue;
    }
    if(bytes_read <= 0){
      continue;
    }
    else{
        // printf("%s",buf);
        if(start == 0){
            if(buf[0] == 'T'){
                start = 1;
                arr[arr_pos] = buf[0];
                arr_pos ++;
            }
        }
        else{
            arr[arr_pos] = buf[0];
            arr_pos ++;
            if(buf[0] == '\n'){
                if(arr_pos >= 34){
                  pthread_mutex_lock(&lock);
                    temprature_change(arr);
                    pthread_mutex_unlock(&lock);
                    arr_pos = 0;
                    start = 0;
                }
                arr_pos = 0;
            memset(arr,0,100);
            }
        }
    }
  }
  is_c = 1;
  arduino = open(filename, O_RDWR | O_NOCTTY | O_NDELAY);
  if(arduino < 0){
    sleep(1);
  }
  else{
    connected = 1;
    configure(arduino);
  }

  
}
printf("Stop reading\n");
}

void* print_tempareture(void* arg){
  char input[100];
  printf("Do you want to read current temperature? Y/y to read\n");
  scanf("%s",input);
  while((strcmp(input,"Y") == 0) || (strcmp(input,"y") == 0)){
    int pos = (3600 + temp_cur - 1) % 3600;
    printf("The temperature now is %f degrees C\n",current_temp);
    printf("Average: %f degrees ; Max: %f degrees ; Min : %f degrees \n\n",avg_temp,max_temp,min_temp);
    printf("Do you want to read current temperature? Y/y to read");
    scanf("%s",input);
  }
} 

