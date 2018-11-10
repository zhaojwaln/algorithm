#include <iostream>
#include "SortTestHelper.h"

using namespace std;

template <typename T>
void selectionSort(T arr[], int n) {
    for (int i=0; i<n; i++) {
        // 选择[i, n)区间内的最小值
        int minIndex = i; // 假定最小的是第一个，找后面比它还小的
        for (int j=i+1; j<n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // 找到最小的后与i进行交换
        swap(arr[i], arr[minIndex]);
    }
}

template <typename T>
void insertionSort(T arr[], int n) {
    for (int i=1; i<n; i++) {
        for (int j=i; j>0 && arr[j]<arr[j-1]; j--) {
            swap(arr[j], arr[j-1]);
        }
    }
}

/*
 * 同样是O(n^2) selectionSort 比 insertionSort 要快一点
 * 这是因为在插入排序时，每一个元素都可能与它前面的每一个元素进行交换
 * 交换过程中就会消耗一定的时间，而排序算法找到最小的一个才会交换
 *
 * 优化：newInsertionSort
 * */

template <typename T>
void newInsertionSort(T arr[], int n) {
    for (int i=1; i<n; i++) {
        T e = arr[i];
        int j;
        for (j=i; j>0 && e < arr[j-1]; j--) {
            arr[j] = arr[j-1];
        }
        arr[j] = e;
    }
}

template <typename T>
// 将arr[l, mid]和arr[mid+1, r]进行合并
void __merge(T arr[], int l, int mid, int r) {
   T aux[r - l + 1];
   for (int i=l; i<=r; i++) {
       aux[i - l] = arr[i];
   }
   int i = l, j = mid + 1;
   for (int k=l; k<=r; k++) {
       if (j > r) {
           arr[k] = aux[i - l];
           i++;
       } else if (i > mid) {
           arr[k] = aux[j - l];
           j++;
       } else if (aux[i - l] > aux[j - l]) {
           arr[k] = aux[j - l];
           j++;
       } else {
           arr[k] = aux[i - l];
           i++;
       }
   }
}

template <typename T>
// 递归进行归并排序，对arr[l, r]的范围进行排序
void __mergeSort(T arr[], int l, int r) {
    // 结束条件 区间没有值
    if (l >= r) {
        return;
    }

    int mid = (l + r) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    if (arr[mid] > arr[mid + 1])
        __merge(arr, l, mid, r);
}

// 自顶向下
template <typename T>
void mergeSort(T arr[], int n) {
    __mergeSort(arr, 0, n-1);
}

// 自底向上
template <typename T>
void mergeSortBU(T arr[], int n) {
    for (int sz = 1; sz <= n; sz += sz) {
        for (int i = 0; i + sz < n; i += sz + sz) {
            __merge(arr, i, i + sz - 1, min(i + sz + sz -1, n - 1));
        }
    }
}

int main() {
    int n = 500000;
//    int *arr = SortTestHelper::generateRandomArray(n, 0, 10000);
    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 0);
    int *arr2 = SortTestHelper::copyIntArray(arr, n);
    int *arr3 = SortTestHelper::copyIntArray(arr, n);
    int *arr4 = SortTestHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("New Insertion Sort", newInsertionSort, arr3, n);
    SortTestHelper::testSort("Merge Sort", mergeSortBU, arr4, n);

    delete []arr;
    delete []arr2;
    delete []arr3;
    delete []arr4;
    return 0;
}