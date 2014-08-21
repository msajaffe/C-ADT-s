#include <stdlib.h>
#include "strqueue.h"
#include <string.h>
#include <assert.h>
struct llnode{
  char str;
  struct llnode *next;
};
struct strqueue{
   struct llnode *front;
   struct llnode *back;
   int length;
};
// create_StrQueue(): creates a new StrQueue
//   PRE:  true
//   POST: caller must call destroy_StrQueue
//   TIME: O(1)
StrQueue create_StrQueue(void){
  StrQueue new = malloc(sizeof(struct strqueue));
  new->front = new->back = NULL;
  new->length = 0;
  return new;
}
// destroy_StrQueue(sq): frees the memory occupied by sq
//     and frees every string still in the queue
//   PRE:  sq is a valid StrQueue (not NULL)
//   POST: sq is no longer valid
//   TIME: O(n), where n is sq_length(sq)
void destroy_StrQueue(StrQueue sq){
   assert(sq);
   struct llnode *p = sq->front;
   if(sq_length(sq)){
      while(p!=NULL){
         struct llnode *n = p->next;
         free(&p->str);
         free(p);
         p = n;
      }
   }
   free(sq);
}

// sq_add_back(sq, str): makes a copy of str and places it at the
//     end of the queue
//   PRE:  sq is a valid StrQueue (not NULL)
//         str is not NULL.
//   POST: sq length increased by 1
//         a copy of str is now at the end of sq
//   TIME: O(n), where n is strlen(str)
void sq_add_back(StrQueue sq, const char *str){
   assert(sq && str);
   struct llnode *new = malloc(sizeof(struct llnode));
   char *newstr = malloc(sizeof(char)*strlen(str));
   strcpy(newstr, str);
   sq->back->next = new;
   sq->back = new;
   new->next = NULL;
   new->str = *newstr;    
   sq->length++;
}


// sq_remove_front(sq): returns the string that was first in the queue 
//     or NULL if empty
//   PRE:  sq is a valid StrQueue (not NULL)
//   POST: if sq is empty, returns NULL 
//         otherwise, returns the first string (caller must free)
//         and sq length decreased by 1
//   TIME: O(1)
char *sq_remove_front(StrQueue sq){
   assert(sq);
   char *retval = malloc(sizeof(char)*strlen(&sq->front->str));
   strcpy(retval, &sq->front->str);
   struct llnode *second = sq->front->next;
   free(&sq->front->str); 
   free(sq->front);
   sq->front = second;
   sq->length--;
   return retval;
}


// sq_length(sq) returns the number of items in the queue.
//   PRE:  sq is a valid StrQueue (not NULL)
//   POST: returns int >= 0
//   TIME: O(1)
int sq_length(StrQueue sq){
   assert(sq);
   return sq->length;
}
