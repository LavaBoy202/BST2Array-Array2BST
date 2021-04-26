#include <stdbool.h>

///////////////////////////////////////
// DO NOT MODIFY THESE STRUCTURES
///////////////////////////////////////
struct bstnode {
  int item;
  struct bstnode *left;
  struct bstnode *right;
  int count;               // <-- new!
};

struct bst {
  struct bstnode *root;
};
///////////////////////////////////////


struct bst *bst_create_empty(void);

bool bst_contains(int i, const struct bst *tree);

void bst_insert(int i, struct bst *tree);

void bst_remove(int i, struct bst *tree);

int bst_select(int k, struct bst *tree);

void bst_destroy(struct bst *tree);

int *bst_to_sorted_array(const struct bst *tree, int *len);

struct bst *bst_create_balanced(int a[], int len);

void bst_insert_rebalance(int i, struct bst *tree);

void bst_compact(struct bst *tree);
