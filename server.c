// /* 
// This code primarily comes from 
// http://www.prasannatech.net/2008/07/socket-programming-tutorial.html
// and
// http://www.binarii.com/files/papers/c_sockets.txt
//  */

// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <errno.h>
// #include <string.h>
// #include "read_usb.h"
// #include <pthread.h>

// #include <fcntl.h>
// #include <signal.h>

// #include <termios.h>


// #include <ctype.h>
// #include <math.h>

// int arduino;
// int light_model;
// int parse(char *request){
      
//       char re[1024];
//       strcpy(re,request);
//       // printf("%s\n",re);
//       char* delim = "?";
//       char* token;
//       token = strtok(re,delim);
//       if(token == NULL){
//             // printf("0");
//             return 0;
//       }
//       if(strcmp(token,"temperature") != 0){
//             printf("%s\n",token);
//       }
//       // printf("%s\n",token);
//       token = strtok(NULL,delim);
//       if(token == NULL){
//             return 0;
//       }
//       printf("aaa%s\n",token);
//       char* msg;
//       printf("%d\n",strcmp(token,"light"));
//       if(strcmp(token,"light") == 0){
//             token = strtok(NULL,delim);
//             printf("%s\n",token);
//             printf("%d\n",strcmp(token,"blue"));
//             printf("%d\n",strcmp(token,"red"));
//             if(strcmp(token,"blue")==0){
//                   msg = "BLUE";
//                   light_model = 1;
//                   printf("%d\n",light_model);
//                   printf("%s\n",msg);
//                   write(arduino,msg,strlen(msg));
//             }
//             else if(strcmp(token,"red") == 0){
//                   light_model = 1;
//                   msg = "RED";
//                   write(arduino,msg,strlen(msg));
//             }else if(strcmp(token,"green") == 0){
//                   light_model = 1;
//                   msg = "GREEN";
//                   write(arduino,msg,strlen(msg));
//             }else if(strcmp(token,"off") == 0){
//                   msg = "OFF";
//                   write(arduino,msg,strlen(msg));
//             }else if(strcmp(token,"random") == 0){
//                   msg = "RANDOM";
//                   write(arduino,msg,strlen(msg));
//             }else if(strcmp(token,"normal") == 0){
//                   msg = "NORMAL";
//                   write(arduino,msg,strlen(msg));
//             }
//       }
//       return 0;
// }



// void* start_server(void* arg)
// { 
// int PORT_NUMBER = *(int*)arg;
//       // structs to represent the server and client
//       struct sockaddr_in server_addr,client_addr;    
      
//       int sock; // socket descriptor

//       // 1. socket: creates a socket descriptor that you later use to make other system calls
//       if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
// 	perror("Socket");
// 	exit(1);
//       }
//       int temp;
//       if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&temp,sizeof(int)) == -1) {
// 	perror("Setsockopt");
// 	exit(1);
//       }

//       // configure the server
//       server_addr.sin_port = htons(PORT_NUMBER); // specify port number
//       server_addr.sin_family = AF_INET;         
//       server_addr.sin_addr.s_addr = INADDR_ANY; 
//       bzero(&(server_addr.sin_zero),8); 
      
//       // 2. bind: use the socket and associate it with the port number
//       if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
// 	perror("Unable to bind");
// 	exit(1);
//       }

//       // 3. listen: indicates that we want to listen to the port to which we bound; second arg is number of allowed connections
//       if (listen(sock, 1) == -1) {
// 	perror("Listen");
// 	exit(1);
//       }
          
//       // once you get here, the server is set up and about to start listening
//       printf("\nServer configured to listen on port %d\n", PORT_NUMBER);
//       fflush(stdout);
//      int i = 1;
//      while(i < 100){
//            i++;
//            printf("%d\n",i);
//       // 4. accept: wait here until we get a connection on that port
//       int sin_size = sizeof(struct sockaddr_in);
//       int fd = accept(sock, (struct sockaddr *)&client_addr,(socklen_t *)&sin_size);
//       if (fd != -1) {
// 	printf("Server got a connection from (%s, %d)\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
      
// 	// buffer to read data into
// 	char request[1024];
	
// 	// 5. recv: read incoming message (request) into buffer
// 	int bytes_received = recv(fd,request,1024,0);
// 	// null-terminate the string
// 	request[bytes_received] = '\0';
// 	// print it to standard out
// 	// printf("This is the incoming request:\n%s\n", request);
//       int xxx = parse(request);




// 	// this is the message that we'll send back
//       char r[1000];
//       char t1[20];
      
//       char *reply = "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: * \nContent-Type: application/json\n\n{\n\"temperature\":";
//       strcat(r,reply);
//       // gvct(current_temp,7,t1);
//       sprintf(t1,"%f",current_temp);
//       strcat(r,t1);

//       char *reply2 = ",\n\"max_temp\":";
//       strcat(r,reply2);
//       char t2[20];
//       sprintf(t2,"%f",max_temp);
//       // gvct(max_temp,7,t2);
//       strcat(r,t2);
//       char *reply3 = ",\n\"min_temp\":";
//       strcat(r,reply3);
//       char t3[20];
//       sprintf(t3,"%f",min_temp);
//       // gvct(min_temp,7,t3);
//       strcat(r,t3);
//       char* reply4 = ",\n\"avg_temp\":";
//       strcat(r,reply4);
//       char t4[20];
//       sprintf(t4,"%f",avg_temp);
//       // gvct(avg_temp,r,t4);
//       strcat(r,t4);
//       char* reply5 = ",\n\"celsius\":";
//       strcat(r,reply5);
//       char t5[10];
//       int is_c = 1;
//       sprintf(t5,"%d",is_c);
//       strcat(r,t5);
//       strcat(r,"\n}");
//       // printf("%s\n",r);
// 	// 6. send: send the outgoing message (response) over the socket
// 	// note that the second argument is a char*, and the third is the number of chars	
//       printf("%s\n",r);
// 	send(fd, r, strlen(r), 0);
//       memset(r,0,1000);
//       }
// 	// 7. close: close the connection
// 	close(fd);
// 	printf("Server closed connection\n");
//       }

//       // 8. close: close the socket
//       close(sock);
//       printf("Server shutting down\n");
  
//       return 0;
// } 






// int main(int argc, char *argv[])
// {
//       printf("the temperature is %f\n",temperature[0]);
//   // check the number of arguments
//   if (argc != 3) {
//       printf("\nUsage: %s [port_number]\n", argv[0]);
//       exit(-1);
//   }

//   int port_number = atoi(argv[1]);
//   printf("%d\n",port_number);
//   char* filename = argv[2];

//   if (port_number <= 1024) {
//     printf("\nPlease specify a port number greater than 1024\n");
//     exit(-1);
//   }

//     arduino = open(filename, O_RDWR | O_NOCTTY | O_NDELAY);
  
//     if (arduino < 0) {
//         perror("Could not open file\n");
//         exit(1);
//     }
//     else {
//         printf("Successfully opened %s for reading and writing\n", filename);
//     }
     
//     configure(arduino);
// //     char* msg = "asdadas\n";
// //     int i = write(fd,msg,strlen(msg));

//     pthread_t threads[3];
//     pthread_create(&threads[0], NULL, read_from_arduino, (void *)&arduino);
//     pthread_create(&threads[1], NULL, (void *)&start_server, (void*) &port_number);
// //     pthread_create(&threads[2], NULL, (void *)&start_server, (void*) &port_number);
//     pthread_join(threads[0],NULL);
//     pthread_join(threads[1],NULL);
// //     pthread_join(threads[2],NULL);
//     // start_server(port_number);
//     }


/* 
This code primarily comes from 
http://www.prasannatech.net/2008/07/socket-programming-tutorial.html
and
http://www.binarii.com/files/papers/c_sockets.txt
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "read_usb.h"
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>


#include <ctype.h>
#include <math.h>
pthread_mutex_t request_lock = PTHREAD_MUTEX_INITIALIZER;
int arduino;
int light_model;
char request[1024];


int parse(char *request){
      // printf("%s\n",request);
      char re[1024];
      strcpy(re,request);
      // printf("%s\n",re);
      char* delim = "?";
      char* token;
      token = strtok(re,delim);
      if(token == NULL){
            // printf("0");
            return 0;
      }
      
      token = strtok(NULL,delim);
      if(token == NULL){
            return 0;
      }
     
      char* msg;
      // printf("%d\n",strcmp(token,"light"));
      
      // control light
      printf("%s\n",token);
      if(strcmp(token,"light") == 0){
            token = strtok(NULL,delim);
            // printf("%s\n",token);
            // printf("%d\n",strcmp(token,"blue"));
            // printf("%d\n",strcmp(token,"red"));
            if(strcmp(token,"blue")==0){
                  msg = "BLUE";
                  light_model = 1;
                  // printf("%d\n",light_model);
                  // printf("%s\n",msg);
                  write(arduino,msg,strlen(msg));
            }
            else if(strcmp(token,"red") == 0){
                  light_model = 1;
                  msg = "RED";
                  write(arduino,msg,strlen(msg));
            }else if(strcmp(token,"green") == 0){
                  light_model = 1;
                  msg = "GREEN";
                  write(arduino,msg,strlen(msg));
            }else if(strcmp(token,"off") == 0){
                  msg = "OFF";
                  write(arduino,msg,strlen(msg));
            }else if(strcmp(token,"random") == 0){
                  msg = "RANDOM";
                  write(arduino,msg,strlen(msg));
            }else if(strcmp(token,"normal") == 0){
                  msg = "NORMAL";
                  write(arduino,msg,strlen(msg));
            }
      }
      // control C or F
      else if(strcmp(token,"unit") == 0){
            token = strtok(NULL,delim);
            if(strcmp(token,"farenheit") == 0){
                  msg = "FAH";
                  is_c = 0;
                  write(arduino,msg,strlen(msg));
            }
            else if(strcmp(token,"celsius") == 0){
                  msg = "CEL";
                  is_c = 1;
                  write(arduino,msg,strlen(msg));
            }
      }
      
      // whether show or not
      else if(strcmp(token,"reading") == 0){
            token = strtok(NULL,delim);
            printf("%s\n",token);
            if(strcmp(token,"stop") == 0){
                  msg = "STOP";
                  write(arduino,msg,strlen(msg));
            }
            else if(strcmp(token,"resume") == 0){
                  msg = "RESUME";
                  write(arduino,msg,strlen(msg));
            }
      }
      // shut down both read and server.
      else if(strcmp(token,"off") == 0){
            control = 0;
      }
      return 0;
}



void* start_server(void* arg)
{ 
int PORT_NUMBER = *(int*)arg;
      // structs to represent the server and client
      struct sockaddr_in server_addr,client_addr;    
      
      int sock; // socket descriptor

      // 1. socket: creates a socket descriptor that you later use to make other system calls
      if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
	perror("Socket");
	exit(1);
      }
      int temp;
      if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&temp,sizeof(int)) == -1) {
	perror("Setsockopt");
	exit(1);
      }

      // configure the server
      server_addr.sin_port = htons(PORT_NUMBER); // specify port number
      server_addr.sin_family = AF_INET;         
      server_addr.sin_addr.s_addr = INADDR_ANY; 
      bzero(&(server_addr.sin_zero),8); 
      
      // 2. bind: use the socket and associate it with the port number
      if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
	perror("Unable to bind");
	exit(1);
      }

      // 3. listen: indicates that we want to listen to the port to which we bound; second arg is number of allowed connections
      if (listen(sock, 1) == -1) {
	perror("Listen");
	exit(1);
      }
          
      // once you get here, the server is set up and about to start listening
      printf("\nServer configured to listen on port %d\n", PORT_NUMBER);
      fflush(stdout);
     while(control){
      //      i++;
      //      printf("%d\n",i);
      // 4. accept: wait here until we get a connection on that port
      int sin_size = sizeof(struct sockaddr_in);
      int fd = accept(sock, (struct sockaddr *)&client_addr,(socklen_t *)&sin_size);
      if (fd != -1) {
	printf("Server got a connection from (%s, %d)\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
      
	// buffer to read data into
	// char request[1024];
	
	// 5. recv: read incoming message (request) into buffer
      pthread_mutex_lock(&request_lock);
	int bytes_received = recv(fd,request,1024,0);
	// null-terminate the string
	request[bytes_received] = '\0';
	// print it to standard out
	// printf("This is the incoming request:\n%s\n", request);
      int xxx = parse(request);
      pthread_mutex_unlock(&request_lock);

      if(control == 0){
            control = 0;
            break;
      }


	// this is the message that we'll send back
      char r[1000];
      char t1[20];
      float current,max,min,avg;
      if(is_c == 0){
            current = current_temp * 1.8 +32;
            max = max_temp * 1.8 + 32;
            min = min*1.8 + 32;
            avg = avg_temp * 1.8 + 32;
      }
      else{
            current = current_temp;
            max = max_temp;
            min = min_temp;
            avg = avg_temp;
      }

      char *reply = "HTTP/1.1 200 OK\nAccess-Control-Allow-Origin: * \nContent-Type: application/json\n\n{\n\"temperature\":";
      strcat(r,reply);
      
      sprintf(t1,"%f",current);
      strcat(r,t1);

      char *reply2 = ",\n\"max_temp\":";
      strcat(r,reply2);
      char t2[20];
      sprintf(t2,"%f",max);
      strcat(r,t2);

      char *reply3 = ",\n\"min_temp\":";
      strcat(r,reply3);
      char t3[20];
      sprintf(t3,"%f",min);
      strcat(r,t3);

      char* reply4 = ",\n\"avg_temp\":";
      strcat(r,reply4);
      char t4[20];
      sprintf(t4,"%f",avg);
      strcat(r,t4);

      char* reply5 = ",\n\"celsius\":";
      strcat(r,reply5);
      char t5[10];
      // int is_c = 1;
      sprintf(t5,"%d",is_c);
      strcat(r,t5);

      char* reply6 = ",\n\"connect\":";
      strcat(r,reply6);
      char t6[10];
      sprintf(t6,"%d",connected);
      strcat(r,t6);

      strcat(r,"\n}");

      




	// 6. send: send the outgoing message (response) over the socket
	// note that the second argument is a char*, and the third is the number of chars	

	send(fd, r, strlen(r), 0);
      memset(r,0,1000);
      }
	// 7. close: close the connection
	close(fd);
	printf("Server closed connection\n");
      }

      // 8. close: close the socket
      close(sock);
      printf("Server shutting down\n");
  
      return 0;
} 






int main(int argc, char *argv[])
{
      printf("the temperature is %f\n",temperature[0]);
  // check the number of arguments
  if (argc != 3) {
      printf("\nUsage: %s [port_number]\n", argv[0]);
      exit(-1);
  }

  int port_number = atoi(argv[1]);
  printf("%d\n",port_number);
  char* filename = argv[2];

  if (port_number <= 1024) {
    printf("\nPlease specify a port number greater than 1024\n");
    exit(-1);
  }
printf("%d\n",control);
control = 1;
printf("%d\n",control);
    pthread_t threads[3];
    pthread_create(&threads[0], NULL, read_from_arduino, (void *)filename);
    pthread_create(&threads[1], NULL, (void *)&start_server, (void*) &port_number);
//     pthread_create(&threads[2], NULL, (void *)&start_server, (void*) &port_number);
    pthread_join(threads[0],NULL);
    pthread_join(threads[1],NULL);
//     pthread_join(threads[2],NULL);
    // start_server(port_number);
    }

