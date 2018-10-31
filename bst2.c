/* Binary Search Tree V2
	Written by Marishka Nicol Magness
	Student ID: 805654
	mmagness@student.unimelb.edu.au */

  /** This version implements key search with a key-node comparison with
  duplicates stored in a linked list **/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst2.h"

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

/* Attaches new nodes to existing list */
listnode_t *insert_list(listnode_t *list, node_t *newnode){
  list_t *new;
  new = (list_t*)malloc(sizeof(*new));
  assert (list!= NULL && new!= NULL);
  new->data = newnode->data;
  new->next = NULL;
  if (list->foot == NULL){
    /*First node in the list */
    list->head = list->foot = new;
  } else {
    list->foot->next = new;
    list->foot = new;
  }
  return list;
}

/* Creates and allocates memory for a linked list */
listnode_t *make_list(void){
  listnode_t *list;
  list = (listnode_t*)malloc(sizeof(*list));
  assert(list!=NULL);
  list->head = list->foot = NULL;
  return list;
}

/* Recursive inserts data into nodes in the bst */
static node_t *recursive_insert(node_t *root, node_t *new,
  int cmp(void*, void*)){
    if(!root){
      return new;
    } else if(cmp(new->data, root->data) < 0){
      /* If new data is less than or equal to root, add node to the left */
      root -> left = recursive_insert(root -> left, new, cmp);
    } else if(cmp(new->data, root->data) == 0){
      /*If new data is a duplicate of root, add to a linked list */
      if(root->linked == NULL){
        /* No linked list attached to node, make new */
        root->linked = make_list();
        root->linked = insert_list(root->linked, root);
      } else {
        /* There is already a linked list, append new node */
        root->linked = insert_list(root->linked, root);
      }
    } else {
      /* If new data is more than root, new node is added to the right */
      root-> right = recursive_insert(root -> right, new, cmp);
    }
    return root;
  }

/* Fills tree with nodes*/
bst_t *fill_tree(bst_t *tree, void *infostruct){
  node_t *new;
  new = malloc(sizeof(*new));
  assert(new!= NULL && tree!= NULL);
  /*add data and left right nodes to the new node */
  new -> data = infostruct;
  new -> left = new -> right = NULL;
  new -> linked = NULL;
  tree -> root = recursive_insert(tree->root, new, tree->cmp);
  if(new->linked){
    printf("linked list allocated\n");
  }
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

/*Free memory allocated to tree and list function */
void free_tree(bst_t *tree){
  assert(tree!=NULL);
  recursive_free(tree->root);
  free(tree);
}

/* Frees memory allocated to list and listnodes */
void free_list(listnode_t *list){
  if(!list){
    return;
  }
  list_t *this;
  assert(list!=NULL);
  while(list->head!=list->foot){
    this = list->head;
    list->head = list->head->next;
    free(this);
    this = NULL;
  }
  free(list->head);
  free(list->foot);
  free(list);
  list = NULL;
  list->head = list->foot = NULL;
}

/* Cycles through a linked list and performs an action on each node*/
static int *recursive_action(listnode_t *list,
  void action(void*, void*), int *cycle, FILE *filename){
  if(!list){
    /* Linked list has no data, duplicate not found */
    return cycle;
  }
  list_t *curr, *next;
  curr = list->head;
  next = curr->next;

  while (curr!= list->foot){
    action(curr->data, filename);
    curr = next;
    next = curr->next;
  }
  return cycle;
}

/* Cycles through the tree for key-node comparisons */
static int *recursive_search(node_t *root, str_t *key, int kcmp(void*, void*),
  void action(void*, void*), int *cycle, FILE *filename){
    int outcome = kcmp(key, root->data);
    if(!root) {
      /* Tree has no data */
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
       all duplicates will be on the linked-list node onwards,
       no more key-node comparisons will be performed*/
      action(root->data, filename);
      *cycle += TRUE;
      if(root->linked != NULL){
      /* Duplicates for this node found */
        return recursive_action(root->linked, action, cycle, filename);
      } else {
        return cycle;
      }
    }
}

/* Function to search tree and perform function on key-node matches */
int *search_tree(bst_t *tree, str_t *key, void action(void*, void*),
  FILE *output){
  assert(tree!=NULL);
  int cycle = 0;
  int* cp = &cycle;
  recursive_search(tree->root, key, tree->kcmp, action, cp, output);
  return cycle;
}

/* test codes */

static void recursive_list(listnode_t *list, void action(void*)){
  if(list==NULL || list->head == NULL){
    return;
  }
  printf("free list nodes\n");
  if(list->head!=NULL){
    list_t *node;
    node = list->head;
    list->head = list->head->next;
    assert(node->data!=NULL);
    action(node->data);
    printf("free list nodes p2\n");
    return recursive_list(list, action);
  }
}

static void recursive_traverse(node_t *root, void action(void*)){
  if(root){
    recursive_traverse(root->left, action);
    action(root->data);
    recursive_traverse(root->right, action);
    recursive_list(root->linked, action);
    }
}

void traverse_tree(bst_t *tree, void action(void*)){
  assert(tree!=NULL);
  recursive_traverse(tree->root, action);
}
