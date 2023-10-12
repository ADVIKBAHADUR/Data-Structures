#include <stdio.h>
#include <string.h>
#include <math.h>


int hash1(char* s){
    int hash = 0;
    while(*s){
        hash = (hash + *s - 'A') % 59;
        s++;
    }
    return abs(hash);
}

int main(){
    char inputString[10];
    printf("Enter some text: ");
    fgets(inputString, sizeof(inputString), stdin);
    //inputString[strlen(inputString)-1] = '\0';

    // if (fgets(inputString, sizeof(inputString), stdin)){
    // size_t input_length = strlen(inputString);
    if (inputString[strlen(inputString)-1] == '\n'){inputString[strlen(inputString)-1] = '\0';}
    int hash = hash1(inputString);

    printf("You entered: %s, hopefully this text isnt seperated %d", inputString, hash);

    return 0;
}
