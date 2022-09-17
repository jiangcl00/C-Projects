/* This Commands struct is implemented using the linked list structure.
   This linked list is a singly linked with a dummy head; it has no pointer
   point to the tail. 
   
   Every node will have the compile command or test command 
   stored (not both, one of them must be NULL), and pointer 
   that points to the next node. 
   
   Each node will only have either compile command or test command,  and 
   compile commands will all be stored first and then test commands come after 
   the last compile command stored.*/

typedef struct node{
  char *compile_cmd;
  char *test_cmd;
  struct node *next;
}Commands;