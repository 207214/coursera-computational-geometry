#include <iostream>

int n;

struct coord {
    long long int x;
    long long int y;
    coord(): x(0), y(0) {}
};

void hoarasort_by_x(int first, int last, struct coord *arr) {
    int i = first;
    int j = last;
    
    long long int val = arr[(first+last) / 2].x;
    long long int y_val = arr[(first+last) / 2].y;
    coord tmp;
 
    do {
       while (1) {
           if  ( (arr[i].x < val) || ( (arr[i].x == val)&&(arr[i].y < y_val) ) )
               i++;
           else break;
       }
       
       while (1) {
           if  ( (arr[j].x > val) || ( (arr[j].x == val)&&(arr[j].y > y_val) ) )
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
        hoarasort_by_x(i, last, arr);
    if (first < j)
        hoarasort_by_x(first, j, arr);
}

bool rightTurn(struct coord &op1, struct coord &op2, struct coord &op3) {
    long long int x1 = op2.x - op1.x;
    long long int y1 = op2.y - op1.y;
    long long int x2 = op3.x - op2.x;
    long long int y2 = op3.y - op2.y;
    return x1*y2 - x2*y1 < 0;
}

bool leftTurn(struct coord &op1, struct coord &op2, struct coord &op3) {
    long long int x1 = op2.x - op1.x;
    long long int y1 = op2.y - op1.y;
    long long int x2 = op3.x - op2.x;
    long long int y2 = op3.y - op2.y;
    return x1*y2 - x2*y1 > 0;
}

int main() {
    scanf("%d", &n);
    struct coord *array 	= (struct coord*)calloc(2*n, sizeof(struct coord));
    struct coord *convexHull    = (struct coord*)calloc(2*n, sizeof(struct coord));
    struct coord *upper 	= (struct coord*)calloc(2*n, sizeof(struct coord));
    
    long long int max_y = 0;
    long long int min_y = 100000000;
    for (int i = 0; i < n; ++i) {
        scanf("%lld %lld", &(array[i].x), &(array[i].y));
        if (max_y < array[i].y)
            max_y = array[i].y;
            
        if (min_y > array[i].y)
            min_y = array[i].y;
    }

    hoarasort_by_x(0, n-1, array);
    
    convexHull[0] = array[0];
    convexHull[1] = array[1];
    int last = 1;// for lower
    for (int i = 2; i < n; ++i) {
        convexHull[i] = array[i];
        last = i;
        while ( (last > 1)&&(!leftTurn(convexHull[last-2], convexHull[last-1], convexHull[last])) ) {
            convexHull[last-1] = convexHull[last];
            last--;
//            std::cout << "AAA";
        }
    }//lower
    

    upper[0] = array[0];
    upper[1] = array[1];
    

    int last_2 = 1; // for upper
    for (int i = 2; i < n; ++i) {
        if ( (array[i].x == array[i-1].x)&&(array[i].y < array[i-1].y) )
            continue;
        upper[i] = array[i];
        last_2 = i;
        while ( (last_2 > 1)&&(!rightTurn(upper[last_2-2], upper[last_2-1], upper[last_2])) ) {
            upper[last_2-1] = upper[last_2];
            last_2--;
        }
    }//upper
    
    for (int i = last_2; i >= 0; --i) {
        convexHull[++last] = upper[i];
    }
    
    std::cout << last-1 << std::endl;
    std::cout << convexHull[1].x << " " << convexHull[1].y << " ";
    for (int i = 2; i <= last; ++i) {
        if ( (convexHull[i].x != convexHull[i-1].x) || (convexHull[i].y != convexHull[i-1].y) )
            std::cout << convexHull[i].x << " " << convexHull[i].y << " ";
    }
    
    if (upper) free(upper);
    if (array) free(array); 
    if (convexHull) free(convexHull);
    return 0;
}

// sorry for bad code