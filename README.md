# Binary-Search-Tree

This is a uni project that tests the number of key comparisons between a Binary Search Tree that uses a linked list to store duplicates and one that doesn't.

BST V1: Stores duplicate information in nodes as part of the main tree.
BST V2: Stores duplicate informaton in nodes of a linked list where only the node head is a part of the main tree

bst -> all tree related functions 
dict -> main function and other non-tree related functions

How to Use:

make the file using a terminal, run the program in stdin according to the format below, the number of comparisons made will be printed in stdout and the key-value pair will be in the output file created in the same folder as the program.

The program takes at least 3 arguements from stdin:
{dictionary} {datafile} {output file} {keyfile/keys}

dictionary - the bst version you'd like to call
datafile - the complete data of which the bst is to be filled with
output file - a file that contains all information found on the keys searched
keyfile/keys - keys you wants found in the dictionary, stored either in a file seperated by newlines or typed in stdin

