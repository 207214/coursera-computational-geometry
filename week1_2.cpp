#include <iostream>
#include <cstdlib>


int ax, ay, bx, by, cx, cy;
float k, b;

struct coord {
    int px;
    int py;
    int ab_relative_position;
    int triangle_pos;
};

const char *to_str(int value) {
    if (!value) return "BORDER";
    if (value == 1) return "INSIDE";
    return "OUTSIDE";
}

inline
void relative(struct coord &crd, int x1, int y1, int x2, int y2) {
    int px = crd.px;
    int py = crd.py;
    if (x1 != x2)
        k = (y2-y1)/((float)(x2-x1));
    b = y1 - x1*k;
    if ( (x1 != x2)&&(py == k*px + b)) {
        if ( ((px >= x1 )&&(px <= x2)) || ((px <= x1)&&(px >=x2)) )
            crd.ab_relative_position = 0; // ON_SEGMENT
        else crd.ab_relative_position = 1; // ON_LINE
    }
    else if ((x1 == x2)&&(px == x1)) {
        if ( ((py >= y1 )&&(py <= y2)) || ((py <= y1)&&(py >=y2)) )
            crd.ab_relative_position = 0; // ON_SEGMENT
        else crd.ab_relative_position = 1; // ON_LINE
    }
    else if ((x1 == x2)&&(px != x1)) {
        if (y2 > y1) {
            if (px > x1)
                crd.ab_relative_position = 3; // RIGHT
            else crd.ab_relative_position = 2; // LEFT
        }
        else {
            if (px > x1)
                crd.ab_relative_position = 2; // LEFT
            else crd.ab_relative_position = 3; // RIGHT
        }
    }
    
    else {
        int y = k*px + b;
        if (x2 >= x1) {
            if (y < py) {
                crd.ab_relative_position = 2;  }//LEFT
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
    scanf("%d %d %d %d %d %d", &ax, &ay, &bx, &by, &cx, &cy);

    scanf("%d", &n);
    struct coord *array = (struct coord*)calloc(n, sizeof(struct coord));
    
    for (int i = 0; i < n; ++i) {
        scanf("%d %d",&(array[i].px), &(array[i].py));
        array[i].triangle_pos = -1;
    }
    
    for (int i = 0; i < n; ++i) {
        relative(array[i], ax,ay,bx,by);
        int tmp = array[i].ab_relative_position;
        if (!tmp)
            array[i].triangle_pos = 0; // BORDER
        else if (tmp == 1)
            array[i].triangle_pos = 2; //OUTSIDE
        else {
            relative(array[i], ax,ay, cx,cy);
            int tmp_2 = array[i].ab_relative_position;
            if (!tmp_2)
                array[i].triangle_pos = 0;// BORDER
            else if (tmp_2 == 1)
                array[i].triangle_pos = 2; // OUTSIDE
            else if (tmp_2 == tmp)
                array[i].triangle_pos = 2; // OUTSIDE
            else {
                relative(array[i], bx,by,cx,cy);
                int tmp_3 = array[i].ab_relative_position;
                if (!tmp_3)
                    array[i].triangle_pos = 0; // BORDER;
                else if (tmp_3 == 1) 
                    array[i].triangle_pos = 2; // OUTSIDE;
                else if (tmp_3 != tmp)
                    array[i].triangle_pos = 2; // OUTSIDE;
            }
        }
        if (array[i].triangle_pos < 0)
            array[i].triangle_pos = 1; // INSIDE;
        std::cout << to_str(array[i].triangle_pos) << std::endl;
    }
    
    free(array);

    return 0;
    
}

