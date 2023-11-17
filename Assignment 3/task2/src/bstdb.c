#include "bstdb.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY 120000
const int range =240000;
int total_insertions = 0;
int total_tree_movements_insert = 0;
double avg_movement = 0;
double time_for_init = 0;
clock_t start_time;

typedef struct Tree_Node{
	struct Tree_Node *leftnode;
    struct Tree_Node *rightnode;
	int id;
    char *name;
	int wordcount;
	char *author;
} Tree_Node;
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int arrindex = 0;
int *myarray;

Tree_Node *Database = NULL;

void tree_delete(Tree_Node* root){
        if (root != NULL){
            tree_delete(root -> leftnode);
            tree_delete(root -> rightnode);
            free(root);
        }

    }

int bstdb_init ( void ) {
	clock_t t = clock();
	start_time = clock();
	srand(time(NULL));
	myarray = (int *)malloc(range * sizeof(int));

    // Initialize the myarray with consecutive numbers
    for (int i = 0; i < ARRAY; i++) {
     myarray[i] = i % range;
    }
    // Fisher-Yates shuffle
    for (int i = ARRAY - 1; i > 0; i--) {
        int j = rand() % (i + 1);
		int * myi = &myarray[i];
		int * myj = &myarray[j];
        swap( myi,  myj);
    }

	Database = (Tree_Node *)malloc(sizeof(Tree_Node));
	if(Database == NULL){
		return 0;
	}
	Database-> leftnode = NULL;
	Database-> rightnode = NULL;
	Database-> id = range/2;
	Database-> name = NULL;
	Database-> wordcount = 0;
	t = clock() - t;
	time_for_init = ((double)t)/CLOCKS_PER_SEC;
	return 1;
}
void Insert_Tree_Node(Tree_Node** root, int id, char *name, int wordcount, char *author){
    if (*root == NULL){
		//printf("gotit");
        *root = (Tree_Node*)malloc(sizeof(Tree_Node));
        (*root)->id = id;
        (*root)->leftnode = NULL;
        (*root)->rightnode = NULL;
		(*root)->name = name;
        (*root)->wordcount = wordcount;
        (*root)->author = author;
    }
    else if (id <= (*root)->id){
		total_tree_movements_insert++;
        Insert_Tree_Node(&((*root)->leftnode), id, name, wordcount, author);
    }
    else if (id > (*root)->id){
		total_tree_movements_insert++;
        Insert_Tree_Node(&((*root)->rightnode), id, name, wordcount, author);
    }

}
int bstdb_add ( char *name, int word_count, char *author ) {

	// Seed the random number generator
	total_insertions++;
	int id = myarray[arrindex];
	arrindex++;
    if (Database->id == range/2) {
        Insert_Tree_Node(&Database, id, name, word_count, author);
        return id;
    } else{
		return(Database->id);
	}
}
Tree_Node* tree_search(Tree_Node* root, int id){
        if (root == NULL){
			printf(" %d ", id);
            return NULL;
        }
        else{
            if ( root -> id == id){
                return root;
            }
            else{
                if ( id < root -> id){
                    return tree_search(root -> leftnode, id);
                }
                    else{
                        return tree_search(root -> rightnode, id);
            }
            }

            
        }
    }

int bstdb_get_word_count ( int doc_id ) {

	Tree_Node *subject = tree_search(Database, doc_id);
	if ( subject == NULL){
		return -1;
	}
	else{
		return subject -> wordcount;
	}
}

char* bstdb_get_name ( int doc_id ) {

	Tree_Node *subject = tree_search(Database, doc_id);
	if ( subject == NULL){
		return 0;

	}
	else{
		return subject -> name;
	}

}

void bstdb_stat ( void ) {
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
	avg_movement = total_tree_movements_insert/total_insertions;
	clock_t duration = clock() - start_time;
	double time_taken = ((double)duration)/CLOCKS_PER_SEC;
	printf("STATS:\n");
	printf("Total leaves nodes pass through before insertion: %d \n", total_tree_movements_insert);
	printf("Average no of leaves passed through: %f \n", avg_movement);
	printf("Time Taken for initiation function: %f seconds \n", time_for_init);
	printf("Time Taken for total program to run: %f seconds \n", time_taken);
}

void
bstdb_quit ( void ) {

	tree_delete(Database);
}
