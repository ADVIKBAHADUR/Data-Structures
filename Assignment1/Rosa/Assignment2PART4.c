#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>

#define MAX_STRING_SIZE 50 // max length of a string
#define ARRAY_SIZE 99991   // best be prime

typedef struct Element Element;
struct Element
{
    // char data[MAX_STRING_SIZE];
    //  int counter;
    char PersonID[MAX_STRING_SIZE];
    char DepositionID[MAX_STRING_SIZE];
    char Surname[MAX_STRING_SIZE];
    char Forename[MAX_STRING_SIZE];
    char Age[MAX_STRING_SIZE];
    char PersonType[MAX_STRING_SIZE];
    char Gender[MAX_STRING_SIZE];
    char Nationality[MAX_STRING_SIZE];
    char Religion[MAX_STRING_SIZE];
    char Occupation[MAX_STRING_SIZE];
};

typedef struct Node Node;
struct Node
{
    Element *data;
    Node *next;
};

Node *hashTable[ARRAY_SIZE]; // array of pointers to element structs

int collisions = 0;
int termCount = 0;

Element *
createNewElement(char *pID, char *dID, char *Sur, char *Fore, char *age, char *pType, char *gend, char *nat, char *rel,
                 char *occ)
{
    Element *newElement = malloc(sizeof(Element));
    if (newElement != NULL) // if memory was successfully allocated
    {
        strcpy(newElement->PersonID, pID);
        strcpy(newElement->DepositionID, dID);
        strcpy(newElement->Surname, Sur);
        strcpy(newElement->Forename, Fore);
        strcpy(newElement->Age, age);
        strcpy(newElement->PersonType, pType);
        strcpy(newElement->Gender, gend);
        strcpy(newElement->Nationality, nat);
        strcpy(newElement->Religion, rel);
        strcpy(newElement->Occupation, occ);
        return newElement;
    }
    else // die
    {
        return NULL;
    }
}

void add_node(Node **head, Element *toInsert)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->data = toInsert;
    newNode->next = *head;
    *head = newNode;
}

void hash_table_setup()
{ // fills hashtable with null
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        hashTable[i] = newNode;
        hashTable[i]->next = NULL;
        hashTable[i]->data = NULL;
    }
}

int hash_function(char *name)
{
    int hash = 0;
    while (*name)
    {
        hash = hash * 31;
        hash = (hash + *name) % ARRAY_SIZE;
        name++;
    }
    return ((hash % ARRAY_SIZE));
}

int hash3(char *s)
{
    int hash = 0;
    while (*s)
    {
        hash = 1 + (hash + *s) % (ARRAY_SIZE - 1);
        s++;
    }
    return hash;
}

void hash_table_print() // for testing purposes
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (hashTable[i]->data == NULL) // if theres nothing in this hash value
        {
            printf("%i -  \n", i);
        }
        else
        {
            char tempf[MAX_STRING_SIZE];
            char temps[MAX_STRING_SIZE];
            char tempp[MAX_STRING_SIZE];
            char tempa[MAX_STRING_SIZE];
            strcpy(tempf, hashTable[i]->data->Forename);
            strcpy(temps, hashTable[i]->data->Surname);
            strcpy(tempp, hashTable[i]->data->PersonID);
            strcpy(tempa, hashTable[i]->data->Age);
            printf("%i - %s - %s - %s - %s\n", i, tempf, temps, tempp, tempa);
        }
    }
}

Node *search(char *name)
{ // if present, returns pointer to existing person in table
    int hashVal = hash_function(name);
    int insertAttempt = 0;

    if (hashTable[hashVal]->data != NULL) // if not theres something in the hash value
    {
        char testing1[MAX_STRING_SIZE];
        strcpy(testing1, hashTable[hashVal]->data->Surname);
        if (!strcmp(testing1, name)) // check its the exact same entry not an insert from probing
        {
            return hashTable[hashVal]; // if the names the same return pointer to that list
        }
        for (int i = 1; i < ARRAY_SIZE; i++)
        {
            insertAttempt = (hashVal + i) % ARRAY_SIZE; // linear probing
            if (hashTable[insertAttempt]->data != NULL) // if theres something in this index
            {
                char testing[MAX_STRING_SIZE];
                strcpy(testing, hashTable[insertAttempt]->data->Surname);
                if (!strcmp(testing, name)) // check its the exact same entry not an insert from probing
                {
                    return hashTable[insertAttempt]; // if the names the same
                }
            }
            else
                return NULL; // if theres nothing in the initial hash location then it wont be in the hashtable at all
        }
    }
    else
    {
        return NULL;
    }
    return NULL;
}

void insert(char *pID, char *dID, char *Sur, char *Fore, char *age, char *pType, char *gend, char *nat, char *rel,
            char *occ)
{
    Element *newEntry = createNewElement(pID, dID, Sur, Fore, age, pType, gend, nat, rel, occ); // create an element for it
    int hashVal = hash_function(Sur);

    if (search(Sur) == NULL) // if the name isnt already in the array
    {

        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            int insertAttempt = (hashVal + i) % ARRAY_SIZE;

            if (hashTable[insertAttempt]->data == NULL)
            { // if its hash index is empty plop it in
                hashTable[insertAttempt]->data = newEntry;
                termCount++;
                return;
            }
            collisions++; // every time something is not returned,up counter since we had to find a new spot
        }
    }
    else if (search(Sur) != NULL)
    { // someone with same surname or surname hash exists

        if (search(Sur)->data != NULL)
        {
            if (!strcmp(search(Sur)->data->Surname, Sur)) // if surname is this same just tack it onto linked list
            {
                // first ->next is the head
                add_node(&hashTable[hashVal]->next, newEntry);
            } // linear probing for same hash value but different surname
            else
            {
                for (int i = 0; i < ARRAY_SIZE; i++)
                {
                    int insertAttempt = (hashVal + i) % ARRAY_SIZE;

                    if (hashTable[insertAttempt]->next == NULL &&
                        strcmp(search(Sur)->data->Surname, Sur))
                    { // if its hash index is empty plop it in
                        hashTable[insertAttempt]->data = newEntry;
                        collisions++;
                        //termCount++;
                        return;
                    }
                }
            }
        }
    }
}

// function from the assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_token(char *buf, FILE *f, int string_max)
{
    // start by skipping any characters we're not interested in

    char tempbuf[MAX_STRING_SIZE];
    memset(tempbuf, 0, string_max);

    tempbuf[0] = fgetc(f);
    if (tempbuf[0] == '"')
    { // its a quotation mark
        while (!feof(f))
        {

            int g = 0;
            for (;;)
            {
                tempbuf[g] = fgetc(f); // read every character if inside quotes

                if (feof(f))
                {
                    break;
                }
                if (tempbuf[g] == '\"')
                {                              // hit second quotation mark
                    tempbuf[g] = '\0';         // remove the quotation mark so it doesnt print
                    tempbuf[g + 1] = fgetc(f); // take in the next comma
                    strcpy(buf, tempbuf);
                    return;
                }
                if (g < (string_max - 1))
                {
                    ++g;
                }
            }
        }
    }
    else
    {
        while (!isalnum(tempbuf[0]) && !feof(f))
        {
            tempbuf[0] = fgetc(f);
        }
        // read string of alphanumeric characters if not in quotes
        int i = 1;
        for (;;)
        {
            tempbuf[i] = fgetc(f); // get next character from file
            if (!isalnum(tempbuf[i]) && tempbuf[i] != ' ')
            {
                break;
            } // only load letters and numbers AND SPACES
            if (feof(f))
            {
                break;
            } // file ended?
            if (i < (string_max - 1))
            {
                ++i;
            } // truncate strings that are too long
        }
        tempbuf[i] = '\0'; // NULL terminate the string
    }
    strcpy(buf, tempbuf);
}

//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file(char *fname)
{
    FILE *f;
    int tokencounter = 0;
    int filetitlechecker = 0;
    char buf[MAX_STRING_SIZE];
    char pidtemp[MAX_STRING_SIZE];
    char depidtemp[MAX_STRING_SIZE];
    char surnametemp[MAX_STRING_SIZE];
    char forenametemp[MAX_STRING_SIZE];
    char agetemp[MAX_STRING_SIZE];
    char ptypetemp[MAX_STRING_SIZE];
    char gendertemp[MAX_STRING_SIZE];
    char nationalitytemp[MAX_STRING_SIZE];
    char religiontemp[MAX_STRING_SIZE];
    char occupationtemp[MAX_STRING_SIZE];

    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f)
    {
        printf("Unable to open %s\n", fname);
        return 0;
    }

    // read until the end of the file
    while (!feof(f))
    {

        next_token(buf, f, MAX_STRING_SIZE);
        filetitlechecker++;
        if (filetitlechecker > 10)
        {
            switch (tokencounter)
            {
            case 0:
                strcpy(pidtemp, buf);
                break;
            case 1:
                strcpy(depidtemp, buf);
                break;
            case 2:
                strcpy(surnametemp, buf);
                break;
            case 3:
                strcpy(forenametemp, buf);
                break;
            case 4:
                strcpy(agetemp, buf);
                break;
            case 5:
                strcpy(ptypetemp, buf);
                break;
            case 6:
                strcpy(gendertemp, buf);
                break;
            case 7:
                strcpy(nationalitytemp, buf);
                break;
            case 8:
                strcpy(religiontemp, buf);
                break;
            case 9:
                strcpy(occupationtemp, buf);
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
    printf("File %s loaded\n", fname);
    fclose(f);

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
            char PersonID[MAX_STRING_SIZE];
            strcpy(PersonID, temp->data->PersonID);

            char DepositonID[MAX_STRING_SIZE];
            strcpy(DepositonID, temp->data->DepositionID);

            char Surname[MAX_STRING_SIZE];
            strcpy(Surname, temp->data->Surname);

            char Forename[MAX_STRING_SIZE];
            strcpy(Forename, temp->data->Forename);

            char Age[MAX_STRING_SIZE];
            strcpy(Age, temp->data->Age);

            char PersonType[MAX_STRING_SIZE];
            strcpy(PersonType, temp->data->PersonType);

            char Gender[MAX_STRING_SIZE];
            strcpy(Gender, temp->data->Gender);

            char Nationality[MAX_STRING_SIZE];
            strcpy(Nationality, temp->data->Nationality);

            char Religion[MAX_STRING_SIZE];
            strcpy(Religion, temp->data->Religion);

            char Occupation[MAX_STRING_SIZE];
            strcpy(Occupation, temp->data->Occupation);

            printf(">>> %s - %s - %s - %s - %s -%s - %s - %s - %s - %s\n ", PersonID, DepositonID, Surname, Forename,
                   Age, PersonType, Gender, Nationality, Religion, Occupation);
        }
        temp = temp->next;
    }
}

int main(int argc, char *argv[])
{
    hash_table_setup();

    load_file(argv[1]);

    printf(" Capacity : %i", ARRAY_SIZE);
    printf("\n Num Terms : %i", termCount);
    printf("\n Collisions : %i", collisions);
    float load = ((float)termCount / (float)ARRAY_SIZE);
    printf("\n Load : %.6f \n", load);

    // hash_table_print();

    printf("\nEnter term to get frequency or type \"quit\" to escape\n>>>");
    char searchname[MAX_STRING_SIZE];

    scanf("%s", searchname);

    while (strcmp(searchname, "quit"))
    {
        find_name_print(searchname);

        scanf("%s", searchname);
    }
    printf("\n");

    return 0;
}