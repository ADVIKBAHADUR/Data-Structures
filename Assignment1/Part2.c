#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

#define NAME_SIZE 20
#define MAX_ARRAY_SIZE 59

typedef struct Name {

    char Name[NAME_SIZE];
    int value;
    int occurences;

} Name;
int load_file(char *files);
Name *createNewElement(char *AddName);
int hash1(char* s);
struct Name *search(char *name);
void insert(char *name);
void next_row(char *buffer, FILE *f, int max);
int load_file(char *files);

Name *HashTable[MAX_ARRAY_SIZE];
int collisions = 0;
int terms = 0;

Name *createNewElement(char *AddName){
    Name *newname = malloc(sizeof(Name)); //Allocate the memory
    if (newname != NULL) 
    {
        strcpy(newname->Name, AddName);
        newname->occurences = 1;
        return newname;
    }
    else
    {
        return NULL;
    }
}

int hash1(char* s){
    int hash = 0;
    int somenum = 0;
    while(*s){
        somenum++;
        hash = (((hash + *s) - 'A')*((hash + *s) - 'A')+ (somenum)*(somenum)) % MAX_ARRAY_SIZE;
        s++;
    }
    return hash;
}

struct Name *search(char *name){
    if (name[strlen(name)-1] == '\n'){name[strlen(name)-1] = '\0';}
    int checkval = hash1(name);
    //printf("After %d %s", checkval, name);
    int count = 0;
    while(count < MAX_ARRAY_SIZE){
        if(HashTable[checkval] != NULL){
            //printf("%s \n", Table[checkval]->Names);
            //char tester[MAX_bufferFER] = Table[checkval]->Names;
        
            //printf("Checker: %d", checker);
            if((strcmp(HashTable[checkval]->Name, name))==0){
                return(HashTable[checkval]);
            }
        }
        checkval++;
        count++;

        checkval %= MAX_ARRAY_SIZE;
    }
    return NULL;
}

void insert(char *name){
    if (search(name) == NULL)
    {
        Name *newName = createNewElement(name); 
        int hash = hash1(name);

        terms++;

        for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        {

            int attempt = (hash + i) % MAX_ARRAY_SIZE;
            if (HashTable[attempt] == NULL)
            { // if empty

                HashTable[attempt] = newName;
                return;

            }
            collisions++; 
        }
    } else if(search(name) != NULL){

        search(name)->occurences++;

    }
}

void next_row(char *buffer, FILE *f, int max){
    buffer[0] = fgetc(f);

    while (!isalnum(buffer[0]) && !feof(f))
    {

        buffer[0] = fgetc(f);

    }
    // read alphanum char
    int i = 1;
    for (;;) {
        buffer[i] = fgetc(f); // get next char
        if (!isalnum(buffer[i]) && buffer[i] != ' ')

        {

            break;

        } // only char/num/space
        if (feof(f))
        {

            break;

        } // Check END
        if (i < (max - 1))
        {

            ++i;

        }
    }
    buffer[i] = '\0'; // NULL terminate the string
}

int load(char *files)
{
    FILE *file;

    char buffer[NAME_SIZE];

    file = fopen(files, "r");


    if (!file)
    {
        printf("cant open%s\n", files);
        return 0;
    }


    while (!feof(file))
    {
        next_row(buffer, file, NAME_SIZE);
        insert(buffer);

  
    }
    printf("File %s loaded\n", files);
    fclose(file);

    return(1);
}

int main(int argc, char *argv[]){




    load(argv[1]);
    printf(" Capacity: %d", MAX_ARRAY_SIZE);
    printf("\n Num Terms: %d", terms);
    printf("\n Collisions: %d", collisions);

    float load = ((float)terms / (float)MAX_ARRAY_SIZE);

    printf("\n Load: %.6f", load);

    printf("\nEnter term to get frequency or type \"quit\" to escape");

    char checker[NAME_SIZE];

    scanf("%s", checker);

    while (strcmp(checker, "quit"))
    {
        printf("\n>>>");
        Name *variable = search(checker);
        if(variable != NULL){

            int occurances = variable->occurences;
            printf(" %s - %d ", checker, occurances);

        } else{
            printf(" %s - 0 ", checker);
        }

        scanf("%s", checker);
        // printf(">>> ");
    }
    printf("\n>>> ");

    return(0);
}