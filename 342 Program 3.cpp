#include <iostream>
#include <cstdlib> // Random Function
#include <ctime> // Time
#include <chrono> //Time for measuring difference.
using namespace std;

const int NUMBER_TO_FIND = 50;
const int MINIMUM_NUMBER_GENERATED = 0;
const int MAXIMUM_NUMBER_GENERATED = 100;
const int NUMBERS_GENERATED = 10000;

void bubbleSort(int arr[], int n);
void swap(int *xp, int *yp);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void quickSort(int arr[], int low, int high);
int partition (int arr[], int low, int high);

int main()
{
	//local variables
	int arrayToBubble[NUMBERS_GENERATED];
	int arrayToMerge[NUMBERS_GENERATED];
	int arrayToQuick[NUMBERS_GENERATED];

	//Seed random number generator.
	srand(time(NULL));

	//Generate random numbers for the arrays given.
	for(int i = 0; i < NUMBERS_GENERATED; i++)
	{
		arrayToBubble[i] = rand() % MAXIMUM_NUMBER_GENERATED + MINIMUM_NUMBER_GENERATED;
		arrayToMerge[i] = rand() % MAXIMUM_NUMBER_GENERATED + MINIMUM_NUMBER_GENERATED;
		arrayToQuick[i] = rand() % MAXIMUM_NUMBER_GENERATED + MINIMUM_NUMBER_GENERATED;
	}

	//test bubblesort
	auto t1 = std::chrono::high_resolution_clock::now();
	bubbleSort(arrayToBubble, NUMBERS_GENERATED);
	auto t2 = std::chrono::high_resolution_clock::now();
	auto iterationDuration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
	cout << "Time take for bubblesort was:\t" << iterationDuration << " nanoseconds." << endl;

	//test mergesort
	t1 = std::chrono::high_resolution_clock::now();
	mergeSort(arrayToMerge, 0, NUMBERS_GENERATED-1);
	t2 = std::chrono::high_resolution_clock::now();
	iterationDuration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
	cout << "Time take for mergesort was:\t" << iterationDuration << " nanoseconds." << endl;

	//test quicksort
	t1 = std::chrono::high_resolution_clock::now();
	quickSort(arrayToQuick, 0, NUMBERS_GENERATED-1);
	t2 = std::chrono::high_resolution_clock::now();
	iterationDuration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
	cout << "Time take for quicksort was:\t" << iterationDuration << " nanoseconds." << endl;
}

//copied from https://www.geeksforgeeks.org/bubble-sort/. Accessed 10 Oct. 2019
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)

    // Last i elements are already in place
    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}

//copied from https://www.geeksforgeeks.org/bubble-sort/. Accessed 10 Oct. 2019
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//copied from https://www.geeksforgeeks.org/merge-sort/. Accessed 10 Oct. 2019
void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

//copied from https://www.geeksforgeeks.org/merge-sort/. Accessed 10 Oct. 2019
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;

	//I had to make changes as these 2 lines make it not compile, stating that the array needs a constant value.
	int n1 = m - l + 1;
	int n2 = r - m;

    /* create temp arrays */
	int L[5001], R[5000];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

//copied from https://www.geeksforgeeks.org/quick-sort/. Accessed 10 Oct. 2019
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//copied from https://www.geeksforgeeks.org/quick-sort/. Accessed 10 Oct. 2019
int partition (int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int i = (low - 1); // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
