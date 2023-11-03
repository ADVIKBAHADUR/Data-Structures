#include <stdio.h>
#include <stdlib.h>
#include "t1.h"


//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    //TODO
    for(int i = 0; i < size;i++){
        array[i] = i;
    }
    
}
//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
    //TODO
    for(int i = 0; i < size; i++){
        array[i] = (size - i - 1);
    }
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size)
{
    //TODO
    for(int i = 0; i < size ; i++){
        array[i] = 3;
    }
    
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size)
{
    //TODO
    int i = 0;
    while(i < size){
        int num = rand() % size;
        array[i] = num;
        i++;
    }
}


//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
    //TODO
    int i = 0;
    while(i < size){
        int same = 0;
        int num = rand() % size;
        for(int j = 0; j < i; j++){
            same  = 0;
            if(num == array[j]){
                same++;
                break;
            }
        }
        if(same == 0){
            array[i] = num;
            i++;
        }

    }
    
}

void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

