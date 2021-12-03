#include <stdlib.h>

#ifndef BTREE_H
#define BTREE_H

typedef struct BTreeNode {
  struct BTreeNode *left;  // The zeroes
  struct BTreeNode *right; // The ones

  char value;
  int leftCount;
  int rightCount;
} BTreeNode;

BTreeNode *create_tree(char value) {
  BTreeNode *tree = malloc(sizeof(BTreeNode));
  tree->value = value;
  tree->leftCount = 0;
  tree->rightCount = 0;

  return tree;
}

/**
 * @brief Inserts a new value into the tree
 *
 * @param tree
 * @param value
 * @param counter
 */
void insert_value(BTreeNode *tree, unsigned int value, int counter) {
  if (counter == 0)
    return;
  counter--;

  char digitValue = (value & 1);
  if (digitValue) {
    if (tree->right == NULL) {
      tree->right = create_tree(1);
    }
    insert_value(tree->right, value >> 1, counter);
    tree->rightCount++;
  } else {
    if (tree->left == NULL) {
      tree->left = create_tree(0);
    }
    insert_value(tree->left, value >> 1, counter);
    tree->leftCount++;
  }
}

/**
 * @brief Determines the rating for either CO2 (false) or Oxygen (true)
 *
 * @param tree
 * @param searchMode
 * @param value
 */
void determine_rating(BTreeNode *tree, int searchMode, unsigned int *value) {
  *value <<= 1;
  *value |= tree->value;

  // Have we reached the end of the road?
  if (tree->left == NULL && tree->right == NULL)
    return;

  // We're looking for the most common
  if (searchMode) {
    if (tree->rightCount >= tree->leftCount) {
      if (tree->right == NULL)
        return;
      determine_rating(tree->right, searchMode, value);
    } else {
      if (tree->left == NULL)
        return;
      determine_rating(tree->left, searchMode, value);
    }
  }

  if (!searchMode) {
    if (tree->rightCount < tree->leftCount) {
      if (tree->right == NULL)
        return;
      determine_rating(tree->right, searchMode, value);
    } else {
      if (tree->left == NULL)
        return;
      determine_rating(tree->left, searchMode, value);
    }
  }
}

#endif