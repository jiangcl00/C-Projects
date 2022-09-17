#include <stdio.h>
#include <assert.h>
#include "simple-sserver.h"


int main(void) {
  Commands commands;

  commands= read_commands("public08.compile-cmds", "student.test-cmds");

  assert(compile_program(commands) == 1);
  /* only two tests in public08-test-cmds succeeded */
  assert(test_program(commands) == 0);

  printf("No assertion remains unsatisfied!\n");
  
  return 0;
}