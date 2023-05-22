// DISCLAIMER: all code here uses only C arrays since STL's can't be used

#include <iostream>
// swap function used in many sorts
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// prints elements in array, usefull to print stuff at main
void printvec(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    std::cout << std::endl;
}

//creates a random vector with numbers 1-20
void randVector(int vec[], int n){
    srand (time(NULL));
    for(int i = 0; i<n; i++){
        vec[i] = (rand() % 21);
    }
} 

// BUBBLE SORT
// Complexity --> Worst case = O(nˆ2)
//                Best case = O(1)
//                General = O(nˆ2)
// stable
void bubbleSort(int vec[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (vec[j] > vec[j + 1])
            {
                swap(&vec[j], &vec[j + 1]);
            }
        }
    }
}

// SELECTION SORT
// Complexity --> Worst case = O(nˆ2)
//                Best case = O(nˆ2)
//                General = O(nˆ2)
// not stable
void selectionSort(int vec[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < size; j++)
        {
            if (vec[j] < vec[min])
            {
                min = j;
            }
        }
        if (i != min)
        {
            swap(&vec[i], &vec[min]);
        }
    }
}

// INSERTION SORT
// Complexity --> Worst case = O(nˆ2)
//                Best case = O(n)
//                General = O(nˆ2)
// stable
void insertionSort(int vec[], int size)
{
    int i, j, aux;
    for (i = 1; i < size; i++)
    {
        aux = vec[i];
        j = i - 1;
        while (j >= 0 && vec[j] > aux)
        {
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = aux;
    }
}

// QUICK SORT
// Complexity --> Worst case = O(nˆ2)
//                Best case = O(n log n)
//                General = O(n log n)
// not stable
void quickSort(int vec[], int begin, int end)
{
    int i, j, pivot;
    i = begin;
    j = end - 1;
    pivot = vec[(begin + end) / 2];
    while (i <= j)
    {
        while (vec[i] < pivot && i < end)
        {
            i++;
        }
        while (vec[j] > pivot && j > begin)
        {
            j--;
        }
        if (i <= j)
        {
            swap(&vec[i], &vec[j]);
            i++;
            j--;
        }
    }
    if (j > begin)
        quickSort(vec, begin, j + 1);
    if (i < end)
        quickSort(vec, i, end);
}

// function used in merge sort to merge subvectors
void merge(int vec[], int ini, int mid, int end, int vecAux[]) {
    int left = ini;
    int right = mid;
    for (int i = ini; i < end; ++i) {
        if ((left < mid) && ((right >= end) || (vec[left] < vec[right]))) {
            vecAux[i] = vec[left];
            ++left;
        }
        else {
            vecAux[i] = vec[right];
            ++right;
        }
    }
    for (int i = ini; i < end; ++i) {
        vec[i] = vecAux[i];
    }
}

void mergeSort(int vec[], int begin, int end, int vecAux[]) {
    if ((end - begin) < 2) return;
    
    int mid = ((begin + end)/2);
    mergeSort(vec, begin, mid, vecAux);
    mergeSort(vec, mid, end, vecAux);
    merge(vec, begin, mid, end, vecAux);
}

// MERGE SORT
// Complexity --> Worst case = θ(n log n)
//                Best case = θ(n log n)
//                General = θ(n log n)
// stable
void mergeSort(int vec[], int size) {
    int vetorAux[size];
    mergeSort(vec, 0, size, vetorAux);
}

//function to heapify vectors
void heapify(int vec[], int n, int i)
{
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && vec[left] > vec[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && vec[right] > vec[largest])
        largest = right;

    // If largest is not root
    if (largest != i)
    {
        swap(&vec[i], &vec[largest]);

        // Recursively heapify the affected sub-tree
        heapify(vec, n, largest);
    }
}

// HEAP SORT
// Complexity --> Worst case = θ(n log n)
//                Best case = θ(n log n)
//                General = θ(n log n)
// not stable
void heapSort(int vec[], int size)
{
    // Build heap (rearrange array)
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(vec, size, i);

    // Extract elements from the heap one by one
    for (int i = size - 1; i > 0; i--)
    {
        // Move current root to the end
        swap(&vec[0], &vec[i]);

        // call max heapify on the reduced heap
        heapify(vec, i, 0);
    }
}

// SHELL SORT (using Sedgewick's Gap Sequence)
// Complexity --> General: close to O(n log n) but indefined
// not stable
void shellSort(int vec[], int size)
{
    //using Sedgewick's Gap Sequence to iterate h
    int gaps[] = {1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305, 260609};

	// Start with a big h, then reduce the h
	for (int i = sizeof(gaps) / sizeof(gaps[0]) - 1; i >= 0; i--)
	{
        int h = gaps[i];

		for (int i = h; i < size; i++)
		{
			// add a[i] to the elements that have been h sorted
			// save a[i] in temp and make a hole at position i
			int temp = vec[i];

			// shift earlier h-sorted elements up until the correct
			// location for a[i] is found
			int j;			
			for (j = i; j >= h && vec[j - h] > temp; j -= h)
				vec[j] = vec[j - h];
			
			// put temp (the original a[i]) in its correct location
			vec[j] = temp;
		}
	}
	return;
}

// BUCKET SORT
// Complexity --> Worst case = O(nˆ2)
//                Best case = O(n + K)
//                General = O(n + K)
// stable
void bucketSort(int vec[], int size){
    //did not implement
}

// RADIX SORT
// Complexity --> Worst case = O(nK)
// stable
void radixSort(int vec[], int size){
    int i;
    int *b;
    int big = vec[0];
    int exp = 1;

    b = (int *)calloc(size, sizeof(int));

    for (i = 0; i < size; i++) {
        if (vec[i] > big)
    	    big = vec[i];
    }

    while (big/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < size; i++)
    	    bucket[(vec[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = size - 1; i >= 0; i--)
    	    b[--bucket[(vec[i] / exp) % 10]] = vec[i];
    	for (i = 0; i < size; i++)
    	    vec[i] = b[i];
    	exp *= 10;
    }

    free(b);
}