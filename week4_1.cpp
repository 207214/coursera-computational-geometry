#include <iostream>
#include <cstdio>
#include <unistd.h>
struct coord {
    float x;
    float y;
};


struct edge {
    coord a;
    coord b;
};

int n, m;
float max_x, min_x;

coord *a;
edge *edges;

float xInter(coord p1, coord p2, coord p3, coord p4) {
//    std::cout << "DEN::: \n";
//    std::cout << "\t" << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << " " << p3.x << " " << p3.y << " " << p4.x << " " << p4.y << std::endl;
    return ((p1.x*p2.y - p1.y*p2.x)*(p3.x-p4.x) - (p1.x-p2.x)*(p3.x*p4.y - p3.y*p4.x))/(((p1.x-p2.x)*(p3.y-p4.y)-(p1.y-p2.y)*(p3.x-p4.x)));
}

float yInter(coord p1, coord p2, coord p3, coord p4) {
    return ((p1.x*p2.y - p1.y*p2.x)*(p3.y-p4.y) - (p1.y-p2.y)*(p3.x*p4.y - p3.y*p4.x))/(((p1.x-p2.x)*(p3.y-p4.y)-(p1.y-p2.y)*(p3.x-p4.x)));
}

bool segmentsIntersection1(coord &p1, coord &p2, coord &q1, coord &q2, coord &inter) {
//    std::cout << "EDGE " << q1.x << " " << q1.y << " " << q2.x << " " << q2.y << std::endl;
    float sign_q1 = (p2.x - p1.x)*(q1.y - p2.y) - (p2.y - p1.y)*(q1.x-p2.x);
    float sign_q2 = (p2.x - p1.x)*(q2.y - p2.y) - (p2.y - p1.y)*(q2.x-p2.x);
    float sign_p1 = (q2.x - q1.x)*(p1.y - q2.y) - (q2.y - q1.y)*(p1.x-q2.x);
    float sign_p2 = (q2.x - q1.x)*(p2.y - q2.y) - (q2.y - q1.y)*(p2.x-q2.x);

    if (((sign_q1 > 0)&&(sign_q2 > 0)) || ((sign_q1 < 0)&&(sign_q2 < 0))||  ((sign_p1 > 0)&&(sign_p2 > 0)) || ((sign_p1 < 0)&&(sign_p2 < 0)) )  {
        return 0;
    }

    if ( (p1.y-p2.y)/(float)(p1.x-p2.x) == (q1.y-q2.y)/(float)(q1.x-q2.x) ) {
        float maxy = std::max(p1.y, p2.y);
        float miny = std::min(p1.y, p2.y);
        float maxx = std::max(p1.x, p2.x);
        float minx = std::min(p1.x, p2.x);
        if ( ((q1.x < maxx)&&(q1.x > minx)&&(q1.y < maxy)&&(q1.y > miny)) || ((q2.x < maxx)&&(q2.x > minx)&&(q2.y < maxy)&&(q2.y > miny)) ) {
            return 1;
        }
        
        maxy = std::max(q1.y, q2.y);
        miny = std::min(q1.y, q2.y);
        maxx = std::max(q1.x, q2.x);
        minx = std::min(q1.x, q2.x);
        if ( ((p1.x < maxx)&&(p1.x > minx)&&(p1.y < maxy)&&(p1.y > miny)) || ((p2.x < maxx)&&(p2.x > minx)&&(p2.y < maxy)&&(p2.y > miny)) ) {
            return 1;
        }//?!??!?!??!

        return 0;
    }
    // к этому моменту точка пересечения одна и только одна
    
    if ( (p1.x == q1.x && p1.y == q1.y) || (p1.x == q2.x && p1.y == q2.y) || 
        (p2.x == q1.x && p2.y == q1.y) || (p2.x == q2.x && p2.y == q2.y) )
            return 0;
    return 1;
}


bool segmentsIntersection2(coord &p1, coord &p2, coord &q1, coord &q2, coord &inter) {
    float sign_q1 = (p2.x - p1.x)*(q1.y - p2.y) - (p2.y - p1.y)*(q1.x-p2.x);
    float sign_q2 = (p2.x - p1.x)*(q2.y - p2.y) - (p2.y - p1.y)*(q2.x-p2.x);
    float sign_p1 = (q2.x - q1.x)*(p1.y - q2.y) - (q2.y - q1.y)*(p1.x-q2.x);
    float sign_p2 = (q2.x - q1.x)*(p2.y - q2.y) - (q2.y - q1.y)*(p2.x-q2.x);
    
//    std::cout << "SIGNS == " << sign_q1 << "	" << sign_q2 << "	" << sign_p1 << "	" << sign_p2 << std::endl;
    if (((sign_q1 > 0)&&(sign_q2 > 0)) || ((sign_q1 < 0)&&(sign_q2 < 0))||  ((sign_p1 > 0)&&(sign_p2 > 0)) || ((sign_p1 < 0)&&(sign_p2 < 0)) )  {
        return 0;
    }
    
    
    inter.x = xInter(p1,p2,q1,q2);
    inter.y = yInter(p1,p2,q1,q2);
    return 1;
}

bool insidePolygon(coord &p) {
    int num = 0;
    coord p1;
    coord p2;
    p1.x = min_x;
    p1.y = p.y;
    p2.x = max_x;
    p2.y = p.y;
    for (int i = 0; i <= n-1; ++i) {
        coord q1 = edges[i].a;
        coord q2 = edges[i].b;
//        std::cout << q1.x << " " << q1.y << " " << q2.x << " " << q2.y << "\n";
        coord inter;
        bool tmp = segmentsIntersection2(p1,p2,q1,q2,inter);
//        std::cout << "\n tmp == " << tmp << " " << inter.x << " " << inter.y << " " <<  q1.x << " " << q1.y << " " << q2.x << " " << q2.y << std::endl;
        if ((inter.x < p.x/*-0.01*/)&&(tmp)&&(!(i == n-1 && inter.x == edges[i].b.x && inter.y == edges[i].b.y))) {
            num++;
//            std::cout << "\n INTER " << inter.x << " " << inter.y << std::endl;
        }
        if (inter.x == edges[i].b.x && inter.y == edges[i].b.y)
            i++;
    }
//    std::cout << num << std::endl;
    return num%2;
}

void classify_diag(int i, int j) {
    coord p1 = a[i];
    coord p2 = a[j];
    int intersects = 0;
    for (int k = 0; k < n; ++k) {
        if (segmentsIntersection1(p1,p2, edges[k].a, edges[k].b, p1)) {
            intersects++;
        }
    }
    if (intersects) {
        std::cout << "INTERSECT\n";
        return;
    }
    
    coord half;
    half.x = (a[i].x+a[j].x)/(float)2;
    half.x += 0.001;
    half.y = (a[i].y+a[j].y)/(float)2;
    half.y += 0.001;
    if (insidePolygon(half)) {
        std::cout << "INTERNAL\n";
    }
    else std::cout << "EXTERNAL\n";
    
}

int main(int argc, char **argv) {
    FILE *f = stdin;
    if (argc > 1) {
        f = fopen(argv[1], "r");
    }
    int tmp = fscanf(f,"%d", &n);
    
    a = (struct coord*)calloc(n, sizeof(struct coord));
    if (!a) {
        fprintf(stderr, "calloc error\n");
        return 1;
    }
    
    edges = (struct edge*)calloc(n, sizeof(struct edge));
    
    max_x = 10000.0f;
    min_x = -10000.0f;
    
    for (int i = 0; i < n; ++i) {
        tmp = fscanf(f, "%f %f", &(a[i].x), &(a[i].y));
        if (a[i].x >= max_x)
            max_x = a[i].x;
        if (a[i].x <= min_x)
            min_x = a[i].x;
        if (i) {
            edges[i-1].a = a[i-1];
            edges[i-1].b = a[i];
        }
    }
    edges[n-1].a = a[n-1];
    edges[n-1].b = a[0];
    
    m = n*(n-3)/2; // diag-s number
    std::cout << m << std::endl;
    
//    int k = 0;
    for (int j = 2; j < n-1; ++j) {
        std::cout <</* ++k << ") " <<*/ a[0].x << " " << a[0].y << " " << a[j].x << " " << a[j].y << " ";
        classify_diag(0,j);
//        std::cout << "\n";
    }
    
    for (int i = 1; i <= n-3; ++i) {
        int j = i+2;
        while (j <= n-1) {
            std::cout << /*++k << ") " <<*/ a[i].x << " " << a[i].y << " " << a[j].x << " " << a[j].y << " ";
            classify_diag(i, j);
            j++;
//            std::cout << "\n";
        }
    }
    free(a);
    free(edges);
    fclose(f);
    return 0;
}
