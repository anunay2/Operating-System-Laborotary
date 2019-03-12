#include <stdio.h>
#include <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdlib.h>
#include <string.h>
void SIGINT_handler(int);
char *message;
int main(int argc,char *argv[]){
  pid_t pid;
  key_t Mykey;
  int ShmID;
  pid_t *ShmPTR;
  int i;
  printf("My pid is %d\n",getpid());
  Mykey=atoi(argv[2]);
  if(signal(SIGINT,SIGINT_handler) == SIG_ERR){
    printf("SIGINT install error\n");
    exit(1);
  }
  ShmID=shmget(Mykey,1024,0666|IPC_CREAT);
  message=(char *)shmat(ShmID,NULL,0);
  //ShmPTR=(pid_t *)shmat(ShmID,NULL,0);
  //pid = *ShmPTR;
  //printf("%d",pid);
  //shmdt(ShmPTR);

  char ch;
  int k=0;
  printf("Press Enter to send the message:\n");
  while(1){
    ch=getchar();
    if(ch=='\n'){
      kill(atoi(argv[1]),SIGINT);
      printf("Message Sent!\n");
      sleep(1);
      for(int i=0;i<k;i++){
        message[i]='\0';
      }
      k=0;
      //shmdt(message);
    }
    else{
      message[k++]=ch;
    }
  }
  return 0;
}

void SIGINT_handler(int sig){
  signal(sig,SIG_IGN);
  printf("Message Received!\n");
  printf("%s\n",message);
  //shmdt(message);
  //printf("From SIGINT:just got a %d(SIGINT ^C) signal\n",sig);
  signal(sig,SIGINT_handler);
}
