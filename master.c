#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "sem.h"

int main(int argc, char* argv[]) {
   printf("in master\n");

   int opt;
   int time;
   int processes;

   time = 100;
   processes = 1;

   while((opt = getopt(argc, argv, "ht:n:")) != -1) {
      switch(opt) {
         case 'h':
            printf("Usage: use command ./master -t x -n y\n");
            printf("where x is max amount of time until the program terminates (deafult 100)\n");
            printf("and x is the number of processes to create (max is 20)\n");
            return -1;
         case 't':
            time  = atoi(optarg);
            break;
         case 'n':
            processes = atoi(optarg);
            break;
         default:
            printf("Arguments required\n");
            //return -1;
            exit(-1);
      }
   }

  // printf("time is %d\n", time);
  // printf("processes is %d\n", processes);

   if(processes > 20) {
      printf("Invalid number of processes. Must be below 20\n");
      exit(-1);
   }


   //char* args[] = {"./slave", "7", NULL};
   pid_t childpid = 0;
   int i;

   for(i = 0; i < processes; i++) {
      if((childpid != fork())) { //child
         //wait(NULL);
         char* args[] = {"./slave", i, NULL};
         //char c = i + '0';
         //args[0] = c;
         printf("execing\n");
         execv("./slave", args);
      }
      
      printf("past fork\n");
   }

   printf("waiting\n");
   wait(NULL);

   printf("leaving master\n");
   return 0;
}


