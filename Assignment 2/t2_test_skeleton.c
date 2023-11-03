#include "t1.h"
#include "t2.h"
#include <stdio.h>



int main()
{
    //TODO test your functions here
    int size = 6;
    int arr[6];

    for(int i = 0; i < size; i++){
        arr[i] = (size - i - 1);
    }

    printf("Intial: ");
    for (int i = 0;i < size ; i++){

        printf("%d", arr[i]);

    }
    printf("\n");

    printf("After: ");

    quickSort(arr, size);

    for (int i = 0;i < size ; i++){

        printf("%d", arr[i]);

    }
}