#include<stdio.h>

/* Name: Changlin Jiang
 * TerpConnect login ID: jiangcl
 * university ID: 117243543
 * Discussion section number: 0102
 * 
 * I pledge on my honor that I have not given or received any unauthorized
 * assistance on this assignment.
 */


/* This program reads the output from warnlines.c program (or the input data 
 * that follows the format of the output of warnlines.c program), and generates 
 * the line numbers of the input lines from the input of warnlines program 
 * that were longer than 80 characters.
 *  
 * The output line numbers are seperated by a single blank space, there should
 * only be spaces between numbers, not before the first number or after the
 * last number printed. The output always ends with a newline, no matter 
 * how many line numbers are printed.
 * 
 */
 
 
/* prototype of print_num function */
static void print_num(void);

/* print out the line number */
void print_num(void) {
  int num;
  scanf("%d", &num);
  printf("%d", num);
}

int main(void) {
  char curr_char;
  int found = 0; /* keep track of the line number printed */
  
  /* check if the first line's length is more than 80 */
  scanf("%c", &curr_char);
  if (curr_char == '*') {
    print_num();
    found++;
  }
  
  /* scan through the whole input */
  while (scanf("%c", &curr_char) != EOF) {
  
    /* check the first character after a newline */
    if (curr_char == '\n') {
      scanf("%c", &curr_char);
      
      /* print out line numbers and separate them with space */
      if (curr_char == '*') {
      
        if (found != 0)  
          printf(" ");
        print_num();
        found++;
      }
    }
  }
  printf("\n");
  return 0;
}
