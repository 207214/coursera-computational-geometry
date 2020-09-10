#include <iostream>
#include <cmath>
#include <cstdio>
//#include <unistd.h>

#define PREV_IN (sign1 >= 0)
#define CURR_IN (sign2 >= 0)
#define PREV_OUT (sign1 < 0)
#define CURR_OUT (sign2 < 0)
unsigned n, m;
unsigned resulting_maxnum;

struct coord {
    float x;
    float y;
    bool to_show;
//    bool good;
//    bool inter;
    void show() { std::cout << (int)round(x) << " " << (int)round(y) << " "; }
    bool operator==(const coord &op) { return x == op.x && y == op.y; }
    bool sameround(const coord &op) { return round(x) == round(op.x) && round(y) == round(op.y); }
};

coord *a;
coord *b; //
coord *result;

inline
bool isarea(coord &aa, coord &bb, coord &cc) {
    
    if ((round(aa.x) == round(bb.x))&&(round(aa.y) == round(bb.y))) return 0;
    if ((round(aa.x) == round(cc.x))&&(round(aa.y) == round(cc.y))) return 0;
    if ((round(bb.x) == round(cc.x))&&(round(bb.y) == round(cc.y))) return 0;
    bool a = aa.x != bb.x;
    bool b = bb.x != cc.x;
    bool c = aa.y != bb.y;
    bool d = bb.y != cc.y;
    return a||b||c||d;
}

/*int pointSearch(const coord &to_search) {
    int j = 0;
    while (! (result[j++] == to_search) );
    return j-1;
-}*/


float xInter(coord p1, coord p2, coord p3, coord p4) {
    return ((p1.x*p2.y - p1.y*p2.x)*(p3.x-p4.x) - (p1.x-p2.x)*(p3.x*p4.y - p3.y*p4.x))/(float)(((p1.x-p2.x)*(p3.y-p4.y)-(p1.y-p2.y)*(p3.x-p4.x)));
}

float yInter(coord p1, coord p2, coord p3, coord p4) {
    return ((p1.x*p2.y - p1.y*p2.x)*(p3.y-p4.y) - (p1.y-p2.y)*(p3.x*p4.y - p3.y*p4.x))/(float)(((p1.x-p2.x)*(p3.y-p4.y)-(p1.y-p2.y)*(p3.x-p4.x)));
}


void resultRefresh(unsigned ind) {

    unsigned newsize = 0;
    coord fresh[resulting_maxnum];
    for (unsigned j = 0; j < resulting_maxnum; ++j)
        fresh[j].to_show = 1;
    
    const coord a1 = a[ind];
    const coord a2 = a[(ind+1)%n];
    for (unsigned i = 0; i < m; ++i) {
        coord prevPoint = result[i];
        coord currPoint = result[(i+1)%m];
        
 //       prevPoint.show();
 //       std::cout << "	";
 //       currPoint.show();
        float sign1 = (a2.x-a1.x)*(prevPoint.y - a2.y) - (prevPoint.x - a2.x)*(a2.y - a1.y);
        float sign2 = (a2.x-a1.x)*(currPoint.y - a2.y) - (currPoint.x - a2.x)*(a2.y - a1.y);
        
        if (PREV_OUT && CURR_OUT) { /*std::cout << "\n out, out\n";*/}
        else if (PREV_OUT && CURR_IN) {
//        std::cout << "\n out, int\n";
            float valx = xInter(prevPoint, currPoint, a1, a2);
            float valy = yInter(prevPoint, currPoint, a1, a2);
//            std::cout << "POINTS " << a1.x << " " << a1.y << ", " << a2.x << " " << a2.y << " AND " << prevPoint.x << " " << prevPoint.y
//                        << ", " << currPoint.x << " " << currPoint.y << std::endl;
//            std::cout << "INTER " << valx << " " << valy << std::endl;  
            fresh[newsize].x =  valx; //(xInter(prevPoint, currPoint, a1, a2));
            fresh[newsize++].y = valy; //(yInter(prevPoint, currPoint, a1, a2));
            
            fresh[newsize++] = currPoint; 
        }
        else if (PREV_IN && CURR_OUT) {
//        std::cout << "\n in, out\n";
            float valx = xInter(prevPoint, currPoint, a1, a2);
            float valy = yInter(prevPoint, currPoint, a1, a2);
//            std::cout << "POINTS " << a1.x << " " << a1.y << ", " << a2.x << " " << a2.y << " AND " << prevPoint.x << " " << prevPoint.y
//                        << ", " << currPoint.x << " " << currPoint.y << std::endl;
//            std::cout << "INTER " << valx << " " << valy << std::endl;  

            fresh[newsize].x =  valx;
            fresh[newsize++].y = valy; //(yInter(prevPoint, currPoint, a1, a2));
        }
        else {
//        std::cout << "\n in, in\n";
            fresh[newsize++] = currPoint;
        }        
    }
    m = newsize;
    unsigned real_index = 0;
    for (unsigned i = 0; i < m; ++i ) {
        if ( (i>0) && fresh[i].sameround(fresh[i-1]) )
            continue;
        result[real_index++] = fresh[i];
    }
    m = real_index;
}

int main(int argc, char **argv) {
    FILE *f = stdin;
    if (argc > 1)
        f = fopen(argv[1], "r");
    
    int tmp = fscanf(f, "%u", &n);
    a = (struct coord*)calloc(n+1, sizeof(struct coord));

    if (!a) {
        fprintf(stderr, "calloc() error while allocating memory for the polygon 1\n");
        return 1;
    }

    for (unsigned i = 0; i < n; ++i) {
        tmp = fscanf(f, "%f %f", &(a[i].x), &(a[i].y));
//        a[i].good = 1;
    }

    tmp = fscanf(f, "%u", &m);
    b = (struct coord*)calloc(m+1, sizeof(struct coord));
    if (!b) {
        fprintf(stderr, "calloc() error while allocating memory for the polygon 2\n");
        return 1;
    }
    
    for (unsigned i = 0; i < m; ++i) {
        tmp = fscanf(f, "%f %f", &(b[i].x), &(b[i].y));
//        b[i].good = 1;
//        b[i].inter = 0;
    }
    
    resulting_maxnum = 3*m;
    result = (struct coord*)calloc(resulting_maxnum+1, sizeof(struct coord));
    if (!result) {
        fprintf(stderr, "calloc() error while allocating memory for the resulting polygon\n");
        return 1;
    }
    for (unsigned i = 0; i < m; i++) {
        result[i] = b[i/*/3*/];
        result[i].to_show = 1;
//        result[i+1].good = 0;
//        result[i+2].good = 0;
    }
//    result[resulting_maxnum].good = 0;
    
    
    for (unsigned i = 0; i < n; ++i) {
//        std::cout << "PLANE " << a[i].x << " " <<a[i].y << ", " << a[(i+1)%n].x << " " << a[(i+1)%n].y << std::endl;
        resultRefresh(i);
    }
    
    unsigned i = 1;
    int x1 =  round(result[0].x);
    int y1 =  round(result[0].y);
    unsigned mcopy = m;
    while (i <= m) {
        int x2 =  round(result[i%m].x);
        int y2 =  round(result[i%m].y);
        if ((x2 == x1)&&(y1 == y2)) {
            result[i%m].to_show = 0;
            mcopy--;
        }
        i++;
        x1 = x2;
        y1 = y2;
    }
    
    i = 0;
    bool isArea = 0;
    do {
        if (m > 0) isArea = isarea(result[i%m], result[(i+1)%m], result[(i+2)%m]);
        i++;
        if (isArea) break;
    } while(i < m);

    if (!isArea) { 
        std::cout << 0 << std::endl;
        return 0;
    }
    
    i = 0;
  //  int k = 1;
    std::cout << mcopy << std::endl;
    while (i < m) {
        if (result[i].to_show) {
    //        std::cout << k++ << ") ";
            result[i].show();
//            std::cout << "\n";
        }
        i++;
    }
    
    fclose(f);
    free(a);
    free(b);
    free(result);
    return 0;
}