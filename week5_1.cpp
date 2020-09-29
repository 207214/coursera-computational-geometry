#include <iostream>
#include <cmath>

int n, m;
int *array;
int *query;

void hoarasort(int first, int last, int *arr) {
    int i = first;
    int j = last;
    
    int val = arr[(first+last) / 2];
    int tmp;
 
    do {
       while (1) {
           if  ( arr[i] < val )
               i++;
           else break;
       }
       
       while (1) {
           if  ( arr[j] > val )
               j--;
           else break;
       }
                  
        
       if (i <= j) {
           if (i < j) {
               tmp = arr[i];
               arr[i] = arr[j];
               arr[j] = tmp;
           }
           i++;
           j--;
        }
    } while (i <= j);
 
    if (i < last)
        hoarasort(i, last, arr);
    if (first < j)
        hoarasort(first, j, arr);
}

int closestPoint(int qp) {
    if (qp <= array[0])
        return array[0];
    if (qp >= array[n-1])
        return array[n-1];
    int i = 0;
    while (qp >= array[i]) {
        ++i;
    }
    return array[i] - qp > qp - array[i-1] ? array[i-1] : array[i]; 
}

int main(int argc, char **argv) {

    FILE *f = stdin;
    if (argc > 1) {
        f = fopen(argv[1], "r");
    }
    int tmp = fscanf(f, "%d", &n);
    if ((n < 1) || (n > 50000)) {
        std::cout << "Bad n!\n";
        return 1;
    }
    array = (int*)calloc(n, sizeof(int));
    
    for (int i = 0; i < n; ++i) {
        tmp = fscanf(f, "%d", &(array[i]));
    }
    
    tmp = fscanf(f, "%d", &m);
    if ((m < 1) || (m > 50000)) {
        std::cout << "Bad m!\n";
        return 2;
    }
    
    query = (int*)calloc(m, sizeof(int));
    
    for (int i = 0; i < m; ++i) {
        tmp = fscanf(f, "%d", &(query[i]));
    }
    hoarasort(0, n-1, array);
    
    for (int i = 0; i < m; ++i) {
        std::cout << closestPoint(query[i]) << std::endl;
    }
    free(array);
    fclose(f);
    free(query);
    return 0;
}