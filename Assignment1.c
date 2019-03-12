#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int fact(int num){
  if(num==0){
    return 1;
  }
  if(num==1){
    return num;
  }
 return num*fact(num-1);
}

int main(int argc,char *argb[]){
  //printf("Please enter the value of n:\n");
  //scanf("%d",&n);
  //printf("The value of n is%d",n);
  for(int i=1;i<argc;i++){
    if(fork()==0){
      //printf("Factorial is %d\n",fact(argb[i]));
      printf("Factorial[%s]:",argb[i]);
      printf("%d ",fact(atoi(argb[i])));
      printf("[son] pid %d from [parent] pid %d\n\n",getpid(),getppid());



      exit(0);
    }
  }
return 0;
}
