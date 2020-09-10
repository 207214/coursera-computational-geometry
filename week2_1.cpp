# include <iostream>

struct coord {
    int x;
    int y;
};

int n;
bool isconvex(struct coord *arr) {
    int i = 0;
    bool res = 1;
    
    while ((res)&&(i<n)) {
        int x1 = arr[(i+1)%n].x - arr[i].x;
        int x2 = arr[(i+2)%n].x - arr[(i+1)%n].x;
        int y1 = arr[(i+1)%n].y - arr[i].y;
        int y2 = arr[(i+2)%n].y - arr[(i+1)%n].y;
        i++;
        res = (x1*y2 - y1*x2  >= 0);   
    }
    
    return res;
}

int main() {
    
    n = 0;
    scanf("%d", &n); // number of polygon vertices
    struct coord *array = (struct coord*)calloc(n, sizeof(struct coord));
    
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &(array[i].x), &(array[i].y));
        
    }
    
    bool isConvex = isconvex(array);
    
    if (isConvex)
         std::cout << "CONVEX";
    else std::cout << "NOT_CONVEX";
    
    free(array);
    return 0;
}