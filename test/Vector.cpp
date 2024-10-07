#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>

template <typename T>
class Vector {
protected:
    int _size;
    int _capacity;
    T* _elem;

    void copyFrom(T const* A, int lo, int hi);
    void expand();
    void shrink();

    bool bubble(int lo, int hi);
    void bubbleSort(int lo, int hi);

    int max(int lo, int hi);
    void selectionSort(int lo, int hi);

    void merge(int lo, int mi, int hi);
    void mergeSort(int lo, int hi);

    int partition(int lo, int hi);
    void quickSort(int lo, int hi);

    void heapSort(int lo, int hi);

public:
    Vector(int c = 3, int s = 0, T const& v = T());
    Vector(T const* A, int lo, int hi);
    Vector(T const* A, int n);
    Vector(Vector<T> const& V, int lo, int hi);
    Vector(Vector<T> const& V);
    ~Vector();

    void push_Back(T const& value);
    int size() const;
    bool empty() const;
    int disordered() const;

    int find(T const& e) const;
    int find(T const& e, int lo, int hi) const;
    int search(T const& e) const;
    int search(T const& e, int lo, int hi) const;

    T& operator[](int r) const;
    Vector<T>& operator=(Vector<T> const&);

    T remove(int r);
    int remove(int lo, int hi);
    int insert(int r, T const& e);

    void sort(int lo, int hi, int ID);
    void unsort(int lo, int hi);
    void unsort();

    int deduplicate();
    int uniquify();

    void traverse(void (*visit)(T&));
    template <typename VST>
    void traverse(VST&);
};

template <typename T>
void Vector<T>::copyFrom(T const* A, int lo, int hi) {
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    while (lo < hi) {
        _elem[_size++] = A[lo++];
    }
}

template <typename T>
Vector<T>::Vector(int c, int s, T const& v) {
    _elem = new T[_capacity = c];
    for (_size = 0; _size < s; _elem[_size++] = v);
}

template <typename T>
Vector<T>::Vector(T const* A, int lo, int hi) {
    copyFrom(A, lo, hi);
}

template <typename T>
Vector<T>::Vector(T const* A, int n) {
    copyFrom(A, 0, n);
}

template <typename T>
Vector<T>::Vector(Vector<T> const& V, int lo, int hi) {
    copyFrom(V._elem, lo, hi);
}

template <typename T>
Vector<T>::Vector(Vector<T> const& V) {
    copyFrom(V._elem, 0, V._size);
}

template <typename T>
Vector<T>::~Vector() {
    delete[] _elem;
}

template <typename T>
void Vector<T>::push_Back(T const& value) {
    if (_size == _capacity) expand();
    _elem[_size++] = value;
}

template <typename T>
int Vector<T>::size() const {
    return _size;
}

template <typename T>
bool Vector<T>::empty() const {
    return!_size;
}

template <typename T>
int Vector<T>::disordered() const {
    int n = 0;
    for (int i = 1; i < _size; i++) {
        if (_elem[i - 1] > _elem[i]) n++;
    }
    return n;
}

template <typename T>
int Vector<T>::find(T const& e, int lo, int hi) const {
    while ((lo < hi--) && (e!= _elem[hi]));
    return hi;
}

template <typename T>
int Vector<T>::search(T const& e, int lo, int hi) const {
    return -1;
}

template <typename T>
T& Vector<T>::operator[](int r) const {
    if (r < 0 || r >= _size) throw std::out_of_range("Index out of range");
    return _elem[r];
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
    if (_elem) delete[] _elem;
    copyFrom(V._elem, 0, V._size);
    return *this;
}

template <typename T>
int Vector<T>::insert(int r, T const& e) {
    expand();
    for (int i = _size; i > r; i--) {
        _elem[i] = _elem[i - 1];
    }
    _elem[r] = e;
    _size++;
    return r;
}

template <typename T>
T Vector<T>::remove(int r) {
    T e = _elem[r];
    remove(r, r + 1);
    return e;
}

template <typename T>
int Vector<T>::remove(int lo, int hi) {
    if (lo == hi) return 0;
    while (hi < _size) {
        _elem[lo++] = _elem[hi++];
    }
    _size -= hi - lo;
    shrink();
    return hi - lo;
}

template <typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    int i = 1;
    while (i < _size) {
        if (find(_elem[i], 0, i) < 0) i++;
        else remove(i);
    }
    return oldSize - _size;
}

template <typename T>
int Vector<T>::uniquify() {
    int p1 = 0, p2 = p1;
    int oldSize = _size;
    while (p2 < _size - 1 && p1 <= p2) {
        p2++;
        if (_elem[p2]!= _elem[p1]) _elem[++p1] = _elem[p2];
    }
    remove(++p1, _size);
    shrink();
    return oldSize - _size;
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) {
    for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST& visit) {
    for (int i = 0; i < _size; i++) visit(_elem[i]);
}

template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return;
    if (_capacity < 3) _capacity = 3;
    T* oldElem = _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete[] oldElem;
}

template <typename T>
void Vector<T>::shrink() {
    if (_capacity < 6) return;
    if (_size << 2 > _capacity) return;
    T* oldElem = _elem;
    _elem = new T[_capacity >>= 1];
    for (int i = 0; i < _size; i++) _elem[i] = oldElem[i];
    delete[] oldElem;
}

template <typename T>
void Vector<T>::unsort(int lo, int hi) {
    T* V = _elem + lo;
    for (int i = lo; i < hi; i++) {
        int j = rand() % (hi - lo) + lo;
        std::swap(V[i], V[j]);
    }
}

template <typename T>
bool Vector<T>::bubble(int lo, int hi) {
    bool sorted = true;
    while (++lo < hi) {
        if (_elem[lo - 1] > _elem[lo]) {
            sorted = false;
            std::swap(_elem[lo - 1], _elem[lo]);
        }
    }
    return sorted;
}

template <typename T>
void Vector<T>::bubbleSort(int lo, int hi) {
    while (!bubble(lo, hi--));
}

template <typename T>
void Vector<T>::merge(int lo, int mi, int hi) {
    T* temp = new T[hi - lo];
    int i = lo, j = mi, k = 0;
    while (i < mi && j < hi) {
        if (_elem[i] < _elem[j]) temp[k++] = _elem[i++];
        else temp[k++] = _elem[j++];
    }
    while (i < mi) temp[k++] = _elem[i++];
    while (j < hi) temp[k++] = _elem[j++];
    for (int l = lo; l < hi; l++) _elem[l] = temp[l - lo];
    delete[] temp;
}

template <typename T>
void Vector<T>::mergeSort(int lo, int hi) {
    if (hi - lo < 2) return;
    int mi = (hi + lo) / 2;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}