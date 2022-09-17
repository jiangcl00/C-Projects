#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <err.h>
#include <sysexits.h>
#include "safe-fork.h"

int main(int argc, char *argv[]) {
  pid_t pid1, pid2;
  int pipefd[2];
  int num1, num2;
  
  if (argc < 2) 
    exit(2);
    
  pipe(pipefd);
  pid1= safe_fork(); 
  
  if (pid1 == 0) {
  /*child 1*/
   dup2(pipefd[1], STDOUT_FILENO);
   close(pipefd[0]);
   close(pipefd[1]);
   execl("./remove-comments.x", "./remove-comments.x", argv[argc - 1], NULL);
   err(EX_OSERR, "execl error");
   
  } else {
    dup2(pipefd[0], STDIN_FILENO);
    scanf("%d", &num2);
    pid2= safe_fork();
    
    if (pid2 == 0) {
      /*child 2*/
      dup2(pipefd[1], STDOUT_FILENO);
      close(pipefd[0]);
      close(pipefd[1]);
      execl("/bin/wc", "wc", "-m", argv[argc - 1], NULL);
      err(EX_OSERR, "execl error");
      
    } else {
      /*parent*/  
      scanf("%d", &num1);
      close(pipefd[0]);
      close(pipefd[1]);
      
      if (num1 >= 2 * num2) {
        printf("Enough comments!\n");
        exit(0);
      } else {
        printf("Too few comments!\n");
        exit(1);
      }
    }
  }
  

  return 0;
}