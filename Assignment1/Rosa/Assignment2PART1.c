#include <stdio.h>
#include <stdlib.h>
#include <string.h> //for strcpy and strcmp
#include <ctype.h>

#define MAX_STRING_SIZE 20 // max length of a string
#define ARRAY_SIZE 59      // best be prime

typedef struct Element Element;
struct Element
{
    char data[MAX_STRING_SIZE];
    int counter;
};

Element *hashTable[ARRAY_SIZE]; // array of pointers to element structs

int collisions = 0;
int termCount = 0;

Element *createNewElement(char *name)
{
    Element *newElement = malloc(sizeof(Element));
    if (newElement != NULL) // if memory was successfully allocated
    {
        strcpy(newElement->data, name); // why did I need strcpy for this??
        newElement->counter = 1;
        return newElement;
    }
    else // die
    {
        return NULL;
    }
}

void hash_table_setup()
{ // fills hashtable with null
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        hashTable[i] = NULL;
    }
}

int hash_function(char *name)
{
    int hash = 0;
    while (*name)
    {
        hash = hash + *name;
        name++;
    }
    return ((hash % ARRAY_SIZE));
}

void hash_table_print()
{
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (hashTable[i] == NULL) // if theres nothing in this hash value
        {
            printf("%i -  \n", i);
        }
        else
        {
            printf("%i - %s - %i\n", i, hashTable[i]->data, hashTable[i]->counter);
        }
    }
}

Element *search(char *name)
{ // if present, returns pointer to existing person in table
    int hashVal = hash_function(name);
    int insertAttempt = 0;
    if (hashTable[hashVal] != NULL) // if theres something in the hash value
    {
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            insertAttempt = (hashVal + i) % ARRAY_SIZE;
            if (hashTable[insertAttempt] != NULL)
            {
                if (!strcmp(hashTable[insertAttempt]->data, name)) // check its the exact same entry not an insert from probing
                {
                    return hashTable[insertAttempt];
                }
            }
            else
                return NULL;
        }
    }

    return NULL;
}

void insert(char *name)
{
    if (search(name) == NULL) // if the name isnt already in the array
    {
        Element *newEntry = createNewElement(name); // create an element for it
        int hashVal = hash_function(name);
        termCount++;
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            int insertAttempt = (hashVal + i) % ARRAY_SIZE;
            if (hashTable[insertAttempt] == NULL)
            { // if its hash index is empty plop it in
                hashTable[insertAttempt] = newEntry;
                return;
            }
            collisions++; // every time something is not returned,up counter since we had to find a new spot
        }
    }
    else if (search(name) != NULL)
    { // yoke already exists just increase its counter
        search(name)->counter++;
    }
}

// function from the assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
void next_token(char *buf, FILE *f, int string_max)
{
    // start by skipping any characters we're not interested in
    buf[0] = fgetc(f);
    while (!isalnum(buf[0]) && !feof(f))
    {
        buf[0] = fgetc(f);
    }
    // read string of alphanumeric characters
    int i = 1;
    for (;;)
    {
        buf[i] = fgetc(f); // get next character from file
        if (!isalnum(buf[i]) && buf[i] != ' ')
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
    buf[i] = '\0'; // NULL terminate the string
}

//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file(char *fname)
{
    FILE *f;
    char buf[MAX_STRING_SIZE];

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
        insert(buf);

        // addOrIncrement( buf);                           //here you call your function from above!
    }

    // always remember to close your file stream
    printf("File %s loaded\n", fname);
    fclose(f);

    return 1;
}

void find_name_print(char *name)
{
    // char findingName[MAX_STRING_SIZE] = name;
    if (search(name) != NULL)
    {
        int i = search(name)->counter;
        // printf(">>> %s - %i\n>>> ", name, i);
        printf(" %s - %i\n ", name, i);
    }
    else
    {
       // printf(">>> %s - 0\n>>> ", name);
        printf(" %s - 0\n ", name);
    }
}

int main(int argc, char *argv[])
{
    hash_table_setup();
    // insert("a");
    load_file(argv[1]);
    printf(" Capacity : %i", ARRAY_SIZE);
    printf("\n Num Terms : %i", termCount);
    printf("\n Collisions : %i", collisions);
    float load = ((float)termCount / (float)ARRAY_SIZE);
    printf("\n Load : %.6f ", load);
    // hash_table_print();
    printf("\nEnter term to get frequency or type \"quit\" to escape\n>>>");
    char searchname[MAX_STRING_SIZE];

    scanf("%s", searchname);
    while (strcmp(searchname, "quit"))
    {
        find_name_print(searchname);

        scanf("%s", searchname);
        // printf(">>> ");
    }
    printf("\n");

    return 0;
}