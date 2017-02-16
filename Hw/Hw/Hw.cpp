#include <iostream>
#include <cstring>

using namespace std;

struct node {
    node * prev;
    int d;
    long long max; // the overall maximum
    long long maxs; // maximum with this element
};


int push(int n, node** top);
int easy_push(int n, node** top);
int pop(node** top);
int size(node* top);
int clear(node** top);
int back(node* top);
int easy_pushA(int n, node** top);

int main() {
    node* top = NULL; // when decreasing
    node* top2 = NULL; // when increasing

    int n = 0;
    int l = 0;
    long long min = -1;
    long long temk = 0;
    long long maxniz = 0;
    cin >> n;
    if (n == 0) {
        cout << 0;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        int h = 0;
        cin >> h;
        if (i == 0)
            push(h, &top);
        else if (h <= top->d && top2 == NULL)
            push(h, &top);
        else if (top2 != NULL && h > top2->d)
            easy_push(h, &top2);
        else if (top2 != NULL && h <= top2->d) {
            int t = 0;
            t = pop(&top2);
            easy_pushA(t, &top);
            while (top2 != NULL) {
                t = pop(&top2);
                push(t, &top);
            }
            if (h <= top->d)
                push(h, &top);
            else
                easy_push(h, &top2);
        }
        else if (h > top->d)
            easy_push(h, &top2);
        
        if (i == 0) {
            min = h;
            maxniz = h;
            temk++;
        }
        else {
            if (min == -1) {
                min = top->d;
            }
            if (top != NULL && top->d > min && min != -1) {
                temk++;
            }
            else if (top != NULL && top->d <= min && min != -1) {
                min = top->d;
                temk++;            
            }
            if (temk * min > maxniz)
                maxniz = temk * min;
            if (top != NULL && top->d == 0) {
                min = -1;
                temk = 0;
            }
        }        
    }
    if (top2 != NULL) {
        int t = 0;
        t = pop(&top2);
        easy_pushA(t, &top);
        while (top2 != NULL) {
            t = pop(&top2);
            push(t, &top);
        }
    }
    
    if (top->max > maxniz)
        cout << top->max << endl;
    else
        cout << maxniz << endl;
    system("pause");
    clear(&top);
    return 0;
}


int push(int n, node** top) {
    if (*top == NULL) {
        *top = new node;
        (*top)->prev = NULL;
        (*top)->d = n;
        (*top)->max = n;
        (*top)->maxs = n;
    }

    else if ((*top) != NULL) {
        node * a = *top;
        *top = new node;
        (*top)->prev = a;
        (*top)->d = n;
        if (a->d == 0) {
            (*top)->max = a->max;
            (*top)->maxs = 0;            
        }
        else if ((((a->maxs) / (a->d) + 1) * n) > a->max) {
            (*top)->max = (((a->maxs) / (a->d) + 1) * n);
            (*top)->maxs = (((a->maxs) / (a->d) + 1) * n);
        }
        else {
            (*top)->max = a->max;
            (*top)->maxs = (((a->maxs) / (a->d) + 1) * n);
        }
    }

    return 1;
}

int pop(node** top) {
    node *a;
    int h = 0;
    a = (*top)->prev;
    h = (*top)->d;
    delete *top;
    (*top) = a;

    return h;
}


int size(node* top) {
    int siz = 0;

    node * a = top;
    while (a != NULL) {
        ++siz;
        a = a->prev;
    }

    return siz;
}

int clear(node** top) {

    node * a = NULL;

    while ((*top) != NULL) {
        a = (*top)->prev;
        delete *top;
        *top = a;
    }

    return 1;
}

int back(node* top) {
    return top->d;
}

int easy_push(int n, node** top) {
    if (*top == NULL) {
        *top = new node;
        (*top)->prev = NULL;
        (*top)->d = n;
    }

    else if ((*top) != NULL) {
        node * a = *top;
        *top = new node;
        (*top)->prev = a;
        (*top)->d = n;
    }

    return 1;
}

int easy_pushA(int n, node** top) {

     if ((*top) != NULL) {
        node * a = *top;
        *top = new node;
        (*top)->prev = a;
        (*top)->d = n;
        if ((a->maxs + a->d) > a->max && (a->maxs + a->d) > n) {
            (*top)->max = (a->maxs + a->d);
            (*top)->maxs = n;
        }
        else if (n > a->max) {
            (*top)->max = n;
            (*top)->maxs = n;
        }
        else {
            (*top)->max = a->max;
            (*top)->maxs = n;
        }
    }


    return 1;
}