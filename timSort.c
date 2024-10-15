#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include <time.h>

#define RUN 16 //taille maximale des segments à trier

void insertion_sort(int* tab, int l, int r)
{
    for(int i = l + 1; i <= r; i++){
        int tmp = tab[i];
        int j = i - 1;
        while (j >= l && tab[j] > tmp) { 
			tab[j + 1] = tab[j]; 
			j--; 
		} 
		tab[j + 1] = tmp; 
    }
}

void merge(int* tab, int* tmp, int l, int m, int r)
{
    int i = l, j = m + 1, k = l;
    while(i <= m && j <= r) {
        if(tab[i] <= tab[j])
            tmp[k++] = tab[i++];
        else
            tmp[k++] = tab[j++];
    }
    while(i <= m)
        tmp[k++] = tab[i++];
    while(j <= r)
        tmp[k++] = tab[j++];
    for(i = l; i <= r; i++)
        tab[i] = tmp[i];
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}

void tim_sort(int tab[], int n)
{
    int* tmp = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i += RUN)
        insertion_sort(tab, i, min((i + RUN - 1), (n - 1)));
    for(int size = RUN; size < n; size = 2 * size) {
        for(int l = 0; l < n; l += 2 * size){
            int mid = l + size - 1;
            int r = min((l + 2 * size - 1), (n - 1));
            if(mid < r)
                merge(tab, tmp, l, mid, r);
        }
    }
    free(tmp);
}


void print_array(int tab[], int n) 
{ 
	for (int i = 0; i < n; i++) 
		printf("%d ", tab[i]); 
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
	int tab[] = { -2, 7, 15, -14, 0, 15, 0, 7, 
				-7, -4, -13, 5, 8, -14, 12 }; 
	int n = sizeof(tab) / sizeof(tab[0]); 
	printf("Given Array is\n"); 
	print_array(tab, n); 

	// Function Call 
	tim_sort(tab, n); 

	printf("After Sorting Array is\n"); 
	print_array(tab, n); 

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
	printf("On remarque que le quick sort de la bibliothèque standard C est 3 fois plus rapide que le TimSort.\nMais cela dépend de plusieur paramêtre car plus la variance des nombres dans \nle tableau est faible plus rapide est notre algorithme;\n");
	printf("On peut aussi manipuler la constante RUN pour améliorer notre score\n");
	return 0; 
}
