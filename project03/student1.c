#include <stdio.h>
#include "machine.h"

/* CMSC 216, Spring 2021, Project #3
 * Public test 1 (public01.c)
 *
 * Tests calling print_instruction() on a few types of instructions.
 *
 * (c) Larry Herman, 2021.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

#define PROGRAM_SIZE 10

int main(void) {
  Wrd program[PROGRAM_SIZE]= {0xc8200014, 0xc8400006, 0x08650000, 0x688d0000,
                              0xc8200000, 0x68ac8000, 0x70ac8000, 0x78a40000,
                              0x78880000, 0x284c0000};
  unsigned short location= -1;
  int result;
  result = is_safe(program, PROGRAM_SIZE, &location);
  printf("%d\n", result);
  return result;
}
