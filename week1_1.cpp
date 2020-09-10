#include <iostream>
#include <cstdlib>

int ax, ay, bx, by;
float k, b;

struct coord {
    int px;
    int py;
    int ab_relative_position;
};

const char *to_str(int value) {
    if (!value) return "ON_SEGMENT";
    if (value == 1) return "ON_LINE";
    if (value == 2) return "LEFT";
    return "RIGHT";
}

void ab_relative(struct coord &crd) {
    int px = crd.px;
    int py = crd.py;
    if (py == k*px + b) {
        if ( ((px >= ax )&&(px <= bx)) || ((px <= ax)&&(px >= bx)) )
            crd.ab_relative_position = 0; // ON_SEGMENT
        else crd.ab_relative_position = 1; // ON_LINE
    }
    else {
        int y = k*px + b;
        if (bx >= ax) {
            if (y < py)
                crd.ab_relative_position = 2; //LEFT
            else crd.ab_relative_position = 3; //RIGHT
        }
        else {
            if (y > py)
                crd.ab_relative_position = 2; // LEFT
            else crd.ab_relative_position = 3; //RIGHT
        }
    }
}

int main() {
    int n = 0;
    
    scanf("%d %d %d %d", &ax, &ay, &bx, &by);
    k = (by-ay)/((float)(bx-ax));
    b = ay - ax*k;

    scanf("%d", &n);
    struct coord *array = (struct coord*)calloc(n, sizeof(struct coord));
    
    for (int i = 0; i < n; ++i) {
        scanf("%d %d",&(array[i].px), &(array[i].py));
    }
    
    for (int i = 0; i < n; ++i) {
        ab_relative(array[i]);
        std::cout << to_str(array[i].ab_relative_position) << std::endl;
    }
    
    free(array);

    return 0;
    
}

