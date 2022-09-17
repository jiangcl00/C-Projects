#include <stdio.h>
#include "student.h"
#include <stdlib.h>
#include <string.h>

/* Name: Changlin Jiang
 * TerpConnect login ID: jiangcl
 * university ID: 117243543
 * Discussion section number: 0102
 * 
 * I pledge on my honor that I have not given or received any unauthorized
 * assistance on this assignment.
 */
 
void init_student(Student *const student, const char first_name[],
                  const char last_name[]){
  if (student != NULL && first_name != NULL && last_name != NULL) {
    student->first_name = malloc(sizeof(first_name));
    student->last_name = malloc(sizeof(last_name));
    strcpy(student->first_name, first_name);
    strcpy(student->last_name, last_name);
  }
  
}
Student *create_student(const char first_name[], const char last_name[]){
  Student *s;
  if (first_name == NULL || last_name == NULL) 
    return NULL;
  s = malloc(sizeof(Student));
  s->first_name = malloc(sizeof(first_name));
  s->last_name = malloc(sizeof(last_name));
  strcpy(s->first_name, first_name);
  strcpy(s->last_name, last_name);

  return s;
}
void print_student(Student student){
  if (student.last_name != NULL) 
    printf("%s, ", student.last_name);
  if (student.last_name != NULL)
    printf("%s", student.first_name);
}
unsigned int change_first_name(Student *const student, const char new_name[]){
  if (student != NULL && new_name != NULL) {
    free(student->first_name);
    student->first_name = malloc(sizeof(new_name));
    strcpy(student->first_name, new_name);
    return 1;
  }
  return 0;
}
unsigned int change_last_name(Student *const student, const char new_name[]){
  if (student != NULL && new_name != NULL) {
    free(student->last_name);
    student->last_name = malloc(sizeof(new_name));
    strcpy(student->last_name, new_name);
    return 1;
  }
  return 0;
}
unsigned int add_nickname(Student *const student, const char nickname[]){
  if (student != NULL && nickname != NULL) {
    strcat(student->first_name, " (");
    strcat(student->first_name, nickname);
    strcat(student->first_name, ")");
    return 1;
  }
  return 0;
}
int compare(Student student1, Student student2){
  int cmp_last, cmp_first;
  cmp_last = strcmp(student1.last_name, student2.last_name);
  cmp_first = strcmp(student1.first_name, student2.first_name);
  
  if (cmp_last == 0)
    return cmp_first;
  else
    return cmp_last;
}
unsigned int reset_student(Student *const student){
  if (student != NULL) {
    free(student->last_name);
    free(student->first_name);
    student->last_name = NULL;
    student->first_name = NULL;
    return 1;
  }
  return 0;
}
unsigned int free_student(Student **const student){
  if (student != NULL && *student != NULL) {
    free((**student).last_name);
    free((**student).first_name);
    free(*student);
    *student = NULL;
    return 1;
  }
  return 0;
}
