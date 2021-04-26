#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


int main(void) {
  struct bst *t = bst_create_empty();
  bst_insert(50, t);
  bst_insert(20, t);
  bst_insert(80, t);
  bst_insert(10, t);
  bst_insert(40, t);
  bst_insert(70, t);
  bst_insert(90, t);
  bst_insert(0, t);
  bst_insert(30, t);
  bst_insert(60, t);
  trace_bst(t);

  int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  struct bst *tree = bst_create_balanced(data, 10);
  trace_bst(tree);
  bst_destroy(tree);
  assert(bst_contains(50, t));
  assert(bst_select(5, t) == 50);
  bst_remove(50, t);
  trace_bst(t);
  assert(!bst_contains(50, t));
  assert(bst_select(5, t) == 60);

  //free(tree);
  bst_destroy(t);
}
