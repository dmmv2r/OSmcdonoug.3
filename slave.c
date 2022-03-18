#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include "sem.h"

int main(int argc, char* argv[]) {
   printf("in slave\n");



   int number;
   //number = atoi(argv[1]);
   number = argv[1];
   printf("argument is %d\n", number);


   //sem work

   char file[20];
   //char num = itoa(argv[1]);

   strcat(file, "slave");
   printf("test1\n");

   strcat(file, argv[1]);
   printf("test2\n");

   strcat(file, ".log");
   printf("test3\n");
   //char* file[] = "slave" + argv[1] + ".log";
   FILE *fptr;
   fptr = fopen(file, "w");
   if(fptr == NULL) {
      perror("FILE: ");
      exit(1);
   }

   fprintf(fptr, "logged");

   fclose(fptr);


   //sem work


   printf("leaving slave\n");
   return 0;
}


