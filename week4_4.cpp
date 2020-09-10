#include <iostream>

// 
int n;
long *array_CN;

long CatalanNumber(int i) {
    long res = 0;
    if ( i <= 1)
        return 1;
    for (int j = 0; j < i; ++j)
        res += array_CN[j] * array_CN[i-1-j];
    return res;
}


int main() {
    int tmp = scanf("%d", &n);
    if ((n < 3 ) || (n > 30)) {
        std::cout << "Bad n!\n";
        return 1;
    }
    array_CN = (long*)calloc(n, sizeof(long));
    
    for (int i = 0; i < n; ++i) {
        array_CN[i] = CatalanNumber(i);
    }
    std::cout << CatalanNumber(n-2);
    free(array_CN);
    return 0;
}
