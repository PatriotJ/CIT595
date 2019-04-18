#ifndef __read_demo_h__
#define __read_demo_h__
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
// #include "cJSON.h"
float temperature[3600];
float max_temp;
float min_temp;
float avg_temp;
float current_temp;
int control;
int connected;
void configure(int fd);
int temprature_change(char* s);
void* read_from_arduino(void* arg);
void* print_tempareture(void* arg);
int is_c;
#endif