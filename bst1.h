/* Binary Search Tree Header V1
	Written by Marishka Nicol Magness
	Student ID: 805654
	mmagness@student.unimelb.edu.au */

/* Preset defined values */

#define MAXSTR 128			/* Max characters allowed per string */
#define MAXLINE 512			/* Max characters allowed per line */
#define MAXCHAR 3				/* Max characters allowed per short string */
#define MAXVAL 50				/* Max number allowed per array */
#define INFSIZE 13			/* Number of information fields */

#define TRUE 1				/* For all true values */
#define FALSE 0				/* For all false values */
#define INV -1 				/* For various invalid or unset values */

/* Structure Declaration */

/* Sets the maximum number of characters allowed for strings*/
typedef char str_t[MAXSTR+1];
typedef char ltr_t[MAXCHAR+1];
typedef char line_t[MAXLINE+1];

/* Some of the following structures have been referenced from "Programming,
 Problem Solving, and Abstraction with C (Revised Edition)"
 written by Alistair Moffat */

typedef struct node node_t;

struct node {
	void *data; 				/*pointer to stored structure */
	node_t *left;				/*left subtree of node */
	node_t *right;			/*right subtree of node */
};

typedef struct {
	node_t *root;								/* root node */
	int (*cmp)(void*, void*); 	/* function pointer */
	int (*kcmp)(void*, void*);  /* keynode pointer */
}bst_t;


/*Function Prototypes */
bst_t *make_tree(int func(void*, void*), int func2(void*, void*));
bst_t *fill_tree(bst_t *tree, void *infostruct);
int *search_tree(bst_t *tree, str_t *key, void action(void*, void*), FILE *output);
void traverse_tree(bst_t *tree, void action(void*));
