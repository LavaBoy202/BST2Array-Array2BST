#include <assert.h>
#include <stdlib.h>
#include "bst.h"
#include <stdio.h>

/////////////////////////////////////////////////////////////////////////////
// The following functions have been
// provided for your convenience
//
// You WILL have to MODIFY them
/////////////////////////////////////////////////////////////////////////////


struct bst *bst_create_empty(void) {
  struct bst *tree = malloc(sizeof(struct bst));
  tree->root = NULL;
  return tree;
}


static struct bstnode *new_leaf(int i, int idex) {
  struct bstnode *leaf = malloc(sizeof(struct bstnode));
  leaf->item = i;
  leaf->left = NULL;
  leaf->right = NULL;
  leaf->count = idex;
  return leaf;
}


bool bst_contains(int i, const struct bst *tree) {
  assert(tree);
  struct bstnode *node = tree->root;
  while (node) {
    if (node->item == i) {
      return true;
    }
    if (i < node->item) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return false;
}

// this is an iterative version of bst_insert
// you could replace this with a recursive version if you prefer
void bst_insert(int i, struct bst *tree) {
  assert(tree);
  struct bstnode *node = tree->root;
  struct bstnode *parent = NULL;
  while (node) {
    if (node->item == i) {
      return;
    }
    parent = node;
    if (i < node->item) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  if (parent == NULL) {  // tree was empty
    tree->root = new_leaf(i, 0);
  } else if (i < parent->item) {
    parent->left = new_leaf(i, 0);
  } else {
    parent->right = new_leaf(i, 0);
  }

  struct bstnode *nodes = tree->root;
  struct bstnode *parents = NULL;
  while (nodes) {
    if (nodes->item == i) {
      nodes->count++;
      return;
    }
    parents = nodes;
    if (i < nodes->item) {
      parents->count++;
      nodes = nodes->left;
    } else {
      parents->count++;
      nodes = nodes->right;
    }
  }
}

// this is an iterative version of bst_remove
// you could replace this with a recursive version if you prefer
void bst_remove(int i, struct bst *tree) {
  assert(tree);
  struct bstnode *target = tree->root;
  struct bstnode *target_parent = NULL;
  // find the target (and its parent)
  while (target && target->item != i) {
    trace_int(target->count);
    trace_int(target->item);
    target->count--;
    target_parent = target;
    if (i < target->item) {
      target = target->left;
    } else {
      target = target->right;
    }
  }
  if (target == NULL) {
    return; // key not found
  }
  // find the node to "replace" the target
  struct bstnode *replacement = NULL;
  if (target->left == NULL) {
    replacement = target->right;
    replacement->count = target->count; //changes
  } else if (target->right == NULL) {
    replacement = target->left;
    replacement->count = target->count; //changes
  } else {
    // neither child is NULL:
    // find the replacement node and its parent
    replacement = target->right;
    struct bstnode *replacement_parent = target;
    while (replacement->left) {
      replacement_parent->count--; //changes
      replacement_parent = replacement;
      replacement = replacement->left;
    }
    replacement_parent->count--;
    // update the child links for the replacement and its parent
    replacement->left = target->left;
    replacement->count = target->count;
    if (replacement_parent != target) {
      replacement_parent->left = replacement->right;
      replacement->right = target->right;
    }
  }
  // free the target, and update the target's parent
  free(target);
  if (target_parent == NULL) {
    tree->root = replacement;
    tree->root->count = replacement->count;
  } else if (i > target_parent->item) {
    target_parent->right = replacement;
  } else {
    target_parent->left = replacement;
  }
}

static int select_node(int k, struct bstnode *node) {
  assert(node && 0 <= k && k < node->count);
  int left_count = 0;
  if (node->left) {
    left_count = node->left->count;
  }
  if (k < left_count) {
    return select_node(k, node->left);
  }
  if (k == left_count) {
    return node->item;
  }
  return select_node(k - left_count - 1, node->right);
}


int bst_select(int k, struct bst *tree) {
  assert(tree);
  return select_node(k, tree->root);
}


static void free_bstnode(struct bstnode *node) {
  if (node) {
    free_bstnode(node->left);
    free_bstnode(node->right);
    free(node);
  }
}


void bst_destroy(struct bst *tree) {
  assert(tree);
  free_bstnode(tree->root);
  free(tree);
}

/////////////////////////////////////////////////////////////////////////////
// The following functions are for you to implement:
// (only PARTIAL documentation shown for CRITICAL information)
/////////////////////////////////////////////////////////////////////////////

// note: if tree is empty, then len is set to 0 and NULL is returned
// effects: modifies *len to store the length of the array
//          allocates memory (caller must free)
// time: O(n)
int *bst_to_sorted_array(const struct bst *tree, int *len){
  assert(len);
  assert(tree);
  if (tree->root == NULL) {
    return NULL;
  }
  *len = tree->root->count;
  int *a = malloc(*len * (sizeof (int)));
  for(int i = 0; i <= *len - 1; i++) {
    a[i] = select_node(i, tree->root);
  }
  return a;
}
struct bst *array_to_bst (int array[], int start, int end, struct bst *t) {
  assert(t);
  int midpoint;
  if (start > end) {
    return t;
  }
  if (((start + end) % 2) == 0) {
    midpoint = ((start + end) / 2);
  }
  else{
    midpoint = (((start + end) / 2) + 1);
  }
  bst_insert(array[midpoint], t);
  array_to_bst(array, start, midpoint - 1, t);
  array_to_bst(array, midpoint + 1, end, t);
  return t;
}


  // note: if a is NULL then len == 0 (and vice versa) and an empty tree is
  //       returned
  // requires: a is either NULL or an ascending sorted array
  //             without duplicates [not asserted]
  //           len >= 0
  // time: O(n)
  struct bst *bst_create_balanced(int a[], int len){
    struct bst *t = bst_create_empty();
    if (len == 0){
      return t;
    }
    //return t;
    return array_to_bst(a, 0, len - 1, t);
  }
