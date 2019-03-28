#include<stdio.h>
#include<pthread.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>
int buffer=0;
int count1=0,count2=0,count3=0;
pthread_mutex_t lock;
void threadfunction(int i){
  if(buffer==24){
    pthread_exit(NULL);
  }
  if(i==0){
    count1++;
  }
  if(i==1){
    count2++;
  }
  if(i==2){
    count3++;
  }

  pthread_mutex_lock(&lock);
  buffer++;
  printf("Thread_ID:%ld\n",pthread_self());
  printf("Process_ID:%d\n",getpid());
  printf("Buffer_value:%d\n",buffer);
  printf("\n");
  pthread_mutex_unlock(&lock);
  sleep(1);
  return NULL;
}
int main(){
  pthread_t t1,t2,t3;
  pthread_mutex_init(&lock,NULL);
  while(buffer<24){
    pthread_create(&t1,NULL,&threadfunction,0);
    pthread_create(&t2,NULL,&threadfunction,1);
    pthread_create(&t3,NULL,&threadfunction,2);
  }
  printf("%d\n",count1);
    printf("%d\n",count2);
      printf("%d\n",count3);
  return 0;
}
