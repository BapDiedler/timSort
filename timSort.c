#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include <time.h>

#define RUN 32

void insertionSort(int* arr, int left, int right){
    for(int i = left + 1; i <= right; i++){
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) { 
			arr[j + 1] = arr[j]; 
			j--; 
		} 
		arr[j + 1] = temp; 
    }
}

void merge(int* arr, int* temp, int l, int m, int r){
    int i = l, j = m + 1, k = l;
    while(i <= m && j <= r) {
        if(arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }
    while(i <= m)
        temp[k++] = arr[i++];
    while(j <= r)
        temp[k++] = arr[j++];
    for(i = l; i <= r; i++)
        arr[i] = temp[i];
}

int min(int a, int b){
    return (a < b) ? a : b;
}

void tim_sort(int arr[], int n){
    int* temp = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i += RUN)
        insertionSort(arr, i, min((i + RUN - 1), (n - 1)));
    for(int size = RUN; size < n; size = 2 * size) {
        for(int left = 0; left < n; left += 2 * size){
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));
            if(mid < right)
                merge(arr, temp, left, mid, right);
        }
    }
    free(temp);
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

    int v = 1000000;
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    int* tab = malloc(sizeof(int)*v);
    int* tab1 = malloc(sizeof(int)*v);
    srand(time(NULL));
    for(int i=0; i<v; i++)
    {
        int n = rand() % 50;
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
	printf("On remarque que le quick sort de la bibliothèque standard C est 3 fois plus rapide que le TimSort.\nMais cela dépend de plusieur paramêtre car plus la variance des nombres dans le tableau est faible plus rapide est notre algorithme;\n");
	return 0; 
}
