/* Dictionary Header V1
	Written by Marishka Nicol Magness
	Student ID: 805654
	mmagness@student.unimelb.edu.au */


/* Structure Declaration */

/* A structure (node) that stores the information of a single athlete */
typedef struct {
	int ID;									/* Unique ID of athlete */
	str_t *name;							/* Name of athlete */
	str_t *info[INFSIZE];		/* Array of recorded data on the athlete */
} athinfo_t;

/* Array of Athelete information Headers */
const char * dataheaders[] = {
  	"Sex: ",
  	"Age: ",
  	"Height: ",
  	"Weight: ",
  	"Team: ",
  	"NOC: ",
  	"Games: ",
  	"Year: ",
  	"Season: ",
  	"City: ",
  	"Sport: ",
  	"Event: ",
  	"Medal: ",
	};

/*Function Prototypes */
int compare_name(void *name1, void *name2);
void print_cycle(str_t *key, int *cycle);
void print_data(void *datanode, void *filename);
void *scan_fill(bst_t *tree, FILE *rawdata);
void free_nodes(void *infostruct);
int key_compare(void *key, void *athinfo);
void free_tree(bst_t *tree);
void test_print(void *datain);
