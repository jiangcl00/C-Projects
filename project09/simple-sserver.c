#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <err.h>
#include <sysexits.h>
#include <sys/wait.h>
#include "safe-fork.h"
#include "split.h"
#include "simple-sserver.h"

/* Name: Changlin Jiang
 * TerpConnect login ID: jiangcl
 * university ID: 117243543
 * Discussion section number: 0102
 * 
 * I pledge on my honor that I have not given or received any unauthorized
 * assistance on this assignment.
 */
 
 
/* This code is able to read and store two lists of commands from two external
 * file in a data structure, free all dynamically-allocated memory in the data
 * structure that stores commands, execute the commands for compiling code 
 * using process control, and execute the commands for testing code using 
 * process control.
 */
 
 


/* This function will read two lists of commands from two external files, 
   whose names are the two parameters to this function. It will return a type 
   Commands that contain the two stored lists of commands that were read. 
   These commands will be stored in a linked list with a dummy header. 
   Each node after the dummy header will only have either compile command or 
   test command stored while the other one will be NULL. 
   Compile commands will all be stored first and then test commands come after 
   the last compile command stored.*/
Commands read_commands(const char compile_cmds[], const char test_cmds[]) {
  FILE *fp; 
  FILE *compile_file;
  FILE *test_file;
  char line[LINE_MAX];
  Commands head, *curr;

  /* open files from two parameters */
  compile_file = fopen(compile_cmds, "r");
  test_file = fopen(test_cmds, "r");
  
  /* exit with exit status of 1 if either parameter is NULL or is the name of 
     a file that doesn't exist, or if any error occurs trying to open either 
     file for reading*/
  if (compile_cmds == NULL || test_cmds == NULL || compile_file == NULL 
      || test_file == NULL)
    exit(1);
  
  fclose(compile_file);
  fclose(test_file);
  
  /* dummpy header */
  head.compile_cmd = NULL;
  head.test_cmd = NULL;
  head.next = NULL;

  fp = fopen(compile_cmds, "r");
  
  if (fp != NULL ) {
    /* loop to store commands into the linked list from compile_cmds file */
    while (fgets(line, sizeof(line), fp)) {
      Commands *node  = malloc(sizeof(Commands));
      node->compile_cmd = malloc(strlen(line)+1);
      node->test_cmd = NULL;
      strcpy(node->compile_cmd, line);
      node->next = NULL;
      
      if (head.next == NULL) {
        head.next = node;
        curr = head.next;
      } else {
        curr->next = node;
        curr = curr->next;
      }
    }
    fclose(fp);
  }
  
  fp = fopen(test_cmds, "r");
  
  if (fp != NULL) {
    /* loop to store commands into the linked list from test_cmds file */
    while (fgets(line, sizeof(line), fp)) {
      Commands *node  = malloc(sizeof(Commands));
      node->test_cmd = malloc(strlen(line)+1);
      node->compile_cmd = NULL;
      strcpy(node->test_cmd, line);
      node->next = NULL;
      
      if (head.next == NULL) {
        head.next = node;
        curr = head.next;
      } else {
        curr->next = node;
        curr = curr->next;
      }
    }
    fclose(fp);
  }
  
  return head;
}

/* This function deallocate all dynamically-allocated memory used by the 
   Commands variable its parameter points to. */
void clear_commands(Commands *const commands) {
  Commands *curr, *next;

  if (commands != NULL) {
    curr = commands->next;
    
    while (curr != NULL) {
      next = curr->next;
      if (curr->compile_cmd)
        free(curr->compile_cmd);
      if (curr->test_cmd)
        free(curr->test_cmd);
      free(curr);
      curr = next;
    }
  }
}

/* This function will execute the compilation commands stored in its parameter
   commands that has been read by the function read_commands(). It will create 
   a child process to execute each command and the commands will be executed 
   in the same order as in the input file. 
   It will return 0 if the commands all execute successfully. 
   If any command has error, it will stop executing commands and return 1. 
   If the first argument to read_commands() was the name of an empty file, 
   then no commands will be executed, and 0 will be returned. */
int compile_program(Commands commands) {
  int count = 0;
  int status;
  pid_t pids[20];
  Commands *curr = commands.next;
  
  /* return 0 if there is no command */
  if (curr->compile_cmd == NULL)
    return SUCCESSFUL_COMPILATION;
  /* loop for each compile command */
  while (curr != NULL && curr->compile_cmd != NULL) {
    /* create a child process for each compile command */
    if ((pids[count] = safe_fork()) == 0) {
      char **cmds = split(curr->compile_cmd);
      int i;
      
      for (i = 0; cmds[i] != NULL; i++) {
        /* input redirection */
        if (strcmp(cmds[i], "<") == 0) {
          int fd1 = open(cmds[i+1], O_RDONLY);
          dup2(fd1, STDIN_FILENO);
          close(fd1);
        }
        /* output redirection */
        if (strcmp(cmds[i], ">") == 0) {
          int fd2 = open(cmds[i+1], FILE_FLAGS, FILE_MODE);
          dup2(fd2, STDOUT_FILENO);
          close(fd2);
        }
      }
      /* execute the command */
      execvp(cmds[0], cmds);
      err(EX_OSERR, "exec error");
    }
    
    /* wait for the child process to execute and return 1 if there is error */
    waitpid(pids[count], &status, 0);
    if (!WIFEXITED(status) || WEXITSTATUS(status))
      return FAILED_COMPILATION;
      
    curr = curr->next;
    count++;
  }

  return SUCCESSFUL_COMPILATION;
}

/* This functions will execute the list of test commands in commands, and the 
   commands will be executed in the same order as in the input file. 
   It will execute all commands even if any command it is executing has an 
   error, it will continue execute any remaining commands and keep track how 
   many of its commands executed successfully and return the count. 
   If there are not test commands in commans, then no commands will be 
   executed, and 0 will be returned. */
int test_program(Commands commands) {
  int count=0;
  int status;
  int pass = 0;
  pid_t pids[20];
  Commands *curr = commands.next;
  
  /* return 0 if there is no command */
  if (curr == NULL)
    return 0;
  
  /* find the first node after compile commands */
  while (curr->compile_cmd != NULL) 
    curr = curr->next;
  
  /* loop for each test command */
  while (curr != NULL && curr->test_cmd != NULL) {
    /* create a child process for each test command */
    if ((pids[count] = safe_fork()) == 0) {
      char **cmds = split(curr->test_cmd);
      int i;
      
      for (i = 0; cmds[i] != NULL; i++) {
        /* input redirection */
        if (strcmp(cmds[i], "<") == 0) {
          int fd1 = open(cmds[i+1], O_RDONLY);
          dup2(fd1, STDIN_FILENO);
          close(fd1);
        }
        /* output redirection */
        if (strcmp(cmds[i], ">") == 0) {
          int fd2 = open(cmds[i+1], FILE_FLAGS, FILE_MODE);
          dup2(fd2, STDOUT_FILENO);
          close(fd2);
        }
      }
      /* execute the command */
      execvp(cmds[0], cmds);
      err(EX_OSERR, "exec error");
    }
    
    /* wait for the child process to execute and keep track of how many of them
       successfully executed */
    waitpid(pids[count], &status, 0);
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
      pass++;
      
    curr = curr->next;
    count++;
  }
  
  return pass;
}