#include <iostream>
#include "SortTestHelper.h"
#include "../ArrayHelper/ArrayHelper.h"

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

template <typename T>
int __partition(T arr[], int l, int r) {
    // 选择随机的一个值作为基准
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T e = arr[l];
    int j = l + 1;
    for (int i = l + 1; i <= r; i ++) {
        if (arr[i] < e) {
            swap(arr[j], arr[i]);
            j ++;
        }
    }
    swap(arr[j - 1], arr[l]);
    return j - 1;
}

template <typename T>
void __quickSort(T arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    // 找到基准所在的位置
    int p = __partition(arr, l, r);
    // 对[l, p]进行快速排序
    __quickSort(arr, l, p);
    // 对[p + 1, r]进行快速排序
    __quickSort(arr, p + 1, r);

}

template <typename T>
void quickSort(T arr[], int n){
    srand(time(NULL));
    __quickSort(arr, 0, n-1);
}

template <typename T>
int __partition2(T arr[], int l, int r) {
    // 选择随机的一个值作为基准
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T e = arr[l];
    int i = l + 1, j = r;
    while( true ) {
        // 找到从左到右第一个比e大的值的位置
        while( i <= r && arr[i] < e ) i++;
        // 找到从右到左第一个比e小的值的位置
        while( j >= l + 1 && arr[j] > e ) j--;
        if ( i > j ) break;
        swap(arr[i], arr[j]);
        i ++;
        j --;
    }
    swap(arr[l], arr[j]);
    return j;
}

template <typename T>
void __quickSort2(T arr[], int l, int r) {
    if (l >= r) {
        return;
    }
    // 找到基准所在的位置
    int p = __partition2(arr, l, r);
    // 对[l, p]进行快速排序
    __quickSort2(arr, l, p - 1);
    // 对[p + 1, r]进行快速排序
    __quickSort2(arr, p + 1, r);

}

template <typename T>
// 双路快排
void quickSort2(T arr[], int n){
    srand(time(NULL));
    __quickSort2(arr, 0, n-1);
}


template <typename T>
void __quickSort3(T arr[], int l, int r) {
    if (l >= r) {
        return;
    }

    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T e = arr[l];

    int lt = l; //[l + 1, lt] < e
    int gt = r + 1; // [gt, r] > e
    int i = l + 1; // [lt + 1, i) == e
    while (i < gt) {
       if (arr[i] < e) {
           swap(arr[i], arr[lt + 1]);
           lt ++;
           i++;
       } else if (arr[i] > e) {
           swap(arr[i], arr[gt - 1]);
           gt --;
       } else {
           i ++;
       }
    }
    swap(arr[l], arr[lt]);

    __quickSort3(arr, l, lt - 1);
    __quickSort3(arr, gt, r);
}

template <typename T>
// 三路快排
void quickSort3(T arr[], int n){
    srand(time(NULL));
    __quickSort3(arr, 0, n-1);
}

int main() {
    int n = 10000;
    int *arr = ArrayHelper::generateRandomArray(n, 0, n);
//    int *arr = SortTestHelper::generateNearlyOrderedArray(n, 0);
    int *arr2 = ArrayHelper::copyIntArray(arr, n);
    int *arr3 = ArrayHelper::copyIntArray(arr, n);
    int *arr4 = ArrayHelper::copyIntArray(arr, n);
    int *arr5 = ArrayHelper::copyIntArray(arr, n);
    int *arr6 = ArrayHelper::copyIntArray(arr, n);
    int *arr7 = ArrayHelper::copyIntArray(arr, n);

    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    SortTestHelper::testSort("Insertion Sort", insertionSort, arr2, n);
    SortTestHelper::testSort("New Insertion Sort", newInsertionSort, arr3, n);
    SortTestHelper::testSort("Merge Sort", mergeSortBU, arr4, n);
    SortTestHelper::testSort("Quick Sort", quickSort, arr5, n);
    SortTestHelper::testSort("Quick2 Sort", quickSort2, arr6, n);
    SortTestHelper::testSort("Quick3 Sort", quickSort3, arr7, n);

    delete []arr;
    delete []arr2;
    delete []arr3;
    delete []arr4;
    delete []arr5;
    delete []arr6;
    delete []arr7;
    return 0;
}