#include <stdio.h>
#include "machine.h"
#include <assert.h>

/* CMSC 216, Spring 2021, Project #3 0xd5a07d64

 */

#define PROGRAM_SIZE 8

int main(void) {
  Wrd program[PROGRAM_SIZE]= {0xb8407d64, 0xb8607d64, 0xb8a07d64, 0xb8807d64, 0x00298000, 0x084e0000, 0x10728000, 0xd5a07d64};
  unsigned short location= -1;
  int i;

  for (i= 0; i < PROGRAM_SIZE; i++) {
    print_instruction(program[i]);
    printf("\n");
  }
  
  assert(where_set(program, PROGRAM_SIZE, -1) == -1);
  assert(is_safe(program, 32765, NULL) == 0);
  printf("?\n");
  assert(disassemble(NULL, PROGRAM_SIZE, &location) == 0);
  return 0;
}