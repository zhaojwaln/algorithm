//
// Created by zhaojwaln on 2018/9/13.
//

#ifndef ARRAYHELPER_H
#define ARRAYHELPER_H

#include <iostream>

using namespace std;

namespace ArrayHelper {

    int *generateRandomArray(int n, int rangeL, int rangeR) {
        assert(n > 0);
        assert(rangeL <= rangeR);

        int *arr = new int[n];
        srand(time(NULL));
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        }
        return arr;
    }

    int *generateNearlyOrderedArray(int n, int swapTimes) {
        int *arr = new int[n];
        for (int i=0; i<n; i++) {
            arr[i] = i;
        }
        srand(time(NULL));
        for (int i=0; i<swapTimes; i++) {
            int posx = rand() % n;
            int posy = rand() % n;
            swap(arr[posx], arr[posy]);
        }
        return arr;
    }

    template <typename T>
    void printArray(T arr[], int n) {
        for (int i = 0; i < n; i ++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        return;
    }

    int *copyIntArray(int a[], int n) {
        int *arr = new int[n];
        copy(a, a+n, arr);
        return arr;
    }
}

#endif //ARRAYHELPER_H
