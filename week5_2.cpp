#include <iostream>
#include <cmath>
//#include <unistd.h>

//using namespace std;

struct coord {
    float x;
    float y;
};

unsigned result;
struct rectangle {
    coord low;
    coord up;
};

int n, q;
int num;
char ch;

coord *p;
rectangle *query;

int Compare(int value1, int value2) {
    return value1-value2;
}

class Binary_Tree;

class Node {
public:
    Node *left;
    Node *right;
    Binary_Tree *assoc;
    int Xleft;
    int Xright;
    int info[2];
    Node() : left(0), right(0){}
    Node(const int val1, const int val2) : left(0), right(0) {info[0] = val1; info[1] = val2; }
    void Show() { if (left) left->Show(); std::cout << info[0] << ", " << info[1] << "\n"; if (right) right->Show(); }
    void Count(unsigned *cnt) { if (left) left->Count(cnt); (*cnt)++; if (right) right->Count(cnt); } 
};


class Binary_Tree {
//private:
public:
    Node *head;
    unsigned size;

    Node *Searching(Node *start, int value, bool flag = 0)
    {
        if (!start) return 0;
        int cmp = Compare(value, (start->info)[flag]);
        if (cmp > 0) return Searching(start->right, value, flag);
        if (cmp < 0) return Searching(start->left, value, flag);
        //cout << start->info[flag] << endl;
        return start;
    }

    Node *Inserting(Node **start, int val1, int val2, bool flag = 0)
    {
        if (*start == 0)
        {
            size++;
            *start = new Node(val1, val2);
            return *start;
        }
        int cmp = Compare(val1*(!flag) + val2*(flag), ((*start)->info)[flag]);
        if (cmp >= 0) { (*start)->right = Inserting(&((*start)->right), val1, val2, flag); }
        if (cmp < 0) { (*start)->left  = Inserting(&((*start)->left), val1, val2, flag); }
        return *start;
    }

    void Deleting(Node **start, int value, bool flag = 0)
    {
        if (((*start)->info)[flag] == value) {
            Node *tmp_node = (*start);
            if ((*start)->left == 0 && (*start)->right == 0)
            {
                *start = 0;
                delete tmp_node;
            }
            else
            {
                if ((*start)->left == 0)
                {
                    *start = (*start)->right;
                    delete tmp_node;
                }
                else
                {
                    if ((*start)->right == 0)
                    {
                        *start = (*start)->left;
                        delete tmp_node;
                    }
                    else
                    {
                        Node *p1 = (*start);
                        Node *p2 = (*start)->left;
                        while (p2->right != 0)
                        {
                            p1 = p2;
                            p2 = p2->right;
                        }
                        *start = p1;
                        p1->right = p2->left;
                        p2->right = tmp_node->right;
                        p2->left = p1;
                        delete tmp_node;
                    }
                }
            }
        }
        else
        {
            int cmp = Compare(((*start)->info)[flag], value);
            if (cmp > 0)
                Deleting(&((*start)->left), value, flag);
            else
            {
                if (cmp < 0)
                    Deleting(&((*start)->right), value, flag);
            }
        }
    }
    int Sequently_Accessing(Node **start, bool flag) const;
    void Destroying(Node **start);

public:
    Node *Get_Head() const { return head; }
    unsigned Get_Size() const { return size; }
    Binary_Tree() : head(0), size(0) {}
    ~Binary_Tree() { Destroying(&head); }

    void Destroy() { Destroying(&head); }
    Node *Search(int value, bool flag = 0) {
        Node* tmp = Searching(head, value, flag);
        if (!tmp) std::cout << "Not found!\n";
        return tmp;
    }
    Node *Insert(int val1, int val2, bool flag = 0) { return Inserting(&head, val1, val2, flag); }
    void Delete(int val, bool flag) { Deleting(&head, val, flag); }
    void Sequent_Access(bool flag = 0) { Sequently_Accessing(&head, flag); }
    void Show() const { head->Show(); }
};



int Binary_Tree::Sequently_Accessing(Node **start, bool flag) const {
    if (*start)
    {
        int tmp = Sequently_Accessing(&((*start)->left), flag);
        if (1) {
            if (tmp != -1)
            {
                ch = getchar();
                if (ch == '\n') {
                    if ((*start)->info[flag])
                        std::cout << ++num << ") " << ((*start)->info)[flag] << std::endl; }
                    else return -1;
            }
            else return -1;
            tmp = Sequently_Accessing(&((*start)->right), flag);
        }
    }
    return 0;
}

void Binary_Tree::Destroying(Node **start)
{
    if (*start)
    {
        Destroying(&(*start)->right);
        Destroying(&(*start)->left);
        delete *start;
        *start = 0;
    }
}

/*
 "Tree Rebalancing  in Optimal Time and Space",
  QUENTIN F. STOUT and BETTE L. WARREN,
  September 1986
  
void tree_to_vine(Node *start, int &size) {
    Node *vine_tail;
    Node *remainder;
    Node *tmpptr;
    vine_tail = start;
    remainder = vine_tail->right;
    size = 0;
    while (remainder != nullptr) {
        if (remainder->left == nullptr) {
            vine_tail = remainder;
            remainder = remainder->right;
            size++;
        }
        else {
            tmpptr = remainder->left;
            remainder->left = tmpptr->right;
            tmpptr->right = remainder;
            remainder = tmpptr;
            vine_tail->right = tmpptr;
        }
    }
}

void compression(Node *start, int count) {
    Node *scanner;
    Node *child;
    scanner = start;

    for (int i = 1; i <= count; ++i) {

        child = scanner->right;
        if (child->right == nullptr) break;
        scanner->right = child->right;
        scanner = scanner->right;
        child->right = scanner->left;
        scanner->left = child;
    }

}

void vine_to_tree(Node *start, int &size) {
    int leaf_count = size + 1 - pow(2, (int)(log10(size+1)));
    compression(start, leaf_count);
    size -= leaf_count;
    while (size > 1) {
        compression(start, size/2);
        size /= 2;
    }
}

void rebalance(Node *start) {
    Node *pseudo_root = new Node;
    pseudo_root->right = start;
    int size;
    tree_to_vine(pseudo_root, size); // understood
    
    vine_to_tree(pseudo_root, size); // understood
    start = pseudo_root->right;
//    std::cout << " dUUU " << start->info[0] << " " << start->info[1] << "\n";
    delete pseudo_root;
}
 "Tree Rebalancing  in Optimal Time and Space",
  QUENTIN F. STOUT and BETTE L. WARREN,
  September 1986
*/

void hoarasort_by_y(int first, int last, struct coord *arr) {
    int i = first;
    int j = last;
    
    long long int val = arr[(first+last) / 2].y;
    long long int x_val = arr[(first+last) / 2].x;
    coord tmp;
 
    do {
       while (1) {
           if  ( (arr[i].y < val) || ( (arr[i].y == val)&&(arr[i].x < x_val) ) )
               i++;
           else break;
       }
       
       while (1) {
           if  ( (arr[j].y > val) || ( (arr[j].y == val)&&(arr[j].x > x_val) ) )
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
        hoarasort_by_y(i, last, arr);
    if (first < j)
        hoarasort_by_y(first, j, arr);
}


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

Node *FindSplitNode(Node *start, int x, int x_prime, bool flag = 0) {
    Node *v = start;
    while ( (v) && (v->left != nullptr || v->right != nullptr) && ((x_prime < (v->info)[flag]) || (x > (v->info)[flag])) ){
        if (x_prime < (v->info)[flag]) {
            v = v->left;    
        }
        else {
            v = v->right;
        }
    }
    return v;
}
void RangeQuery_1D(Node *start, int x, int x_prime, bool flag = 0) {
    if (!start) return;
    Node *v = FindSplitNode(start, x, x_prime, flag);
    if (!v) {
        return;
    }
    
    if ((v->info)[flag] >= x && (v->info)[flag] <= x_prime) {
        result++;
    }
    if (v->left == nullptr && v->right == nullptr) {
        return;
    }
    
    Node *vv;
    if (v->left) {
        vv = v->left;
        // условие x_prime >= выполняется    
        while ((vv)&&(vv->left != nullptr || vv->right != nullptr)) {
            if (x <= vv->info[flag]) {
                result++;
                if (vv->right) vv->right->Count(&result);
                vv = vv->left;
            }
            else {
                vv = vv->right;
            }
        }
    
        if ( vv && (vv->info)[flag] >= x && (vv->info)[flag] <= x_prime) {
            result++;
        }
    }
    
    if (v->right) {
        vv = v->right;
        // условие x <= выполняется    
        while ((vv)&&(vv->left != nullptr || vv->right != nullptr)) {
            if (x_prime >= (vv->info)[flag]) {
                result++;
                if (vv->left) vv->left->Count(&result);
                vv = vv->right;
            }
            else {
                vv = vv->left;
            }
        }
    
        if (vv && (vv->info)[flag] >= x && (vv->info)[flag] <= x_prime) {
            result++;
        }
    }    
}

void RangeQuery_2D(Node *start, int x, int x_prime, int y, int y_prime) {
    if (!start) return;
    Node *v = FindSplitNode(start, x, x_prime, 0);
//    std::cout << "SPLIT_NODE == " << v->info[0] << " " << v->info[1] << std::endl; 
    if (!v) {
        std::cout << result << "\n";
        return;
    }
    if ((v->info)[0] >= x && (v->info)[0] <= x_prime && (v->info)[1] >= y && (v->info)[1] <= y_prime) {
        result++;
    }
    if (v->left == nullptr && v->right == nullptr) {
        std::cout << result << "\n";
        return;
    }

    Node *vv;
    if (v->left) {
        vv = v->left;
        while ( (vv)&&(vv->left != nullptr || vv->right != nullptr)) {
            if ((vv->info)[0] >= x && (vv->info)[0] <= x_prime && (vv->info)[1] >= y && (vv->info)[1] <= y_prime) {
                result++;
            }
            if (x <= vv->info[0]) {

                if (vv->right) RangeQuery_1D(vv->right->assoc->Get_Head(), y, y_prime, 1);		
                vv = vv->left;

            }
            else {
                vv = vv->right;
            }
        }
    
        if (vv && (vv->info)[0] >= x && (vv->info)[0] <= x_prime && (vv->info)[1] >= y && (vv->info)[1] <= y_prime) {
            result++;
        }
    }
    
    if (v->right) {
        vv = v->right;
        // условие x <= выполняется    
        while ( (vv)&&(vv->left != nullptr || vv->right != nullptr)) {
            if ((vv->info)[0] >= x && (vv->info)[0] <= x_prime && (vv->info)[1] >= y && (vv->info)[1] <= y_prime) {
                result++;
            }
            if (x_prime >= (vv->info)[0]) {
                if (vv->left) RangeQuery_1D(vv->left->assoc->Get_Head(), y, y_prime, 1);
                vv = vv->right;
            }
            else {
                vv = vv->left;
            }
        }
    
        if ((vv)&&(vv->info)[0] >= x && (vv->info)[0] <= x_prime && (vv->info)[1] >= y && (vv->info)[1] <= y_prime) {
            result++;
        }
    }
    
    std::cout << result << "\n";
}

int Xleft_define(Node *node) {
    if (!node->left) return node->info[0];
    else return Xleft_define(node->left);
}

int Xright_define(Node *node) {
    if (!node->right) return node->info[0];
    else return Xright_define(node->right);
}

void Xdefine(Node *node) {
    if (!node) return;
    node->Xleft = Xleft_define(node);
    node->Xright = Xright_define(node);
    Xdefine(node->left);
    Xdefine(node->right);
}

//coord *tmp_array;
int index;

void forming_array(Node *node, int &ind, coord *tmp_array) {
    if (!node) return;
    tmp_array[ind].x = node->info[0];
    tmp_array[ind].y = node->info[1];
    ind++;
    forming_array(node->left, ind, tmp_array);
    forming_array(node->right, ind, tmp_array);
}

void assoc_building(Node *node, int &ind) {

    if (!node) return;
    struct coord *tmp_array = (struct coord*)calloc(n+2, sizeof(struct coord));
    forming_array(node, ind, tmp_array);
    node->assoc = new Binary_Tree;
    node->assoc->head = new Node;
    node->assoc->head->info[0] = tmp_array[0].x;
    node->assoc->head->info[1] = tmp_array[0].y;

    for (int i = 1; i < ind; ++i) {
        node->assoc->Insert(tmp_array[i].x, tmp_array[i].y, 1);
    }
    free(tmp_array);
    ind = 0;
    assoc_building(node->left, ind);
    ind = 0;
    assoc_building(node->right, ind);
}

int main(int argc, char **argv) {
    result = 0;
    
    FILE *f = stdin;
    if (argc > 1) {
        f = fopen(argv[1], "r");
    }
    int tmp = fscanf(f, "%d", &n);
    if ((n < 1) || (n > 30000)) {
        std::cout << "Bad n!\n";
        return 1;
    }
    p = (struct coord*)calloc(n, sizeof(struct coord));
    for (int i = 0; i < n; ++i) {
        tmp = fscanf(f, "%f %f", &(p[i].x), &(p[i].y));
    }

    hoarasort_by_y(0, n-1, p);
    Binary_Tree tree;
    for (int i = 0; i < n; ++i) {
        tree.Insert(p[i].x, p[i].y, 0);
    }
    
    hoarasort_by_x(0, n-1, p);
    Node *h = tree.Get_Head();
    Xdefine(h);    
    int index = 0;
    assoc_building(h, index);
    tmp = fscanf(f, "%d", &q);
    
    if ((q < 1) || (q > 30000)) {
        std::cout << "Bad q!\n";
        return 2;
    }
    
    query = (struct rectangle*)calloc(q, sizeof(struct rectangle));
    for (int i = 0; i < q; ++i) {
        tmp = fscanf(f, "%f %f %f %f", &(query[i].low.x), &(query[i].low.y), &(query[i].up.x), &(query[i].up.y) );
        if (query[i].low.y > query[i].up.y) {
            std::swap(query[i].low, query[i].up);
        }
    }
    
//    tree.Show();
//    rebalance(h);
//    std::cout << "\n";
//    tree.Show();
    for (int i = 0; i < q; ++i) {
        result = 0;
        RangeQuery_2D(h, std::min(query[i].low.x, query[i].up.x),
                         std::max(query[i].low.x, query[i].up.x),
                         query[i].low.y,
                         query[i].up.y);
    }
    fclose(f);
    free(p);
    free(query);
    return 0;
}
