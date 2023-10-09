#include <stdio.h>

int main(){
    int myarr[10] = {4,3,6,8,1,2,5,7,9,0};
    int refined[10];
    int index;
    for(int j = 0; j <10; j++){
        int smallest = myarr[j];
        index = j;
        int indexval = myarr[j];
        for (int i = j; i<10;i++){
            if(myarr[i] < smallest){
                smallest = myarr[i];
        }
        myarr[j] = smallest;
        myarr[index] = indexval;
    } 

    }
    for(int loop = 0; loop < 10; loop++)
      printf("%d ", myarr[loop]);

    }