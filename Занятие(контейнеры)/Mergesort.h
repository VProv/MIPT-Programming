#pragma once


using namespace std;

template <typename t>
int mergesort(t* a, int left, int right, t* temp) {
    if (left == right)
        return 0;
    sort(a.begin(), a.end(), Cmp());
    int mid = (left + right) / 2;
    mergesort(a, left, mid, temp);
    mergesort(a, mid + 1, right, temp);

    int i = left;
    int j = mid + 1;
    for (int step = 0; step < right - left + 1; step++) {
        if ((j > right) || (i <= mid && a[i] < a[j])) {
            temp[step] = a[i];
            i++;
        }
        else {
            temp[step] = a[j];
            j++;
        }
    }

    for (int i = 0; i < right - left + 1; i++)
        a[left + i] = temp[i];
    return 0;
}