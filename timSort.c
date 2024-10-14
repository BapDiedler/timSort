#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include <time.h>

#define RUN 32

void insertionSort(int* arr, int left, int right) 
{ 
	for (int i = left + 1; i <= right; i++) { 
		int temp = arr[i]; 
		int j = i - 1; 
		while (j >= left && arr[j] > temp) { 
			arr[j + 1] = arr[j]; 
			j--; 
		} 
		arr[j + 1] = temp; 
	} 
} 

void merge(int* arr, int l, int m, int r) 
{
	int len1 = m - l + 1, len2 = r - m; 
	int left[len1], right[len2]; 
	for (int i = 0; i < len1; i++) 
		left[i] = arr[l + i]; 
	for (int i = 0; i < len2; i++) 
		right[i] = arr[m + 1 + i]; 

	int i = 0, j = 0, k = l;
	while(i < len1 && j < len2){ 
		if(left[i] <= right[j])
		{ 
			arr[k] = left[i]; 
			i++; 
		} 
		else
		{ 
			arr[k] = right[j]; 
			j++; 
		} 
		k++; 
	}
	while(i < len1)
	{ 
		arr[k] = left[i]; 
		k++; 
		i++; 
	}
	while(j < len2)
	{ 
		arr[k] = right[j]; 
		k++; 
		j++; 
	} 
} 

void tim_sort(int arr[], int n) 
{ 
	for (int i = 0; i < n; i += RUN) 
		insertionSort(arr, i, fmin((i + RUN - 1), (n - 1))); 
	for(int size = RUN; size < n; size = 2 * size)
	{
		for(int left = 0; left < n; left += 2 * size)
		{
			int mid = left + size - 1; 
			int right = fmin((left + 2 * size - 1), (n - 1)); 
			if(mid < right) 
				merge(arr, left, mid, right); 
		} 
	} 
} 


void print_array(int arr[], int n) 
{ 
	for (int i = 0; i < n; i++) 
		printf("%d ", arr[i]); 
	printf("\n"); 
} 


int compareValeurs(const void* val1, const void* val2)
{
    if(val1 == val2) return 0;
    if(val1 < val2) return -1;
    return 1;
}


int main() 
{ 
	int arr[] = { -2, 7, 15, -14, 0, 15, 0, 7, 
				-7, -4, -13, 5, 8, -14, 12 }; 
	int n = sizeof(arr) / sizeof(arr[0]); 
	printf("Given Array is\n"); 
	print_array(arr, n); 

	// Function Call 
	tim_sort(arr, n); 

	printf("After Sorting Array is\n"); 
	print_array(arr, n); 

    int v = 100000;
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    int* tab = malloc(sizeof(int)*v);
    int* tab1 = malloc(sizeof(int)*v);
    srand(time(NULL));
    for(int i=0; i<v; i++)
    {
        int n = rand() % 1000;
        tab[i] = n;
        tab1[i] = n;
    }
    //print_array(tab,v);

    clock_t start = clock();

    tim_sort(tab,v);

    printf("%ld\n",(clock()-start)* 1000 / CLOCKS_PER_SEC);

    start = clock();

    qsort(tab1,v,sizeof(int), compareValeurs);

    printf("%ld\n",(clock()-start)* 1000 / CLOCKS_PER_SEC);

    //print_array(tab,v);

    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
	return 0; 
}
