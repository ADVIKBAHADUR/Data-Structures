#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256 // Maximum string length this program can handle
#define MAX_NAME_SIZE 20 //max length of a string
#define ARRAY_SIZE 59  //best be prime
#define NAME_PROMPT "Enter term to get frequency or type \"quit\" to escape\n>>> " //you can use this string as your invitation to the user
#define NEW_LINE_PROMPT
typedef struct Name {

    char Names[MAX_NAME_SIZE];
    int value;
    int occurences;

} Name;

// The CSV parser
int next_field( FILE *f, char *buf, int max ) {
	int i=0, end=0, quoted=0;
	
	for(;;) {
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { break; }
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		// truncate fields that would overflow the buffer
		if( i<max-1 ) { ++i; } 
	}

	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

Name* Table[ARRAY_SIZE];
int collisions = 0;
int num_terms = 0;

int hash1(char* s){
    int hash = 0;
    while(*s){
        hash = (hash + *s - 'A') % ARRAY_SIZE;
        s++;
    }
    return abs(hash);
}
void addElement(Name* table[], char *name){
    struct Name* currName = (struct Name*)malloc(sizeof(struct Name));
    strcpy(currName->Names, name);
    int val = hash1(name);
    printf("before: %d", val);
    currName->value = val;
    currName->occurences = 1;
    printf("Name: %s, Key %d \n", currName->Names, currName->value);
    HashmapManagement(currName, table);
}

struct Name *search(char *name){
    int checkval = hash1(name);
    printf("After %d %s", checkval, name);
    while(Table[checkval] != NULL){
        if(strcmp(Table[checkval]->Names, name)){
            return(Table[checkval]);
        }
        ++checkval;

        checkval %= ARRAY_SIZE;
    }
    return NULL;
}

void HashmapManagement(Name * myobject, Name * table[]){
    int index = myobject->value;
    //printf("index: %d", index);
    if(table[index] == NULL){ //EMPTY SLOT
        //printf("NULL");
        table[index] = myobject;
        num_terms++;
    }

    else if(table[index] != NULL){
        //printf("NOTNULL");

        //CHECK IF DUPLICATES FIRST:

        if(strcmp(table[index]->Names,myobject->Names)){
            table[index]->occurences++;
            //printf("\nOccurences: %s %d %d", table[index]->Names, table[index]->occurences, table[index]->value);
        }

        else{
            //printf("NODUP");
            while(table[index] != NULL){
                collisions++;
                ++index; 
                index %= ARRAY_SIZE;
            }
            table[index] = myobject;
            num_terms++;
        }

    }


}

int main ( int argc, char *argv[] ) {
	FILE *f;		
	char buffer[MAX_BUFFER];
    char query[MAX_NAME_SIZE] = "";

	// Users must pass the name of the input file through the command line. Make sure
	// that we got an input file. If not, print a message telling the user how to use
	// the program and quit
	if( argc < 2 ) { 
		printf("usage: csv FILE\n"); 
		return EXIT_FAILURE; 
	}

	// Try to open the input file. If there is a problem, report failure and quit
	f = fopen(argv[1], "r");
	if(!f) { 
		printf("unable to open %s\n", argv[1]); 
		return EXIT_FAILURE; 
	}
    else{
        printf("%s loaded! \n", argv[1]);
    }

	while( !next_field(f, buffer, MAX_BUFFER) ); // discard the header

	// Now read and print records until the end of the file
    int counter = 0;
	while(!feof(f)) {
		int eor = next_field( f, buffer, MAX_BUFFER );
        char name[MAX_NAME_SIZE] = "";
		sprintf(name, "%s%c\n", buffer, ((eor)? '\n':' '));  // double newline if eor is not 0
        //printf("\n Name: %s", name);
        addElement(Table, name);
        counter++;
	}
    float load = (float)num_terms/(float)ARRAY_SIZE;
    printf("Capacity : %d \n", ARRAY_SIZE);
    printf("Num Terms: %d \n", num_terms);
    printf("Collisions: %d \n", collisions);
    printf("Load: %f \n", load);
    printf("Enter term to get frequency or type \"quit\" to escape \n");
    scanf("%s", query);
    struct Name* freq = search(query);

    if(freq != NULL){
        printf("%s %d", query, freq->occurences);
    } else {
        printf("Not found");
    }
	// Always remember to close the file
	fclose(f);
	return EXIT_SUCCESS;
}


