#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256 // Maximum string length this program can handle
#define MAX_NAME_SIZE 265 //max length of a string
#define ARRAY_SIZE 59  //best be prime
#define NAME_PROMPT "Enter term to get frequency or type \"quit\" to escape\n>>> " //you can use this string as your invitation to the user
#define NEW_LINE_PROMPT

typedef struct Name {

    char Names[MAX_NAME_SIZE];
    int value;
    int occurences;

} Name;

void HashmapManagement(Name * myobject, Name * table[]);
void AddNonDuplicate(Name * myobject);

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
    if (name[strlen(name)-1] == '\n'){name[strlen(name)-1] = '\0';}
    strcpy(currName->Names, name);
    int val = hash1(name);
    //printf("before: %s : %d", currName->Names, val);
    currName->value = val;
    currName->occurences = 1;
    //printf("Name: %s, Key %d \n", currName->Names, currName->value);
    HashmapManagement(currName, table);
}

struct Name *search(char *name){
    if (name[strlen(name)-1] == '\n'){name[strlen(name)-1] = '\0';}
    int checkval = hash1(name);
    //printf("After %d %s", checkval, name);
    int count = 0;
    while(count < ARRAY_SIZE){
        if(Table[checkval] != NULL){
            //printf("%s \n", Table[checkval]->Names);
            //char tester[MAX_BUFFER] = Table[checkval]->Names;
        
            //printf("Checker: %d", checker);
            if((strcmp(Table[checkval]->Names, name))==0){
                return(Table[checkval]);
            }
        }
        checkval++;
        count++;

        checkval %= ARRAY_SIZE;
    }
    return NULL;
}

// Name *search(char *name)
// { 
//     int hash = hash1(name);
//     int Attempt = 0;
//     if (Table[hash] != NULL) 
//     {
//         for (int i = 0; i < ARRAY_SIZE; i++)
//         {
//             Attempt = (hash + i) % ARRAY_SIZE;
//             if (Table[Attempt] != NULL)
//             {
//                 if (!strcmp(Table[Attempt]->Names, name)) 
//                 {
//                     return Table[Attempt];
//                 }
//             }
//             else
//                 return NULL;
//         }
//     }

//     return NULL;
// }

// void HashmapManagement(Name * myobject, Name * table[]){
//     char myname[MAX_BUFFER];
//     strcpy(myname, myobject->Names);
//     if (myname[strlen(myname)-1] == '\n'){myname[strlen(myname)-1] = '\0';}
//     if(search(myname) == NULL){AddNonDuplicate(myobject);}
//     else{
//         for(int i = 0; i < ARRAY_SIZE; i++){
// 			if(table[i] && strcmp(table[i]->Names, myname) == 0){table[i]->occurences++;}
// 		}
//     }


// }

// void AddNonDuplicate(Name * myobject){
//     char myname[MAX_BUFFER];
//     strcpy(myname, myobject->Names);
//     if (myname[strlen(myname)-1] == '\n'){myname[strlen(myname)-1] = '\0';}

//     int index = hash1(myname);

//     while(Table[index] != NULL){
//         ++collisions;
//         ++index; 
//         index %= ARRAY_SIZE;
//     }
//     myobject->value = index;
//     Table[index] = myobject;
//     num_terms++;

// }

int main ( int argc, char *argv[] ) {
	FILE *f;		
	char buffer[MAX_BUFFER];
    char query[MAX_BUFFER];

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
        printf("File %s loaded\n", argv[1]);
    }

	// Now read and print records until the end of the file
    int counter = 0;
	while(!feof(f)) {
		int eor = next_field( f, buffer, MAX_BUFFER );
        char name[MAX_NAME_SIZE] = "";
		sprintf(name, "%s%c\n", buffer, ((eor)? '\n':' '));  // double newline if eor is not 0
        //printf("\n Name: %s", name);
        if (name[strlen(name)-1] == '\n'){name[strlen(name)-1] = '\0';}
        addElement(Table, name);
        counter++;
	}
    float load = (float)num_terms/(float)ARRAY_SIZE;
    printf(" Capacity: %d\n", ARRAY_SIZE);
    printf(" Num Terms: %d\n", num_terms);
    printf(" Collisions: %d\n", collisions);
    printf(" Load: %f", load);
    //query[strcspn(query, "\n")] = 0;

    //printf("Query: ", query);
    
    // for(int i = 0; i < ARRAY_SIZE; i++){

    //     if(Table[i] == NULL){
    //         printf("\n %d : EMPTY", i);
    //     }
    //     else{
    //         printf("\n %d : %s : %d", i, Table[i]->Names, Table[i]->occurences);
    //     }

    // }
    int sentinel = 0;
    printf("\n%s", NAME_PROMPT);
    while(sentinel != 1){

        fgets(query, sizeof(query), stdin);
        //printf("Query: %s", query);
        if (query[strlen(query)-1] == '\n'){query[strlen(query)-1] = '\0';}

        if(strcmp(query, "quit") == 0){
            sentinel = 1;
            return EXIT_SUCCESS;
        }
        struct Name* freq = search(query);
        
        if(freq != NULL){
            printf("\n>>> %s - %d",freq->Names, freq->occurences);
        } else {
            printf("\n>>> %s - 0", query);
        }

    }

	// Always remember to close the file
	fclose(f);
	return EXIT_SUCCESS;
}


