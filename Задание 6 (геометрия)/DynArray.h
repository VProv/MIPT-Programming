#pragma once
#include <cassert>
template<typename T>
class DynArray {
T* buf;
size_t size, capacity;
static const double grow_factor;
static const unsigned int  startcapacity = 100;
public:
DynArray();
DynArray(const DynArray&);
DynArray(const T* arr, const int length);
~DynArray();
void SetDynArray(const DynArray&);
void SetDynArray(const T* arr, const int length);
unsigned int getcapacity() const;
unsigned int getsize() const;
void push_back(const T&);
void clear();
void eclear();//do not delet buf
T& operator [](const unsigned int)const;
T pop_back();
};

template<typename T>
const double DynArray<T>::grow_factor = 2;

template<typename T>
T DynArray<T>::pop_back() {
    if (size > 0) {
        T a = (*this)[size - 1];
        size--;
        return a;
    }
}

template<typename T>
void DynArray<T>::eclear() {
    size = 0;
}

template<typename T>
DynArray<T>::DynArray() {
buf = new T[startcapacity];
capacity = startcapacity;
size = 0;
}

template<typename T>
void DynArray<T>::SetDynArray(const DynArray& a) {
if (a.capacity <= this->capacity) {
this->size = a.size;
for (size_t i = 0; i < size; i++)
buf[i] = a[i];
}
else {
clear();
capacity = a.capacity;
size = a.size;
buf = new T[capacity];
for (size_t i = 0; i < size; i++)
buf[i] = a.buf[i];
}
return;
}

template<typename T>
DynArray<T>::DynArray(const DynArray& a) {
SetDynArray(a);
}

template<typename T>
void DynArray<T>::clear() {
delete[] buf;
capacity = 0;
size = 0;
}

template<typename T>
DynArray<T>::DynArray(const T* array, const int length) {
buf = new T[length + 1];
size = length;
capacity = length + 1;
for (int i = 0; i < length; i++) {
buf[i] = array[i];
}
}

template<typename T>
void DynArray<T>::SetDynArray(const T* ar, const int length) {
if (length <= capacity) {
this->size = length;
for (size_t i = 0; i < size; i++)
buf[i] = ar[i];
}
else {
clear();
if (length < DynArray<T>::startcapacity)
capacity = DynArray<T>::startcapacity;
else
capacity = length + 1;
size = length;
buf = new T[capacity];
for (size_t i = 0; i < size; i++)
buf[i] = ar[i];
}
return;
}

template<typename T>
DynArray<T>::~DynArray() {
clear();
}

template<typename T>
void DynArray<T>::push_back(const T& a) {
if (size + 1 > capacity) {
T* temp = buf;
buf = new T[static_cast<size_t>(capacity * grow_factor)];
capacity = static_cast<size_t>(capacity * grow_factor);
for (int i = 0; i < size; i++) {
buf[i] = temp[i];
}
delete[] temp;
buf[size] = a;
size++;
}
else {
buf[size] = a;
size++;
}
}

template<typename T>
T& DynArray<T>::operator [](const unsigned int a)const {
if (a < size)
    return buf[a];
else
    throw 1;
}

template<typename T>
unsigned int DynArray<T>::getcapacity()const {
return capacity;
}

template<typename T>
unsigned int DynArray<T>::getsize()const {
return size;
}
