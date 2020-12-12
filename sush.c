#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "token.h"
#define MAX_LEN 1023
#define AMNT_ROWS 5

char* PS1;
char* HOME;
char* PATH;
char* CWD;

void sushFork(const char* cmd, char *const argv[]){
  pid_t pid = fork();

  if (pid == 0){
    execvp(cmd, argv);
  }else{
    int status;
    waitpid(pid, &status, 0);
  }
}

void sushExit(){
  printf("Bye!\n");
  exit(0);
}

void sushPwd(){
  const char* cmd = "/bin/pwd";
  char *const pwdargs[] = { strdup(cmd), NULL };

  sushFork(cmd, pwdargs);
}

void sushLs(char **tokenizedCmd){
  const char* cmd = "/bin/ls";
  char *const lsargs[] = { strdup(cmd), tokenizedCmd[1]};

  sushFork(cmd, lsargs);
}

int cmdExecute(char* command){

  char **tokenizedCmd = malloc(sizeof(char *) * (AMNT_ROWS + 1));

  for(int i = 0; i < AMNT_ROWS + 1; i++){
    tokenizedCmd[i] = malloc(sizeof(command[i]) * (strlen(command) + 1));
  }
  
  if(command == NULL){
    return 0;
  }

  string_tok(command, tokenizedCmd);

  if(strcmp(tokenizedCmd[0], "exit") == 0){
    sushExit();
  }else if(strcmp(tokenizedCmd[0], "pwd") == 0){
    sushPwd();
  }
  // else if(strcmp(tokenizedCmd[0], "ls") == 0){
  //   sushLs(tokenizedCmd);
  // }

  free(tokenizedCmd);
  return 1;

}

void init(){

  char *command = malloc(MAX_LEN * sizeof(char));

  PS1 = "$";
  CWD = getcwd(CWD, PATH_MAX);
  HOME = getenv("HOME");
  PATH = getenv("PATH");

  // printf(" %s\n", PS1);
  // printf(" %s\n", CWD);
  // printf(" %s\n", HOME);
  // printf(" %s\n", PATH);

  FILE *sushrc;

  sushrc = fopen(strcat(CWD, "/.sushrc"), "r");

  if(sushrc != NULL){
  // execute any commands that are in sushrc
    while(fgets(command, MAX_LEN, sushrc)){
      cmdExecute(command);
    }
  free(command);
  }

  fclose(sushrc);

}

void mainloop(){
  char *command = malloc(sizeof(char) * MAX_LEN);

  while(1){
    printf("%s", PS1);

    fgets(command, MAX_LEN, stdin);

    if(feof(stdin) != 0){
      break;
    }

    cmdExecute(command);
  }
}

int main(int argc, char const *argv[]) {

  // Initialize variables from .sushrc or set them to default
  init();

  // Execute mainloop and stay there until program is terminated
  mainloop();

  return 0;
}
