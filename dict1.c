/* Dictionary V1 (Duplicates stored as any other node)
	Written by Marishka Nicol Magness
	Student ID: 805654
	mmagness@student.unimelb.edu.au */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "bst1.h"
#include "dict1.h"



int main(int argc, char *argv[]){
  bst_t *tree;
  tree = make_tree(compare_name, key_compare);
  int cycle;
  str_t key;
  FILE *rawdata, *output;
  rawdata = fopen(argv[1], "r");
  tree = scan_fill(tree, rawdata);
  fclose(rawdata);
  output = fopen(argv[2], "w");

  /* test print whole tree */

  while (scanf("%[^\n]", key) == 1){
    /* cycles through keys provided and searches for them in the bst */
    cycle = (int)search_tree(tree, &key, print_data, output);
    print_cycle(&key, &cycle);
    fgetc(stdin);
  }
  fclose(output);
  traverse_tree(tree, free_nodes);
  free_tree(tree);    //Free memory
  tree = NULL;
  return 0;
}

/* Compares key in data structure */
int compare_name(void *athinfo1, void *athinfo2){
  athinfo_t *data1 = athinfo1, *data2 = athinfo2;
  return strcmp((char*)data1->name, (char*)data2->name);
}

/* Compares key-node */
int key_compare(void *key, void *athinfo){
  athinfo_t *data = athinfo;
  str_t *keywords = key;
  return strcmp((char*)keywords, (char*)data->name);
}

/* Prints the number of cycles for each search */
void print_cycle(str_t *key, int *cycle){
  printf("%s --> %d\n\n", *key, *cycle);
}

/* Prints the data in data structure to specified file */
void print_data(void *datain, void *filename){
  athinfo_t *datanode = datain;
  FILE* output = filename;
  int i;
  fprintf(output,"%s --> ID: %d",
    (char*)datanode -> name,
    datanode -> ID
    );

  for (i = 0; i < INFSIZE; i++) {
    fprintf(output,"%s%s || ", dataheaders[i], (char*)datanode -> info[i]);
  }
  fprintf(output, "\n\n");
}

/* Scans datafile provided and fills a bst with data supplied */
void *scan_fill(bst_t *tree, FILE *rawdata){
  athinfo_t *new;
  str_t dname;
  line_t dinfo;
  int dID;
  /*Fills the struct with the given information */
  while ((fscanf(rawdata,
    "%d, %[^,] %[^\n]" ,&dID, dname, dinfo)) != EOF) {
      fgetc(rawdata);             //skip over trailing characters
      new = malloc(sizeof(*new));
      assert(new!=NULL);
      new->name = (str_t*)malloc(1+strlen(dname));
      strcpy((char*)new -> name, dname);
      new -> ID = dID;

      /* Breaks info string into token info */
      char *tmp = strtok(dinfo, ",");
      int i = FALSE;

      while (tmp != NULL){
        new->info[i] = (str_t*)malloc(1+strlen(tmp));
        strcpy((char*)new -> info[i], tmp);
        tmp = strtok(NULL, ",");
        i++;
      }
    /* Insert info into tree */
    tree = fill_tree(tree, new);
    }
  return tree;
}

void free_nodes(void *infostruct){
  athinfo_t *data = infostruct;
  int i;
  free(data->name);
  for(i=0;i<INFSIZE;i++){
    free(data->info[i]);
  }
  free(data);
}

/* Test functions */
void test_print(void *datain){
  athinfo_t *datanode = datain;
  printf("testprint\n");
  printf("testhelptest %s --> ID: %d \n",
  (char*)datanode -> name,
  datanode -> ID);
}
