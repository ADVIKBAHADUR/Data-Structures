#include <stdio.h> 
#include "t2.h"
#include <time.h>
#include <stdlib.h>

int number_comparisons = 0;
int number_swaps = 0;

int partition(int arr[], int low, int high);
void selectionSort(int arr[], int size);
void insertionSort(int arr[], int size);
void quickSort(int arr[], int size);
void actualQuickSort(int arr[], int low, int high);
int choosePivot(int low, int high);

void selectionSort(int arr[], int size) 
{ 
  //TODO
  for(int i = 0; i < size; i++){
    int min = arr[i];
    int minIndex = i;
    int ival = arr[i];

    for (int j = i+1; j < size; j++){
      number_comparisons++;
      if(arr[j] < min){
        minIndex = j;
        min = arr[j];
      }
    }
    arr[minIndex] = ival;
    number_swaps++;
    arr[i] = min;

  }
} 

void insertionSort(int arr[], int size) 
{ 
  //TODO
  for(int i = 0; i < size; i++){
    int curr = arr[i]; //VALUE OF CURRENT ITEM
    int prev = i - 1; //INDEX OF PREV ITEM
    int sentinel = 0;
    number_comparisons++;
    number_comparisons++;
    if (prev >= 0 && arr[prev] > curr){
      sentinel = 1;
    }
    while (sentinel == 1){
      number_comparisons++;
      number_comparisons++;
      arr[prev + 1] = arr[prev]; //bring the bigger num forward
      number_swaps++;
      prev = prev - 1;//so we can compare the num before for if bigger?
      if (prev >= 0 && arr[prev] > curr){
        sentinel = 1;
      }
      else{
        sentinel = 0;
      }
    }
    arr[prev + 1] = curr; // So now, we have assigned the curr val to its required pos
  }
  
}




int partition(int arr[], int low, int high) 
{ 
 //TODO
  int piv = choosePivot(low, high);
  int temp2 = arr[piv];
  arr[piv] = arr[high];
  arr[high] = temp2;
  number_swaps++;
  piv = high;
  int i = (low - 1);

  for(int j = low; j <= high; j++){
    number_comparisons++;
    if(arr[j] < arr[piv]){
      i++;
      //SWAP
      int temp = arr[i];
      number_swaps++;
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  int newpiv = i + 1;
  int temp = arr[newpiv];
  number_swaps++;
  arr[newpiv] = arr[high];
  arr[high] = temp;
  return(newpiv);
}

void quickSort(int arr[], int size) {

  actualQuickSort(arr, 0, size);

}

void actualQuickSort(int arr[], int low, int high){
  number_comparisons++;
  if(low < high){
    int split = partition(arr, low, high); 

    actualQuickSort(arr, low, split -1);
    actualQuickSort(arr, split+1, high);
  }

}

int choosePivot(int low, int high){
  srand(time(NULL));
  return low + rand() % (high - low + 1);
}


