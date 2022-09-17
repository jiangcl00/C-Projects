#include<stdio.h>

/* Name: Changlin Jiang
 * TerpConnect login ID: jiangcl
 * university ID: 117243543
 * Discussion section number: 0102
 * 
 * I pledge on my honor that I have not given or received any unauthorized
 * assistance on this assignment.
 */
 
 
/* This program checks if the input line has more than 80 characters by
 * generating one output line or two output lines.
 * 
 * The first output line has a single blank space (if the length of the current
 * input line was 80 or less) or a single asterisk (if the line's length was 
 * more than 80), the current input line number in a field of 5 places (filled 
 * with blank spaces if the number is less than 5 digits), a colon, a single 
 * blank space, all the characters from the current input line, and a newline.
 *
 * The second output line is generated only when the length of the current 
 * input line is longer than 80. This line has exactly 88 blank spaces, and 
 * then enough caret characters underneath every character of the input line
 * that is beyond the 80th position.
 * 
 */

int main(void) {
  char curr_line[1000];
  char curr_char;
  int count = 0;
  int length = 0;
  int line_num = 0;
  int caret_num = 0;
  int i = 0;
  int j = 0;
  int k = 0;
  
  while (scanf("%c", &curr_char) != EOF) {
    if (curr_char != '\n') {
      curr_line[count] = curr_char; /* store characters in the current line */
      count++;
      
      /* check the appearance of tab character, and
         increment the actual length */
      if (curr_char == '\t') 
        length  += 8 - (length % 8);
      else
        length++;
      
    } else { /* print out the first output line for current line */
      line_num++;
      /* print a single blank space if the length is not greater than 80
         print a single asterisk if the length is greater than 80 */
      if (length <= 80)
        printf(" "); 
      else
        printf("*");
      
      printf("%5d", line_num); /* print out line number in 5 places */
      printf(": ");
      
      /* print out all the characters from the current input line */
      for (i = 0; i < count; i++)
        printf("%c", curr_line[i]);
      printf("\n");
      
      /* print out the second output line for current line 
         if the length is greater than 80 */
      if (length > 80) {
        caret_num = length - 80;
        for (j = 0; j < 88; j++) 
          printf(" ");
        for (k = 0; k < caret_num; k++)
          printf("^");
          
        printf("\n");
      }
      
      /* reset count and length for next line */
      count = 0;
      length = 0;
    }
  } 
  
  return 0;
}
