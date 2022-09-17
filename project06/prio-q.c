#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prio-q.h"

#define MAX_STRING_NUM 1000
#define MAX_STRING_SIZE 400

/* Name: Changlin Jiang
 * TerpConnect login ID: jiangcl
 * university ID: 117243543
 * Discussion section number: 0102
 * 
 * I pledge on my honor that I have not given or received any unauthorized
 * assistance on this assignment.
 */
 
 
/* This code has multiple functions that don't print any output. These 
 * functions either modifythe Prio_que parameter, or return a value, or both.
 * 
 * This code is able to enqueue the priority queue, check the queue to see if 
 * it is empty, get the size of the queue, get the highest priority element, 
 * dequeue the priority queue, and get an array that contains all string 
 * elements (ends with a NULL).
 */



/* initialize the Prio_que variable that prio_q is pointing to.
   prio_q is pointing to a dummy head that is not the actual element,
   and it links to the next element, which is currently NULL.*/
void init(Prio_que *const prio_q){
  if ( prio_q != NULL) {
    prio_q->data = NULL;
    prio_q->next = NULL;
  }
}

/* store new_element with the priority priority into prio_q, and return 1
   the new element will be inserted into the queue according to its priority.
   if prio_q is NULL, the input priority already exists, or priority is 
   negative, the function will return 0 without modifying the queue prio_q. */
unsigned int enqueue(Prio_que *const prio_q, const char new_element[],
                     unsigned int priority){
  Prio_que *curr, *prev, *new_item = NULL;
  int result = 0;
  prev = prio_q;
  
  /* return 0 if new_element is NULL or priority is negative */
  if (new_element == NULL || priority < 0)
    return 0;

  if (prio_q != NULL) {
    curr = prio_q->next;

    /* find first element in list that's less than or equal to the one we
       want to insert */
    while (curr != NULL && curr->priority > priority) {
      prev = curr;
      curr = curr->next;
    }
    /* return 0 if the priority already exists*/
    if (curr != NULL && curr->priority == priority)
      return 0;
      
    /* create new node and if memory allocation succeeded fill in its
       fields */
    new_item = malloc(sizeof(*new_item));  
    if (new_item != NULL) {
      new_item->data = malloc(strlen(new_element)+1);
      strcpy(new_item->data, new_element);
      new_item->priority = priority;
      new_item->next = curr;

      if (prev != NULL && prev->priority == -1)
        prio_q->next = new_item;  /* inserting new first element */
      else prev->next = new_item;  /* inserting elsewhere */

      result = 1;
    }
  }

  return result;
}

/* return 1 if no element was stored in prio_q, and 0 if there are any element
   being stored. */
unsigned int is_empty(const Prio_que prio_q){
  if (prio_q.next == NULL)
    return 1;
  return 0;
}

/* return the number of elements that were stored in prio_q. */
unsigned int size(const Prio_que prio_q){
  int count = 0;
  Prio_que *curr = prio_q.next;
  
  while (curr != NULL) {
    count++;
    curr = curr->next;
  }
  
  return count;
} 

/* return the string of the element in prio_q that has the highets priority, 
   without removing it; return NULL if prio_q is empty. */
char *peek(Prio_que prio_q){
  char* highest;
  
  if (is_empty(prio_q)) 
    return NULL;
    
  highest = malloc(strlen(prio_q.next->data)+1);
  strcpy(highest, prio_q.next->data);
  
  return highest;
}

/* return the string of the element in prio_q that has the highets priority, 
   and remove it from prio_q; return NULL if the parameter prio_q is NULL or 
   prio_q is empty. */
char *dequeue(Prio_que *const prio_q){
  char* highest;
  Prio_que *temp;
  if (prio_q == NULL || is_empty(*prio_q)) 
    return NULL;
    
  highest = malloc(strlen(prio_q->next->data)+1);
  strcpy(highest, prio_q->next->data);
  temp = prio_q->next;
  free(prio_q->next->data);
  prio_q->next = temp->next; /* make the dummy point to a new head */
  free(temp);
  
  return highest;
}

/* return an array of the elements stored in the queue in order of decreasing
   priority.
   there should be n + 1 elements stored into the array from the queue that has
   n elements and the last element of the array will be NULL 
   if the queue is empty, the array will still have one element NULL. */
char **get_all_elements(Prio_que prio_q){
  Prio_que *curr = prio_q.next;
  char ** elements = malloc(MAX_STRING_NUM * sizeof(char*));
  int count = 0;
  
  /* storing string into the array until the end of queue is reached */
  while (curr != NULL) {
    elements[count] = malloc(MAX_STRING_SIZE * sizeof(char));
    strcpy(elements[count++], curr->data);
    curr = curr->next;
  }
  
  return elements;
}
