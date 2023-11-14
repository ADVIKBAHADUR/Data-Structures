#include "bstdb.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.
#define MAX_ARRAY_SIZE 180000


typedef struct Tree_Node{
	int id;
    char *name;
	int wordcount;
	char *author;
    struct Tree_Node *left;
    struct Tree_Node *right;
} Tree_Node;


int keys = 0;
int sorted_keys[MAX_ARRAY_SIZE];


// void sort(array_size){

// }

Tree_Node *Library = NULL;

void tree_delete(Tree_Node* root){
        if (root != NULL){
            tree_delete(root -> left);
            tree_delete(root -> right);
            free(root);
        }
        //TODO
    }


int
bstdb_init ( void ) {

	// This function will run once (and only once) when the database first
	// starts. Use it to allocate any memory you want to use or initialize 
	// some globals if you need to. Function should return 1 if initialization
	// was successful and 0 if something went wrong.
	Library = (Tree_Node *)malloc(sizeof(Tree_Node));
	if(Library == NULL){
		return 0;
	}
	Library -> id = 0;
	Library -> name = NULL;
	Library -> wordcount = 0;
	Library -> left = NULL;
	Library -> right = NULL;

	return 1;
}
void insertion(Tree_Node** root, int id, char *name, int wordcount, char *author){
    if (*root == NULL){
        *root = (Tree_Node*)malloc(sizeof(Tree_Node));
        (*root)->id = id;
        (*root)->name = name;
        (*root)->wordcount = wordcount;
        (*root)->author = author;
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else if (id <= (*root)->id){
        insertion(&((*root)->left), id, name, wordcount, author);
    }
    else if (id > (*root)->id){
        insertion(&((*root)->right), id, name, wordcount, author);
    }
    // Note: If id is equal, you might want to decide what to do (skip or update).
}



int
bstdb_add ( char *name, int word_count, char *author ) {
	// This function should create a new node in the binary search tree, 
	// populate it with the name, word_count and author of the arguments and store
	// the result in the tree.
	//
	// This function should also generate and return an identifier that is
	// unique to this document. A user can find the stored data by passing
	// this ID to one of the two search functions below.
	//
	// How you generate this ID is up to you, but it must be an integer. Note
	// that this ID should also form the keys of the nodes in your BST, so
	// try to generate them in a way that will result in a balanced tree.
	//
	// If something goes wrong and the data cannot be stored, this function
	// should return -1. Otherwise it should return the ID of the new node
	int id = rand();
    if (Library->id == 0) {
        insertion(&Library, id, name, word_count, author);
        return id;
    } else {
        return -1;
    }
}

Tree_Node* tree_search(Tree_Node* root, int id){
        if (root == NULL){
            return NULL;
        }
        else{
            if ( root -> id == id){
                return root;
            }
            else{

            
                if ( id < root -> id){
                    return tree_search(root -> left, id);
                }
                    else{
                        return tree_search(root -> right, id);
            }
            }

            
        }

    }

int
bstdb_get_word_count ( int doc_id ) {

	// This is a search function. It should traverse the binary search tree
	// and return the word_count of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return -1
	Tree_Node *subject = tree_search(Library, doc_id);
	if ( subject == NULL){
		return -1;

	}
	else{
		return subject -> wordcount;
	}
}

char*
bstdb_get_name ( int doc_id ) {
	// This is a search function. It should traverse the binary search tree
	// and return the name of the node with the corresponding doc_id.
	//
	// If the required node is not found, this function should return NULL or 0
	Tree_Node *subject = tree_search(Library, doc_id);
	if ( subject == NULL){
		return 0;

	}
	else{
		return subject -> name;
	}

}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
}

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends. Use
	// it to free any memory you allocated in the course of operating the
	// database.
	tree_delete(Library);
}
