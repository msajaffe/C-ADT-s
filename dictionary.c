#include "dictionary.h"
#include <assert.h>
#include <stdlib.h>
struct bstnode {
   void *key;
   void *value;
   struct bstnode *left;
   struct bstnode *right;
};

struct dictionary{
   struct bstnode *root;
   CompareFunction comp;
   FreeFunction free_keys;
   FreeFunction free_vals;
   int called;
};

// create_Dictionary(comp_k, free_k, free_v) creates a new Dictionary
//     that uses the comp_k function to compare keys
//     the free_k function to free keys and
//     the free_v function to free values
//   PRE:  comp_k, free_k and free_v are valid (non-NULL) function pointers
//   POST: caller must call destroy_Dictionary
//   TIME: O(1)
//   NOTE: comp_k(a,b) follows the strcmp(a,b) return convention
Dictionary create_Dictionary(CompareFunction comp_k, FreeFunction free_k, FreeFunction free_v){
   assert(comp_k && free_k && free_v);
   Dictionary dic = malloc(sizeof(struct dictionary));
   dic->comp = comp_k;
   dic->free_keys = free_k;
   dic->free_vals = free_v;
   dic->root = NULL;
   dic->called = 0;
   return dic;
}

void free_nodes(struct bstnode *p, FreeFunction free_k, FreeFunction free_v){
   struct bstnode *l = p->left;
   struct bstnode *r = p->right;
   free_k(p->key);
   free_v(p->value);
   free(p);
   if(l!=NULL){
      free_nodes(l, free_k, free_v);}
   if(r!=NULL){
      free_nodes(r, free_k, free_v);
   }
}
// destroy_Dictionary(dict): Frees all memory allocated for dict, 
//     and frees the memory for every key and every value
//   PRE:  dict is a valid Dictionary (not NULL)
//   POST: dict is no longer valid
//   TIME: O(n * f), where n is the number of items in Dictionary, f is time to free key & value
void destroy_Dictionary(Dictionary dict){
   assert(dict);
   if(dict->called!=0){
      free_nodes(dict->root, dict->free_keys, dict->free_vals);
   }
   free(dict);
}

void insert_node(struct bstnode *b,struct bstnode *p, void *k, void *v, Dictionary d){
   if(p != NULL){ 
   int result = d->comp(k, p->key);
      if(result > 0){
         insert_node(p, p->right, k, v, d);
      } else if (result < 0){
         insert_node(p, p->left , k, v, d);
      } else {
         d->free_vals(p->value);
         p->value = v;
      }
   }
   else {
     struct bstnode *new = malloc(sizeof(struct bstnode));
     d->called++;
     if(b!=NULL){
     int result = d->comp(k, b->key); 
      if(result < 0){
            b->left = new;
         } else if (result > 0){
            b->right = new;
         }
      new->key = k;
      new->value = v;
      new->right = new->left = NULL;
      } else {
         d->root = new;
         new->key = k;
         new->value = v;
         new->right = new->left = NULL;
      }   

   }
}
// insert(dict, k, v): insert the key/value pair k/v into the dictionary.
//     the client should not modify or free k or v after insert.
//     if the key k already exists, the previous value will be freed
//     and the value for k will be replaced with v.
//   PRE:  dict, k, and v are valid (not NULL)
//   POST: it will add the (k,v) pair into the dictionary
//         if k already existed, the previous value will be freed
//   TIME: O(h * c), where h is height of underlying BST, and c is time to compare two keys
void insert(Dictionary dict, void *k, void *v){
   assert(dict && k && v);
   insert_node(NULL, dict->root, k, v, dict);
}


// lookup(dict, k): returns the value associated with key k, if such
//     a value exists.  Otherwise, returns NULL.
//   PRE:  dict and k are valid (not NULL)
//   POST: returns a value or NULL
//   TIME: O(h * c), where h is height of underlying BST, and c is time to compare two keys
void *lookup(Dictionary dict, void *k){
   assert(dict && k);
   struct bstnode *t = dict->root;
   while (t) {
      int result = dict->comp(k, t->key);
         if (result < 0) {
            t = t->left;
         } else if (result > 0) {
            t = t->right;
         } else { 
            return t->value;
      }
   }
   return NULL; 
}
