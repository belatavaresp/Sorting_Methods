#include "sorts.h"
#include <iostream>

#include <time.h>
#include <stdlib.h>

//creates a random vector with numbers 1-20
void randVector(int vec[], int n){
    srand (time(NULL));
    for(int i = 0; i<n; i++){
        vec[i] = (rand() % 21);
    }
} 

int main(){
    int vec[10];
    randVector(vec, 10);
    printvec(vec, 10);
    radixSort(vec, 10);
    printvec(vec, 10);

    return 0;
}