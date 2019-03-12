#include  <stdio.h>
#include  <stdlib.h>
#include  <unistd.h>
#include  <errno.h>
#include  <string.h>
extern int errno;
int main(int n,char *file[]){
  //for loop for n process
  for(int i=0;i<n;i++){
    if(fork()==0){
        //Creating a temporary array of characters to add ./
        char temp[]="./";
        //concatinating the ./ with temp
        strcat(temp,file[i]);
        //NULL terminates the execvp systemcall
        char *args[]={temp,NULL};
        //Passing the argument in the execvp system call
        execvp(args[0],args);
        printf("The execvp system call did not execute successfully\n");
        //printing the error
        printf("Error No.%d\n",errno);
        perror("Program\n");
        exit(0);
    }
    else{
      wait(NULL);
    }
  }
  return 0;
}
