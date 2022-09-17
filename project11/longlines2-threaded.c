#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "randomdelay.h"




static void *get_file_count(void *arg);

static void *get_file_count(void *arg) {
  char *file = (char*) arg;
  long one_file_count, line_length;
  char ch;
  FILE *fp;
  long *result = malloc(sizeof(*result));
  
  fp= fopen(file, "r");  /* open file for reading */
  
  if (fp != NULL) {

    one_file_count= 0;
    line_length= 0;
    
    /* randomdelay(&file);  */
    
    while ((ch= fgetc(fp)) != EOF) {  /* read by character */
      if (ch != '\n')
        line_length++;
      else {
        if (line_length > 80)
          one_file_count++;

        line_length= 0;  /* reset for the next line */
      }
    }
    
    if (line_length > 80)
      one_file_count++;
    
    fclose(fp);
    /*printf("%ld\n", one_file_count);*/
    *result = one_file_count;
  } 
  return result;
}

int main(int argc, char *argv[]) {
  long all_files_total= 0;
  int i;
  void **file_counts;
  pthread_t *tids;

  file_counts= malloc(sizeof(*file_counts)*(argc-1));
  tids = malloc(sizeof(*tids)*(argc-1));
  
  if (argc > 1) {
    for (i= 0; i < argc-1; i++) {
      pthread_create(&tids[i], NULL, get_file_count, argv[i+1]);
    }
    for (i= 0; i < argc-1; i++) {
      pthread_join(tids[i], &file_counts[i]);
      all_files_total += *(long*)file_counts[i];
      free(file_counts[i]);
    }
    
  }
  free(file_counts);
  free(tids);
  printf("%ld\n", all_files_total);

  return 0;
}