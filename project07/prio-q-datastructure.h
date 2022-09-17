
/* This priority queue is implemented using the linked list structure.
   This linked list is a singly linked with a dummy head; it has no pointer
   point to the tail. 
   Every node will have the string data stored, the priority, and pointer 
   that points to the next node. */
typedef struct node {
  char *data;
  unsigned int priority;
  struct node *next;
} Prio_que;
