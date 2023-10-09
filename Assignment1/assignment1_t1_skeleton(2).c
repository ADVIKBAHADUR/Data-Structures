#include<stdio.h>
#include<stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>  //for isalnum

// NB: this skeleton is here to help you - ignore anything that does not help you
// There are a lot of others (and better!) ways of doing this

// note this sekeleton uses a global variable. It therefore will only work with 
// one hashtable, of the size set. In general global variables should be avoided
// as their global scope makes it very challenging to see where they are updated 
// (as it can be anywhere!), and don't work well when several threads/programs
// update them at the same time (concurency), amongst others problems.
// Having said that, they can make coding a bit easier, so that's why we are using 
// one here. If you can, try using a hashTable as a variable, passing it as a 
// parameter to functions!



#define MAX_STRING_SIZE 20 //max length of a string
#define ARRAY_SIZE 59  //best be prime
#define NAME_PROMPT "Enter term to get frequency or type \"quit\" to escape\n>>> " //you can use this string as your invitation to the user
#define NEW_LINE_PROMPT ">>> " //you can use this string as your invitation to the user where the user should input the name

typedef struct Element Element;
struct Element{
    // TODO1
};

Element* hashTable[ARRAY_SIZE];
int collisions = 0;
int num_terms = 0;

int hash_function(char* s){
    int hash = 0;
    while(*s){
       hash = (hash + *s - 'A') %ARRAY_SIZE;
        s++;
    }
    return hash;
}

Element* createNewElement(char* name){
    // TODO2
    // you might want to use the function strcpy from the string package here!
	return NULL;
}


// returns the element with name name or NULL if the element is not present
Element* search (char* name){
    //TODO4

    return NULL;
}

// assuming that no element of key name is in the list (use search first!), add element at the correct place in the list
// NB: it would be more efficient for search to return the index where it should be stored directly, but aiming for simplicity here!
void insert(char* name){
   // TODO3
  
}

// prints the number of occurences, or 0 if not in the file
void printNumberOfOccurences(char* name){
    //TODO5
}

//searches the name in the array, if it is there increment its count, if not, add it
void addOrIncrement(char* name){
    //TODO6
}



// From assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_token ( char *buf, FILE *f, int string_max ) {
	// start by skipping any characters we're not interested in
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
	// read string of alphanumeric characters
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);                // get next character from file
		if( !isalnum(buf[i]) ) { 
            if(buf[i]!=' '){ // we still want to keep spaces
                break; // only load letters and numbers
            }
        } 
		if( feof(f) ) { break; }          // file ended?
		if( i < (string_max-1) ) { ++i; } // truncate strings that are too long
	}
	buf[i] = '\0'; // NULL terminate the string
}


//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file ( char *fname ) {
	FILE *f;
	char buf[MAX_STRING_SIZE];

	// boiler plate code to ensure we can open the file
	f = fopen(fname, "r");
	if (!f) { 
		printf("Unable to open %s\n", fname);
		return 0; 
	}
	
	// read until the end of the file
	while ( !feof(f) ) {
		next_token(buf, f, MAX_STRING_SIZE);
		addOrIncrement( buf);
	}
    
    printf("File %s loaded\n", fname);
    float load = 0; //TODO7
    printf(" Capacity: %i\n Num Terms: %i\n Collisions : %i\n Load: %f\n", ARRAY_SIZE, num_terms, collisions,load);
	// always remember to close your file stream
	fclose(f);

	return 1;
}


int main ( int argc, char *argv[] ) {
    
	//TODO0
	//advice: follow the TODO number order
	//first test insert and search
    //then move on to addOrIncrement
    //only then worry about loading the file - see the function above and assignment 0 as to have to use arguments for your executable
    //and later again about an interactive interface - see the assignment 0 solution and the #define strings above

    
    
    return 0;
}