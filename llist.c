#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
* See list.h for expected behavior of functions
**/

typedef struct node {
    ElemType val;
    struct node *next;
} NODE;


struct list_struct {
  NODE *front;
  NODE *back;
  int size;
};


/*
* returns pointer to newly created empty list
*/
LIST *lst_create() {
LIST *l = malloc(sizeof(LIST));

  l->front = NULL;
  l->back = NULL;
  l->size = 0;
  return l;
}

void lst_free(LIST *l) {
NODE *p = l->front;
NODE *pnext;

  while(p != NULL) {
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p);
    p = pnext;
  }
  // now free the LIST 
  free(l);
}

void lst_print(LIST *l) {
NODE *p = l->front;

  printf("[");
  while(p != NULL) {
    printf(FORMAT, p->val);
    p = p->next;
  }
  printf("]\n");
}


/**
* TODO:  
*   function:  lst_are_equal
*   description:  returns true(1) if lst1 and lst2
*      contain exactly the same sequenc of values.
*      Returns 0 otherwise.
**/
int lst_are_equal(LIST *lst1, LIST *lst2) {
  while(lst1->front != NULL && lst2->front != NULL){
    if(lst1->front->val != lst2->front->val) 
      return 0;
    lst1->front = lst1->front->next;
    lst2->front = lst2->front->next;
  }
  if (lst1->front != NULL) return 0;
  if (lst2->front != NULL) return 0;
  return 1;  // placeholder
}

/**
* TODO:  print in reverse order 
*
* Try to do without looking at notes!
* Hints:  recursive helper function
*/
void lst_rev_helper(NODE *node){
  if(!node)
    return;
  lst_rev_helper(node->next);
  printf(FORMAT, node->val);
}

void lst_print_rev(LIST *l) {
  NODE *node = l->front;
  if(node == NULL)
    return;
  printf("[");
  lst_rev_helper(node);
  printf("]\n");
}

void lst_push_front(LIST *l, ElemType val) {
NODE *p = malloc(sizeof(NODE));

  p->val = val;
  p->next = l->front;
  
  l->front = p;
  if(l->back == NULL)   // was empty, now one elem
      l->back = p;
}

void lst_push_back(LIST *l, ElemType val) {
  NODE *p;

  if(l->back == NULL)   // list empty - same as push_front
    lst_push_front(l, val);
  else {  // at least one element before push
    p = malloc(sizeof(NODE));
    p->val = val;
    p->next = NULL;
    l->back->next = p;

    l->back = p;  
  }
}

/** TODO 
*   modifications to enable this operation
*   to execute in O(1) time.  (You will almost
*   certainly modify other functions and the 
*   data structure itself -- see header).
**/
int lst_length(LIST *l) {
  return l->size;
}

int lst_is_empty(LIST *l) {
  return !l->front;
}


/** TODO
 *    function:  lst_count
*     description:  Counts number of occurrences 
*     		of x in the list and returns 
*     		that value.
*/
int lst_count(LIST *l, ElemType x) {
  NODE *node = l->front;
  int count = 0;
  while(node != NULL){
    if(node->val==x)
      count++;
    node = node->next;
  }
  return count; 
}


/* These are "sanity checker" functions that check to see
*     list invariants hold or not.
*/
int lst_sanity1(LIST *l) {
  if(l->front == NULL && l->back != NULL){
	fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
	return 0;
  }
  if(l->back == NULL && l->front != NULL){
	fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
	return 0;
  }
  return 1;
}

int lst_sanity2(LIST *l) {
  if(l->back != NULL && l->back->next != NULL) {
	fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
	return 0;
  }
  return 1;
}

/*
* function:  find_back()
* description:  returns a pointer to the last
*               node of the given list.
*		Note that we are operating at
*		the "node level".
*
*		if p is NULL, NULL is returned.
*
* purpose:  mostly for debugging -- enables sanity3
*/
static NODE * find_back(NODE *p) {

  if(p ==  NULL)
	return NULL;

  while(p->next != NULL) {
	p = p->next;
  }
  return p;
}

/*
*   makes sure that the back pointer is also the last reachable
*    node when you start walking from front.
*    HINT:  use pointer comparison
*/
int lst_sanity3(LIST *l) {
NODE *real_back;

  real_back = find_back(l->front);

  return (real_back == l->back);
}



ElemType lst_pop_front(LIST *l) {
ElemType ret;
NODE *p;
 

  if(lst_is_empty(l))
	return DEFAULT;   // no-op

  ret = l->front->val;
  
  if(l->front == l->back) {  // one element
	free(l->front);
	l->front = NULL;
	l->back = NULL;
  }
  else {
	p = l->front;  // don't lose node being deleted
	l->front = l->front->next;  // hop over
	free(p);
  }
  l->size--;
  return ret;
}

     
  


/* TODO 
*    
*    if list is empty, we do nothing and return arbitrary value
*    otherwise, the last element in the list is removed and its
*      value is returned.
*
*/
ElemType lst_pop_back(LIST *l) {
  ElemType ret;
  NODE *p;

  if(lst_is_empty(l))
	  return DEFAULT;   

  ret = l->back->val;
  
  if(l->back == l->front) {  
	  free(l->back);
	  l->front = NULL;
	  l->back = NULL;
  }
  while(p->next != l->back){
    p = p->next;
  }
  free(l->back);
  l->back = p;
  p->next = NULL;
  l->size--;
  return ret;
} 

/* TODO
*  For full credit, you cannot allocate any new memory!
*
*  description:  self-evident 
*/
void lst_reverse(LIST *l) {
  NODE *prev = NULL;
  NODE *current = l->front;
  NODE *next = NULL;
  while(current!=NULL){
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  l->front = prev;
}


/*
* removes first occurrence of x (if any).  Returns
*   0 or 1 depending on whether x was found
*/
int lst_remove_first(LIST *l, ElemType x) {
NODE *p;
NODE *tmp;

  if(l->front == NULL) return 0;
  if(l->front->val == x) {
	lst_pop_front(l);
	return 1;
  }
  // lst non-empty; no match on 1st elem
  p = l->front;

  while(p->next != NULL) {
     if(x == p->next->val) {
	tmp = p->next;
	p->next = tmp->next;
	if(tmp == l->back) 
	    l->back = p;
	free(tmp);
	return 1;
     }
     p = p->next;
  }
  return 0;
}


/**
* function: lst_remove_all_slow
* description:  removes all occurrences of x
*   from given list (if any).
*   Returns number of occurrences (i.e., deletions).
* 
* notes:  it is called "slow" because in the worst
*   case, it takes quadratic time.
*   (Discussion of why and when this happens is a
*   lecture topic).
*/
int lst_remove_all_slow(LIST *l, ElemType x) {
  int n=0;
  while(lst_remove_first(l, x))
    n++;
  return n;
}

/** 
 * function: lst_sra_bad_case (sra:  slow_remove_all)
 *
 * description: constructs a list of length n such that 
 * the above function takes quadratic time to remove
 * all occurrences of a specified value. 
 *
 * By convention, the specified value will be 0
 */
LIST *lst_sra_bad_case(int n) {
  LIST *l = lst_create();
  int i;
  int k=n/2;

  for(i=0; i<k; i++) {
    lst_push_front(l, 0);
  }
  for(i=0; i<n-k; i++) {
    lst_push_front(l, 1);
  }
  return l;
}

/** TODO
*   function:  lst_remove_all_fast
*   description:  same behavior/semantics as
*      lst_remove_all_slow.  However, this function
*      must guarantee linear time worst case 
*      runtime (hence, "fast").
*
*   REQUIREMENT:  linear worst-case runtime.
*
*   Note:  your solution may be either recursive or 
*   iteratieve.
**/
int lst_remove_all_fast(LIST *l, ElemType x) {
  int nodesDeleted = 0;
  LIST *temp = lst_create();
  if(l->front == NULL)
    return nodesDeleted;
  while(lst_length(l)>0){
    if(l->front->val==x){
      lst_pop_front(l);
      nodesDeleted++;
    }
    else if(l->front->val != x){
      lst_push_back(temp, l->front->val); 
      lst_pop_front(l);
    }
  }
  return nodesDeleted;
}

int lst_is_sorted(LIST *l){
NODE *p = l->front;

  while(p!=NULL && p->next != NULL) {
	if(p->val > p->next->val)
	  return 0;
	p = p->next;
  }
  return 1;
}



/** TODO
* function:  lst_insert_sorted
*
* description:  assumes given list is already in sorted order
*	   and inserts x into the appropriate position
* 	   retaining sorted-ness.
* Note 1:  duplicates are allowed.
*
* Note 2:  if given list not sorted, behavior is undefined/implementation
* 		dependent.  We blame the caller.
* 		So... you don't need to check ahead of time if it is sorted.
*/
void lst_insert_sorted(LIST *l, ElemType x) {
  NODE *current;
  NODE *head = l->front;
  if(head == NULL || x <= head->val)
    lst_push_front(l,x);
  else{
    current = head;
    while(current->next!=NULL && current->next->val < x){
      current = current->next;
    }
    NODE *insertNode = malloc(sizeof(NODE));
    insertNode->val = x;
    insertNode->next = current->next;
    current->next = insertNode;
  }
}

/** TODO
 * function:  lst_merge_sorted
 *
 * description:  assumes both list a and b are in
 * 	sorted (non-descending) order and merges them
 * 	into a single sorted list with the same
 * 	elements.  
 *
 * 	This single sorted list is stored in a while
 * 	b becomes empty.
 *
 * 	if either of given lists are not sorted, 
 * 	we blame the caller and the behavior is
 * 	implementation dependent -- i.e., don't worry
 * 	about it!
 *
 * 	Example:
 *
 * 		a:  [2 3 4 9 10 30]
 * 		b:  [5 8 8 11 20 40]
 *
 * 		after call on (a,b)
 *
 * 		a:  [2 3 4 5 8 8 9 10 11 20 30 40]
 * 		b:  []
 * 
 * implementation:  should not allocate ANY new list
 * 	nodes -- it should just re-link existing
 * 	nodes.
 *
 * 	Must be linear time in the |a|+|b| -- i.e.,
 * 	the total number of elements being processed.
 */

void lst_merge_sorted(LIST *a, LIST *b){
  NODE dummy;
  NODE *prev = &dummy;
  dummy.next = NULL;
  while(a->front != NULL && b->front!=NULL){
    if(a->front->val <= b->front->val){
      prev->next = a->front;
      a->front = a->front->next;
    } else {
      prev->next = b->front;
      b->front = b->front->next;
    }
    prev = prev->next;
  }
  if (a->front==NULL) prev->next = b->front;
  if (b->front==NULL) prev->next = a->front; 
  a->front = dummy.next;
}



/**
* TODO
* function:  lst_clone
*
* description:  makes a "deep copy" of the given list a
*   and returns it (as a LIST pointer).
*
*/
LIST * lst_clone(LIST *a) {
  LIST *list = lst_create();
  NODE *node = a->front;
  for(int i = 0; i<lst_length(a); i++){
    lst_push_back(list, node->val);
    node = node->next;
  }
  return list;
}



/**
* TODO
* function:  lst_from_array 
*
* description:  creates a new list populated with the
*      elements of array a[] in the same order as 
*      they appear in a[] (element at a[0] will be the
*      first element in the list and so-on).  List is
*      returned as a LIST pointer.
*
*      Parameter n indicates the length of the given array.
*
* runtime requirement:  THETA(n)
*/
LIST * lst_from_array(ElemType a[], int n){
  LIST *list = lst_create();
  for(int i = 0; i<n; i++){
    lst_push_back(list, a[i]);
  }
  return list;
}


/**
* TODO
* function:  lst_to_array 
*
* description:  allocates an array of ElemType and populates
*         it with the elements in the given list (as with
*         lst_from_array elements are in the same order in
*         both data structures).
*
* runtime requirement:  THETA(n)
*
*/
ElemType * lst_to_array(LIST *lst) {
  ElemType *arr = malloc(sizeof(ElemType)*lst_length(lst));
  NODE *curr = lst->front;

  int index = 0;
  while(curr!=NULL){
    arr[index++] = curr->val;
    curr = curr->next;
  }
  return arr;
}


/**
* TODO
* function:  lst_prefix
*
* description:  removes the first k elements from the
*               given list which are used to form a new list
*		which is then returned.
*
*		if n is the length of the given list, we have the
*		following boundary conditions:
*
*		  if k==0:
*			lst unchanged and an empty list returned
*		  if k>=n:
*			lst becomes empty and a list containing
*			all elements previously in lst is returned.
*
*		examples:
*
*		  EX1:  lst:  [2, 3, 9, 7, 8]
*			k:    3
*
*			after call:
*			   lst:  [7, 8]
*			   returned list:  [2, 3, 9]
*
*		  EX2  lst:  [2, 3, 9, 7, 8]
*			k:    0
*
*			after call:
*			   lst:  [2, 3, 9, 7, 8]  (unchanged)
*			   returned list:  []
*
*		  EX3  lst:  [2, 3, 9, 7, 8]
*			k:    5
*
*			after call:
*			   lst:  []
*			   returned list:  [2, 3, 9, 7, 8]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) worst case where n is the length of the given list
*
*       ORDERING:  the ordering of the returned prefix should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		   list).
*/
LIST * lst_prefix(LIST *lst, unsigned int k) {
  LIST *list = lst_create();
  if(k==0)
    return list;
  if(k>=lst_length(lst)){
    lst_concat(list, lst);
  }
  if(k<lst_length(lst)){
    for(int i =0; i<k; i++){
      lst_push_back(list,lst->front->val);
      lst_pop_front(lst);
    }
  }
  return list;
}




/**
* TODO
* function:  lst_filter_leq
*
* description:  removes all elements of the given list (lst) which
*		are less than or equal to a given value (cutoff)
*		
*		A list containing the removed elements is returned.
*
* examples:
*
*	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
*		cutoff:  4
*
*		after call:
*			lst:  [9, 8, 12, 7]
*			returned list:  [4, 2, 4, 3]
*
*       -----------------------------------------
*	EX2: 	lst:  [6, 5, 2, 1]
*		cutoff:  6
*
*		after call:
*			lst:  []
*	 		returned list:  [6, 5, 2, 1]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) where n is the length of the given list
*
*       ORDERING:  the ordering of the returned list should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		   list).
*			
*/
LIST * lst_filter_leq(LIST *lst, ElemType cutoff) {
  LIST *lessCutoff = lst_create();
	LIST *greaterCutoff = lst_create();
	if (lst->front == NULL) {
		return lessCutoff;
	}
	while (lst_length(lst) != 0){
		if (lst->front->val > cutoff){
			lst_push_back(greaterCutoff, lst->front->val);
			lst_pop_front(lst);
		}
		else if (lst->front->val <= cutoff){
			lst_push_back(lessCutoff, lst->front->val);
			lst_pop_front(lst);
		}
	}
	lst_concat(lst, greaterCutoff);
	return lessCutoff;
}

/**
* TODO
* function:  lst_concat
*
* description:  concatenates lists a and b; resulting
*    concatenation is reflected in list a; list b becomes
*    empty.
*
*    example:
*
*	EX1:  a: [2, 9, 1]
*	      b: [5, 1, 2]
*
*	after call:
*
*		a: [2, 9, 1, 5, 1, 2]
*		b: []
*
* REQUIREMENTS:  
*
*     runtime:  O(1)
*
*     sanity:  this operation makes sense when a and b
*		are distinct lists.  For example, we don't
*		want/allow the caller to do something like
*		this:
*
*			LIST *my_list;
*
*			lst_push_front(my_lst, 4);
*			lst_push_front(my_lst, 2);
*
*			lst_concat(my_lst, my_lst);
*
*		your implementation must detect if it is being
*		called this way.  If so the function does nothing
*		and (optionally) prints an error message to
*		stderr.
*	
*/
void lst_concat(LIST *a, LIST *b) {
  if (a==b || lst_length(b)==0)
    return;
  if(lst_length(a)==0)
    a = b;
  else if (lst_length(b)>0){
    a->back->next = b->front;
    a->back = b->back;
    a->size += b->size;
  }
  b->front = NULL;
  b->back = NULL;
  b->size = 0;
}
