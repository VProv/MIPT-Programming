#include <iostream>

using namespace std;

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return i * 2;
}

int right(int i) {
    return i * 2 + 1;
}

void sift_up(int size, int*a) {
    int i = size;
    int x = a[i];
    while (i > 1 && a[parent(i)] < x) {
        a[i] = a[parent(i)];
        i = parent(i);
        a[i] = x;
    }
}


void insert(int c, int* a, int* size) {
    (*size)++;
    a[(*size)] = c;
    sift_up((*size), a);

}

void sift_down(int i, int* a, int size) {
    int n = size;
    int largest = -1;
    if (left(i) <= n && a[left(i)] > a[i])
        largest = left(i);
    else
        largest = i;

    if (right(i) <= n && a[right(i)] > a[largest])
        largest = right(i);

    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        sift_down(largest, a, size);
    }

}


int extract_max(int* a, int* size) {
    if ((*size) < 1)
        return -1;
    int n = (*size);
    int max = a[1];
    a[1] = a[n];
    (*size)--;
    sift_down(1, a, (*size));
    return max;

}


int main() {
    int n = 0;
    cin >> n;
    int size = 0;
    int a[1000];
    for (int i = 0; i < n; i++) {
        int t = 0;
        cin >> t;
        if (t == 0) {
            int c = 0;
            cin >> t;
            insert(t, a, &size);
        }
        else if (t == 1) {
            cout << extract_max(a, &size);

        }
    }

    system("pause");

    return 0;

}