#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include "mmstack.h"
struct llnode{
	int item;
  struct llnode *next;
  int min;
  int max;
};

struct mmstack {
	struct llnode *top;
  int len;
};

// create_MMStack() creates a new empty stack
//   PRE:  true
//   POST: client must eventually call destroy_MMStack
//   TIME: O(1)
MMStack create_MMStack(void){
	MMStack newstack = malloc(sizeof(struct mmstack));  
  newstack->top = NULL;
  newstack->len = 0;
  return newstack;
}

// destroy_MMStack(mms) empties the stack and frees all memory
//   PRE:  mms is a valid MMStack
//   POST: all memory for mms is freed, and mms is no longer valid
//   TIME: O(n), where n = mms_length(mms)
void destroy_MMStack(MMStack mms){
  assert(mms);
  struct llnode *ptr_top = mms->top; 
  while(ptr_top!=NULL){
  	struct llnode *temp = ptr_top->next;
    free(ptr_top);
    ptr_top = temp;
  }
  free(mms);
}

// mms_length(mms) returns the number of entries in mms
//   PRE:  mms is a valid MMStack
//   POST: returns int >= 0
//   TIME: O(1)
int mms_length(MMStack mms){
	assert(mms);
  return mms->len;
}

// mms_push(mms, i) puts i on the top of the mms
//   PRE:  mms is a valid MMStack
//   POST: length of mms is updated
//   TIME: O(1)
void mms_push(MMStack mms, int i){
	assert(mms);
  struct llnode *newnode = malloc(sizeof(struct llnode)); 
  newnode->item = i;
  if (mms->len == 0){ 
    newnode->next = NULL;
  	newnode->min = i;
    newnode->max = i;
  }
  else if (i > mms->top->max){
  	newnode->next = mms->top;
    newnode->max = i;
    newnode->min = mms->top->min;
  }
  else if (i < mms->top->min){
  	newnode->next = mms->top;
    newnode->max = mms->top->max;
    newnode->min = i;
  }
  mms->top = newnode;           
  mms->len++;
}

// mms_pop(mms) removes and returns item from the top of the mms
//   PRE:  mms is a valid MMStack
//         mms_length(mms) > 0
//   POST: length of mms is updated
//   TIME: O(1)
int mms_pop(MMStack mms){
	assert(mms && mms_length(mms) > 0);
  int retval = mms->top->item;
  struct llnode *top = mms->top->next;
  free(mms->top);
  mms->top = top;
  mms->len--;
  return retval;
}

// mms_min(mms) returns the minimum item stored in the mms
//   PRE:  mms is a valid MMStack
//         mms_length(mms) > 0
//   POST: returns min int stored in mms
//   TIME: O(1)
int mms_min(MMStack mms){
	assert(mms && mms_length(mms) > 0);
  return mms->top->min;
}

// mms_max(mms) returns the maximum item stored in the mms
//   PRE:  mms is a valid MMStack
//         mms_length(mms) > 0
//   POST: returns max int stored in mms
//   TIME: O(1)
int mms_max(MMStack mms){
  assert(mms && mms_length(mms) > 0);
  return mms->top->max;
}