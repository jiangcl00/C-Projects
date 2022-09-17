/* Name: Changlin Jiang
 * TerpConnect login ID: jiangcl
 * university ID: 117243543
 * Discussion section number: 0102
 * 
 * I pledge on my honor that I have not given or received any unauthorized assistance on this assignment.
 */
 
#include "functions.h"

int prism_area(int l, int w, int h) {
  int area;
  
  if(l<=0 || w<=0 || h<=0){
    return -1;
  }
  area = 2  *( l * w + l * h + w * h );
  return area;
}

long jacobsthal(short n) {
  if(n < 0){
    return -1;
  }
  if(n == 0){
    return 0;
  }
  if(n == 1){
    return 1;
  }
  
  return 2 * jacobsthal(n-2) + jacobsthal(n-1);
}

short ith_digit(long n, unsigned short i) {
  int digit;
  int div = 1;
  int x;
  if(i==0){
    return -1;
  }
  if(n == 0){
    if(i == 1){
      return 0;
    }
    else{
      return -1;
    }
  }
  
  if(n < 0){
    n *= -1;
  }
  
  for(x = 0 ; x < i - 1 ; x ++){
    div = div*10;
  }
  
  if(n / div ==0){
    return -1;
  }
  
  digit = n/div;
  digit = digit % 10;
  return digit;
}

