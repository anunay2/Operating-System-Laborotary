#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define BUFSIZE 1024
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);
char *builtin_str[]={"cd","help","exit"};

int (*builtin_func[])(char **)={&lsh_cd,&lsh_help,&lsh_exit};

int lsh_num_builtins(){
  return sizeof(builtin_str)/sizeof(char *);
}

int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

int lsh_help(char **args){
  int i;
  printf("SHELL\n");
  printf("You have entered the help section:\n");
  printf("The following are the built in:\n");
  for(i =0;i<lsh_num_builtins();i++){
    printf("%s\n",builtin_str[i]);
  }
  return 1;
}
int lsh_exit(char **args){
  return 0;
}


char *read_line(){
  int Buffer_size = BUFSIZE;
  int position = 0;
  char *buffer  =malloc(sizeof(char)*Buffer_size);
  int c;
  //WE took C as the integer as C is the EOF is the integer and not a character

  while(1){
    //get the character from the user
    c=getchar();
    if(c==EOF || c=='\n'){
      buffer[position]='\0';
      //printf("%sas",buffer);
      return buffer;
    }else{
      buffer[position]=c;
    }
    position++;
  }

}
char **split_line(char *line){
  int bufsize=64,position=0;
  char **tokens=malloc(bufsize*sizeof(char*));
  char *token;
  //int position=0;
  //strtok is the library function ussed for the parsing the string
  token=strtok(line,"\t\r\n\a");
  while(token!=NULL){
    tokens[position]=token;
    position++;
    token=strtok(NULL,"\t\n\r\a");
  }
  tokens[position]=NULL;
  return tokens;
}
int launch(char **args){
  pid_t pid,wpid;
  int status;
  pid=fork();
  //Child Process
  if(pid==0){
    if(execvp(args[0],args)==-1){
      perror("lsh");
    }
    return 0;
  }else if(pid<0){
    perror("lsh");
  }else{
    //Parent Process
    do{
      wpid=waitpid(pid,&status,WUNTRACED);
    }while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
}
int execute(char **args){
  int i;
  if(args[0]==NULL){
    return 1;
  }

  for(i=0;i<lsh_num_builtins();i++){
    if(strcmp(args[0],builtin_str[i])==0){
      return (*builtin_func[i])(args);
    }
  }

  return launch(args);
}
void loop(){
  char *line;
  char **args;
  int status=1;
  do{
    printf("root>");
    line=read_line();
    //printf("%s\n",line);
    args=split_line(line);
    status=execute(args);
    free(line);
    free(args);
    }while(status);
  }

  int main(int argc,char **argv){
    loop();
    return 0;
  }
