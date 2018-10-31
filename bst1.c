/* Binary Search Tree V1
	Written by Marishka Nicol Magness
	Student ID: 805654
	mmagness@student.unimelb.edu.au */

  /** This version implements key search by key-node comparisons through
  the whole tree **/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bst1.h"

/* Some of the following functions have been referenced from "Programming,
 Problem Solving, and Abstraction with C (Revised Edition)"
 written by Alistair Moffat */

/* Create a tree function */
bst_t *make_tree(int func(void*, void*), int func2(void*, void*)){
  bst_t *tree;
  tree = malloc(sizeof(*tree));
  assert(tree!=NULL);
  /*Create empty root */
  tree -> root = NULL;
  tree -> cmp = func;
  tree -> kcmp = func2;
  return tree;
}

/* Recursive inserts data into nodes in the bst */
static node_t *recursive_insert(node_t *root, node_t *new,
  int cmp(void*, void*)){
    if(root == NULL){
      /* Empty tree, new node is tree root */
      return new;
    } else if(cmp(new->data, root->data) <= 0){
      /* If new data is less than or equal to root, add node to the left */
      root -> left = recursive_insert(root -> left, new, cmp);
    } else {
      /* If new data is more than root, new node is added to the right */
      root-> right = recursive_insert(root -> right, new, cmp);
    }
    return root;
  }

/* Fill tree with nodes function */
bst_t *fill_tree(bst_t *tree, void *infostruct){
  node_t *new;
  new = malloc(sizeof(*new));
  assert(new!= NULL && tree!= NULL);
  /*add data and left right nodes to the new node */
  new -> data = infostruct;
  new -> left = new -> right = NULL;
  tree -> root = recursive_insert(tree->root, new, tree->cmp);
  return tree;
}

/* Frees memory previously allocated to nodes and list */
static void recursive_free(node_t *root){
  if(root){
    recursive_free(root->left);
    recursive_free(root->right);
    free(root);
    root = NULL;
  }
}

/*Free memory allocated to tree function */
void free_tree(bst_t *tree){
  assert(tree!=NULL);
  recursive_free(tree->root);
  free(tree);
}

/* Cycles through the corresponding left nodes of tree to
find more duplicates*/
static int *recursive_action(node_t *root, str_t *key, int kcmp(void*, void*),
  void action(void*, void*), int *cycle, FILE *filename){
  int outcome = kcmp(key, root->data);
  if(!root){
    *cycle += TRUE;
    return cycle;
  } else if ((outcome!= 0) && (root->left != NULL)){
    *cycle += TRUE;
    return recursive_action(root->left, key, kcmp, action, cycle, filename);
  } else if ((outcome!= 0) && (root->left == NULL)){
    *cycle += TRUE;
    return cycle;
  } else if ((outcome == 0) && (root->left == NULL)){
    action(root->data, filename);
    *cycle += TRUE;
    return cycle;
  } else {
    action(root->data, filename);
    *cycle += TRUE;
    return recursive_action(root->left, key, kcmp, action, cycle, filename);
  }
}

/* Cycles through the tree for key-node comparisons */
static int *recursive_search(node_t *root, str_t *key, int kcmp(void*, void*),
  void action(void*, void*), int *cycle, FILE *filename){
    int outcome = kcmp(key, root->data);
    if(!root) {
      return cycle;
    }else if(outcome < 0){
      *cycle += TRUE;
      /* Key is to the left branch of tree,
      search continues only to left node onwards */
      if(root->left == NULL){
        /* This node is a leaf, no duplicates found */
        fprintf(filename, "%s --> NOTFOUND \n\n", (char*)key);
        *cycle += TRUE;
        return cycle;
      } else {
        return recursive_search(root->left, key, kcmp, action,
          cycle, filename);
      }
    }else if (outcome > 0){
      *cycle += TRUE;
      /* Key is to the right branch of tree,
      search continues only to right node onwards */
      if(root->right == NULL){
        /* This node is a leaf, no duplicates found */
        fprintf(filename, "%s --> NOTFOUND \n\n", (char*)key);
        *cycle += TRUE;
        return cycle;
      } else {
        return recursive_search(root->right, key, kcmp, action,
          cycle, filename);
      }
    }else{
      /* Key match is found, action will be performed on match,
       all duplicates will be on the left node onwards*/
      action(root->data, filename);
      *cycle += TRUE;
      if(root->left != NULL){
        return recursive_action(root->left, key, kcmp, action, cycle, filename);
      }else{
        return cycle;
      }
    }
}

/* Function to search tree and perform function on key-node matches */
int *search_tree(bst_t *tree, str_t *key, void action(void*, void*), FILE *output){
  assert(tree!=NULL);
  int cycle = 0;
  int* cp = &cycle;
  recursive_search(tree->root, key, tree->kcmp, action, cp, output);
  printf("%d\n", cycle);
  return (int*)cycle;
}

/* traverses through tree and performs an action on each node */
static void recursive_traverse(node_t *root, void action(void*)){
  if(root){
    recursive_traverse(root->left, action);
    action(root->data);
    recursive_traverse(root->right, action);
  }
}

/*Performs action on all nodes in tree */
void traverse_tree(bst_t *tree, void action(void*)){
  assert(tree!=NULL);
  recursive_traverse(tree->root, action);
}
