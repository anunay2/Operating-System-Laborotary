#include  <stdio.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <sys/types.h>
#include  <signal.h>
#include <stdlib.h>
#include  <string.h>
char *message;
void SIGINT_handler(int);

int main(int argc,char *argv[]){

  int i;
  pid_t pid = getpid();
  pid_t *ShmPTR;

  //for the command line argument
  key_t key=atoi(argv[2]);

  if (signal(SIGINT, SIGINT_handler) == SIG_ERR) {
       printf("SIGINT install error\n");
       exit(1);
  }
  int partner_pid;
  printf("My pid is %d\n",pid);
  printf("Enter the partner pid:\n");
  scanf("%d",&partner_pid);
  //string message="";
  //shmget t=returns a identifier in shmid
  printf("Yohooo!Connection Established!\n");
  int shmid = shmget(key,1024,IPC_CREAT | 0666);
  message=(char *) shmat(shmid,NULL,0);
  //*ShmPTR = pid;
  printf("Press Enter to send the message:\n");
  int k=0;
  char ch;
  ch = getchar();
  while(1){
    ch=getchar();
    if(ch=='\n'){
      kill(partner_pid,SIGINT);
      //printf("%s",message);
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
  //for(i=0;;i++){
    //printf("From process %d:%d\n",pid,i);
    //sleep(2);
  //}
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
