#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NAME_SIZE 20
#define MAX_ARRAY_SIZE 99991

typedef struct Name
{

    char personID[NAME_SIZE];
    char depositID[NAME_SIZE];
    char Surname[NAME_SIZE];
    char Forename[NAME_SIZE];
    char age[NAME_SIZE];
    char person[NAME_SIZE];
    char gender[NAME_SIZE];
    char nationality[NAME_SIZE];
    char religion[NAME_SIZE];
    char occupation[NAME_SIZE];

} Name;

typedef struct Node Node;
struct Node
{
    Name *mydata;
    Node *next;
};

// Declarations of functions
int load_file(char *files);
Name *createNewElement(char *personID, char *depositID, char *Surname, char *Forename, char *age, char *person, char *gender, char *nationality, char *religion,
                       char *occupation);
int hash1(char *s);
Node *search(char *name);
void insert(char *personID, char *depositID, char *Surname, char *Forename, char *age, char *person, char *gender, char *nationality, char *religion,
            char *occupation);
void next_row(FILE *file, char *buffer, int max);
int load_file(char *files);

Node *HashTable[MAX_ARRAY_SIZE];
int collisions = 0;
int terms = 0;

Name *createNewElement(char *personID, char *depositID, char *Surname, char *Forename, char *age, char *person, char *gender, char *nationality, char *religion,
                       char *occupation)
{
    Name *newname = malloc(sizeof(Name)); // Allocate the memory
    if (newname != NULL)
    {
        strcpy(newname->personID, personID);
        strcpy(newname->depositID, depositID);
        strcpy(newname->Surname, depositID);
        strcpy(newname->Forename, Forename);
        strcpy(newname->age, age);
        strcpy(newname->person, person);
        strcpy(newname->gender, gender);
        strcpy(newname->nationality, nationality);
        strcpy(newname->religion, religion);
        strcpy(newname->occupation, occupation);
        return newname;
    }
    else
    {
        return NULL;
    }
}

int hash1(char *s)
{
    int hash = 0;
    while (*s)
    {
        hash = (hash + *s - 'A') % MAX_ARRAY_SIZE;
        s++;
    }
    return hash;
}
void addToList(Node **head, Name *item)
{

    Node *myNode = (Node *)malloc(sizeof(Node)); // To allocate memory
    myNode->mydata = item;
    myNode->next = *head;
    *head = myNode;
}

Node *search(char *name)
{
    int Val = hash1(name);
    int attempt = 0;

    if (HashTable[Val]->mydata != NULL)
    {
        char checker[NAME_SIZE];
        strcpy(checker, HashTable[Val]->mydata->Surname);
        if (!strcmp(checker, name))
        {

            return HashTable[Val]; // if the names the same return pointer to that list
        }
        for (int i = 1; i < MAX_ARRAY_SIZE; i++)
        {
            attempt = (Val + i) % MAX_ARRAY_SIZE;   // linear probing
            if (HashTable[attempt]->mydata != NULL) // if theres something in this index
            {
                char checker2[NAME_SIZE];
                strcpy(checker2, HashTable[attempt]->mydata->Surname);
                if (!strcmp(checker2, name)) // check its the exact same entry not an insert from probing
                {
                    return HashTable[attempt]; // if the names the same
                }
            }
            else
                return NULL; // if theres nothing in the initial hash location then it wont be in the HashTable at all
        }
    }
    else
    {
        return NULL;
    }
    return NULL;
}

void insert(char *personID, char *depositID, char *Surname, char *Forename, char *age, char *person, char *gender, char *nationality, char *religion,
            char *occupation)
{
    Name *newEntry = createNewElement(personID, depositID, Surname, Forename, age, person, gender, nationality, religion,
                                      occupation); // create an Name for it
    int val = hash1(Surname);

    if (search(Surname) == NULL) // if the name isnt already in the array
    {

        for (int i = 0; i < MAX_ARRAY_SIZE; i++)
        {
            int attempt = (val + i) % MAX_ARRAY_SIZE;

            if (HashTable[attempt]->mydata == NULL)
            { // if its hash index is empty plop it in
                HashTable[attempt]->mydata = newEntry;
                terms++;
                return;
            }
            collisions++; // every time something is not returned,up counter since we had to find a new spot
        }
    }
    else if (search(Surname) != NULL)
    { // someone with same surname or surname hash exists

        if (search(Surname)->mydata != NULL)
        {
            if (!strcmp(search(Surname)->mydata->Surname, Surname)) // if surname is this same just tack it onto linked list
            {
                // first ->next is the head
                addToList(&HashTable[val]->next, newEntry);
            } // linear probing for same hash value but different surname
            else
            {
                for (int i = 0; i < MAX_ARRAY_SIZE; i++)
                {
                    int attempt = (val + i) % MAX_ARRAY_SIZE;

                    if (HashTable[attempt]->next == NULL &&
                        strcmp(search(Surname)->mydata->Surname, Surname))
                    { // if its hash index is empty plop it in
                        HashTable[attempt]->mydata = newEntry;
                        collisions++;
                        // termCount++;
                        return;
                    }
                }
            }
        }
    }
}

void next_row(FILE *file, char *buffer, int max)
{
    // start by skipping any characters we're not interested in

    char temp[NAME_SIZE];
    memset(temp, 0, max);

    temp[0] = fgetc(file);
    if (temp[0] == '"')
    { // its a quotation mark
        while (!feof(file))
        {
            int g = 0;
            for (;;)
            {
                temp[g] = fgetc(file); 

                if (feof(file))
                {
                    break;
                }
                if (temp[g] == '\"')
                {                              
                    temp[g] = '\0';         
                    temp[g + 1] = fgetc(file); 
                    strcpy(buffer, temp);
                    return;
                }
                if (g < (max - 1))
                {
                    ++g;
                }
            }
        }
    }
    else
    {
        while (!isalnum(temp[0]) && !feof(file))
        {
            temp[0] = fgetc(file);
        }
        
        int i = 1;
        for (;;)
        {
            temp[i] = fgetc(file); 
            if (!isalnum(temp[i]) && temp[i] != ' ')
            {
                break;
            } 
            if (feof(file))
            {
                break;
            } 
            if (i < (max - 1))
            {
                ++i;
            }
        }
        temp[i] = '\0'; 
    }
    strcpy(buffer, temp);
}

int load(char *files)
{
    FILE *file;
    int tokencounter = 0;
    int filetitlechecker = 0;
    char buffer[NAME_SIZE];
    char pidtemp[NAME_SIZE];
    char depidtemp[NAME_SIZE];
    char surnametemp[NAME_SIZE];
    char forenametemp[NAME_SIZE];
    char agetemp[NAME_SIZE];
    char ptypetemp[NAME_SIZE];
    char gendertemp[NAME_SIZE];
    char nationalitytemp[NAME_SIZE];
    char religiontemp[NAME_SIZE];
    char occupationtemp[NAME_SIZE];
    file = fopen(files, "r");
    if (!file)
    {
        printf("Unable to open %s\n", files);
        return 0;
    }

    while (!feof(file))
    {

        next_row(file, buffer, NAME_SIZE);
        printf("row: %s", buffer);
        filetitlechecker++;
        if (filetitlechecker > 10)
        {
            switch (tokencounter)
            {
            case 0:
                strcpy(pidtemp, buffer);
                break;
            case 1:
                strcpy(depidtemp, buffer);
                break;
            case 2:
                strcpy(surnametemp, buffer);
                break;
            case 3:
                strcpy(forenametemp, buffer);
                break;
            case 4:
                strcpy(agetemp, buffer);
                break;
            case 5:
                strcpy(ptypetemp, buffer);
                break;
            case 6:
                strcpy(gendertemp, buffer);
                break;
            case 7:
                strcpy(nationalitytemp, buffer);
                break;
            case 8:
                strcpy(religiontemp, buffer);
                break;
            case 9:
                strcpy(occupationtemp, buffer);
                break;
            }
            if (tokencounter <= 8)
            {
                tokencounter++;
            }
            else
            {
                insert(pidtemp, depidtemp, surnametemp, forenametemp, agetemp, ptypetemp, gendertemp,
                       nationalitytemp,
                       religiontemp, occupationtemp);
                tokencounter = 0;
            }
        }
    }

    // always remember to close your file stream
    printf("File %s loaded\n", file);
    fclose(file);

    return 1;
}

void find_name_print(char *name)
{
    Node *temp;
    temp = search(name);
    if (temp == NULL)
    {
        printf("%s not in table\n", name);
    }
    while (temp != NULL)
    {
        if (temp != NULL)
        {
            char PersonID[NAME_SIZE];
            strcpy(PersonID, temp->mydata->personID);

            char DepositonID[NAME_SIZE];
            strcpy(DepositonID, temp->mydata->depositID);

            char Surname[NAME_SIZE];
            strcpy(Surname, temp->mydata->Surname);

            char Forename[NAME_SIZE];
            strcpy(Forename, temp->mydata->Forename);

            char Age[NAME_SIZE];
            strcpy(Age, temp->mydata->age);

            char PersonType[NAME_SIZE];
            strcpy(PersonType, temp->mydata->person);

            char Gender[NAME_SIZE];
            strcpy(Gender, temp->mydata->gender);

            char Nationality[NAME_SIZE];
            strcpy(Nationality, temp->mydata->nationality);

            char Religion[NAME_SIZE];
            strcpy(Religion, temp->mydata->religion);

            char Occupation[NAME_SIZE];
            strcpy(Occupation, temp->mydata->occupation);

            printf(">>> %s - %s - %s - %s - %s -%s - %s - %s - %s - %s\n ", PersonID, DepositonID, Surname, Forename,
                   Age, PersonType, Gender, Nationality, Religion, Occupation);
        }
        temp = temp->next;
    }
}

int main(int argc, char *argv[])
{

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
        find_name_print(checker);

        scanf("%s", checker);
    }
    printf("\n>>> ");

    return (0);
}