#include <stdio.h>
#include <assert.h>
#include "functions.h"


int main(void) {
  long result;
  assert(prism_area(1, 1, 1) == 6);

  result= jacobsthal(1) + ith_digit(1111, 2);
  /* this assertion will always be true, regardless of what your
     jacobsthal() and ith_digit() functions return */
  assert(result == 1 || result != 1);
  assert(prism_area(-1, 1, 1) == -1);
  
  assert(jacobsthal(-1) ==-1);
  assert(jacobsthal(6) == 21);
  assert(jacobsthal(0) ==0);
  assert(jacobsthal(1) ==1);
  assert(jacobsthal(2) ==1);
  assert(jacobsthal(4) ==5);
  assert(jacobsthal(5) ==11);
  assert(jacobsthal(7) ==43);

  assert(ith_digit(-216, 3) ==2);
  assert(ith_digit(-216, 4) ==-1);
  assert(ith_digit(-216, 1) ==6);
  assert(ith_digit(-216, 2) ==1);
  assert(ith_digit(216, 3) ==2);
  assert(ith_digit(216, 1) ==6);
  assert(ith_digit(216, 11) ==-1);
  assert(ith_digit(216216,8) ==-1);
  assert(ith_digit(216216, 6) ==2);
  assert(ith_digit(216216, 4) ==6);
  assert(ith_digit(216216, 2) ==1);
  assert(ith_digit(216216, 1) ==6);
  
  printf("\nThe test passed!\n");

  return 0;
}