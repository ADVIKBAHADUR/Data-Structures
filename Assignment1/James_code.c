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
	int key;
    char surname[MAX_STRING_SIZE];
	int count;
};

Element* hashTable[ARRAY_SIZE] = {0};
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
	Element* newElement = malloc(sizeof(Element));
	newElement->key = hash_function(name);
	strcpy(newElement->surname,name);
	newElement -> count = 1;
	return newElement;
}


// returns the element with name name or NULL if the element is not present
Element* search (char* name){
    int keys = hash_function(name);
	int count = 0;

	while(count != ARRAY_SIZE){
		if (hashTable[keys] && (strcmp(hashTable[keys]->surname, name))==0){return hashTable[keys];}
		keys = (keys + 1) % ARRAY_SIZE;
		count ++;
	}
    return NULL;
}

// assuming that no element of key name is in the list (use search first!), add element at the correct place in the list
// NB: it would be more efficient for search to return the index where it should be stored directly, but aiming for simplicity here!
void insert(char* name){
	int keys = hash_function(name);
	int count = 0;

	while (hashTable[keys]!=NULL){
		if (keys < ARRAY_SIZE - 1){
			keys++;
			collisions++;
		}
		else if(keys > ARRAY_SIZE){
			keys = 0;
			count++;
		}
		else if(keys == hash_function(name) && count>0){
			break;
		}
	}
	
	if(!hashTable[keys]){
    hashTable[keys] = createNewElement(name);
	hashTable[keys]->key = keys;


	num_terms++;
}
}
   


// prints the number of occurences, or 0 if not in the file
void printNumberOfOccurences(char* name){
    if(search(name)== NULL){
		printf("%s - 0 \n", name);
	}
	else{
	int numbs = search(name)->count;
	printf("%s - %d \n",name , numbs);
	}

}

//searches the name in the array, if it is there increment its count, if not, add it
void addOrIncrement(char* name){
    if(search(name)== NULL){insert(name);}
	else{
		for(int i = 0; i < ARRAY_SIZE; i++){
			if(hashTable[i] && strcmp(hashTable[i]->surname, name) == 0){hashTable[i]->count++;}
		}
	}


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
		if( !isalnum(buf[i]) && buf[i]!= ' ') { break; } // only load letters and numbers
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
    float load= (float)num_terms / (float)ARRAY_SIZE;

    printf(" Capacity: %i\n Num Terms: %i\n Collisions: %i\n Load: %f\n", ARRAY_SIZE, num_terms, collisions,load);
	// always remember to close your file stream
	fclose(f);

	return 1;
}


int main ( int argc, char *argv[] ) {
	char input[100];
	//if (argc<2){return 1;} // not enough arguments?
    load_file(argv[1]);
	printf("%s", NAME_PROMPT);
	scanf("%s", input);
	while(strcmp(input,"quit")!=0){
		printNumberOfOccurences(input);
		printf("%s", NEW_LINE_PROMPT);
		scanf("%s", input);
	}

    
    return 0;
}