
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// very incomplete small test program...

int main() {
  LIST *lst1;
  LIST *lst2;
  int i;

  lst1 = lst_create();
  lst2 = lst_create();

  for(i=0; i<5; i++) {
     lst_push_front(lst1, 3);
  }
  /*for(i=0; i<5; i++) {
     lst_push_back(lst1, i);
  }*/
  for(i=0; i<6; i++) {
     lst_push_front(lst2, i);
  }
  /*for(i=5; i<11; i++) {
     lst_push_back(lst2, i);
  }*/
  
  
  printf("lst_length(lst1) : %i\n", lst_length(lst1));
  printf("lst1 contents: ");
  lst_print(lst1);
  printf("lst_length(lst2) : %i\n", lst_length(lst2));
  printf("lst2 contents: ");
  lst_print(lst2);


  //lst_pop_front(lst1);
  //lst_pop_front(lst1);
  lst_merge_sorted(lst1,lst2);
  printf("lst1 contents after sorting: ");
  lst_print(lst1);



  /** TODO:  test code here! **/
  if(lst_are_equal(lst1, lst2)) {
		printf("Linked List 1 and Linked List 2 are equal.\n");
	} else {
	  printf("Linked List 1 and Linked List 2 are not equal.\n");
	}

  /** test code for lst_count **/

  printf("number of 3's = %i\n", lst_count(lst1, 3));
  printf("number of 0's = %i\n", lst_count(lst1, 0));


  /** test code for lst_print_rev **/
  //lst_print_rev(lst1);




  /** test code for lst_push_back **/
  //lst_reverse(lst1);
  
  

  lst_free(lst1);
  lst_free(lst2);
}
  
