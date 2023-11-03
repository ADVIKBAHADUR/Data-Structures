#include "t1.h"
#include <stdio.h>

int main()
{
    //TODO test your functions here
    int array[6];
    int *ptrarr = array;

    fill_without_duplicates(ptrarr, 6);
    for (int i = 0;i < 6 ; i++){

        printf("%d", array[i]);

    }
    
}