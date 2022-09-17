#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "prio-q.h"
#include "compare-name-lists.h"
#include "memory-checking.h"

int main(void) {
  Prio_que prio_q;
  char *elements[]= {"Rocky Racoon", "Earl Squirrel", "Sally Salamander",
                     "Shelly Sheep", "Robin Robin", "Giselle Gazelle",
                     "Neil Seal", "Placido Flamingo"};
  int priorities[]= {90, 40, 60, 20, 30, 50, 70, 45};
  char *expected_elements[]= {"Rocky Racoon", "Neil Seal", "Sally Salamander",
                              "Giselle Gazelle", "Placido Flamingo",
                              "Earl Squirrel", "Robin Robin", "Shelly Sheep"};
  int expected_priorities[]= {90, 70, 60, 50, 45, 40, 30, 20};
  int i;

  init(&prio_q);

  for (i= 0; i < ARRSIZE(elements); i++)
    enqueue(&prio_q, elements[i], priorities[i]);

  assert(change_priority(&prio_q, "Placido Flaming", 45) == 0);

  for (i= 0; i < ARRSIZE(expected_elements); i++)
    assert(get_priority(prio_q, expected_elements[i]) ==
           expected_priorities[i]);

  printf("Yet another test worked right!\n");

  return 0;
}
