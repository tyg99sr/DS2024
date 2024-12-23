#include <iostream>
#include "../utilities/vector/Vector.hpp"
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

// ��������
void bubbleSort(Vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// ��������
void insertionSort(Vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// ѡ������
void selectionSort(Vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }
        swap(arr[i], arr[minIdx]);
    }
}

// �鲢����
void merge(Vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    Vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(Vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// ��������
int partition(Vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) swap(arr[++i], arr[j]);
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(Vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ������
void heapify(Vector<int>& arr, int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(Vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ���ܲ���
void testSort(void (*sortFunc)(Vector<int>&), Vector<int>& arr, const string& name) {
    Vector<int> temp = arr;
    auto start = high_resolution_clock::now();
    sortFunc(temp);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << name << ": " << duration.count()  << " ΢��" << endl;
}

int main() {
    const int n = 10000; // ���������С
    Vector<int> ascending(n), descending(n), random(n);

    // ��ʼ����������
    for (int i = 0; i < n; ++i) {
        ascending.push_Back(i);
        descending.push_Back(n-i);
        random.push_Back(rand() % n); 
    }

    // ������Խ��
    cout << "˳�������ϵ����ܲ���:" << endl;
    testSort(bubbleSort, ascending, "��������");
    testSort(insertionSort, ascending, "��������");
    testSort(selectionSort, ascending, "ѡ������");
    testSort([](Vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, ascending, "�鲢����");
    testSort([](Vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, ascending, "��������");
    testSort(heapSort, ascending, "������");

    cout << "\n���������ϵ����ܲ���:" << endl;
    testSort(bubbleSort, descending, "��������");
    testSort(insertionSort, descending, "��������");
    testSort(selectionSort, descending, "ѡ������");
    testSort([](Vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, descending, "�鲢����");
    testSort([](Vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, descending, "��������");
    testSort(heapSort, descending, "������");

    cout << "\n��������ϵ����ܲ���:" << endl;
    testSort(bubbleSort, random, "��������");
    testSort(insertionSort, random, "��������");
    testSort(selectionSort, random, "ѡ������");
    testSort([](Vector<int>& arr) { mergeSort(arr, 0, arr.size() - 1); }, random, "�鲢����");
    testSort([](Vector<int>& arr) { quickSort(arr, 0, arr.size() - 1); }, random, "��������");
    testSort(heapSort, random, "������");

    system("pause");
    

    return 0;
}
