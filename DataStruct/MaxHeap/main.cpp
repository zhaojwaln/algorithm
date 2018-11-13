//
// Created by zhaojwaln on 2018/11/12.
//

/*
 * 最大堆
 * 概念：1.完全二叉树 2.二叉树中每个节点的值不大于其父节点的值
 * 实现：使用数组存储最大堆
 *                  33(1)
 *               /        \
 *         22(2)             31(3)
 *       /       \        /         \
 *    12(4)      18(5)  24(6)     29(7)
 *    /   \      /
 *  6(8) 10(9) 14(10)
 *  根节点的索引为1
 *  每个节点(i)的左孩子的索引值2*i,有节点的索引值为2*i+1
 *  每个节点(i)的父节点的索引值为i/2
 *
 *  插入过程：数组末尾增加元素，与它的父节点进行判断，如果>父节点，交换与父节点的位置，直到root节点为止
 *  删除过程：删除root节点并将数组中最后一个节点放在root位置，再与其左右节点中较大的节点进行交换（保证根节点比它左右节点都大），直到没有其子节点可以交换为止
 *  优化：对比插入排序算法，减少使用swap操作，用赋值替换swap
 * */

#include <iostream>
#include "../../ArrayHelper/ArrayHelper.h"

using namespace std;

template <typename Item>
class MaxHeap {
private:
    Item *data;
    int count;
    int capacity;

    void shiftUp(int k) {
        while( k > 1 && data[k/2] < data[k]) {
            swap(data[k/2], data[k]);
            k /= 2;
        }
    }

    void shiftDown(int k) {
       while(2*k <= count) {
           int j = 2*k;
           if (j + 1 <= count && data[j+1] > data[j]) {
               j += 1;
           }
           if (data[k] >= data[j]) {
               break;
           }
           swap(data[k], data[j]);
           k = j;
       }
    }
public:
    MaxHeap(int capacity) {
        data = new Item[capacity + 1];
        count = 0;
        this->capacity = capacity;
    }

    ~MaxHeap() {
        delete []data;
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    void insert(Item item) {
        assert(count + 1 <= capacity);
        data[count + 1] = item;
        count ++;
        shiftUp(count);
    }

    Item extractItem() {
        assert(count > 0);
        Item ret = data[1];
        swap(data[1], data[count]);
        count --;
        shiftDown(1);
        return ret;
    }

    void printData() {
        for (int i = 1; i <= count; i ++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main(void) {
    MaxHeap<int> maxHeap = MaxHeap<int>(100);
    int n = 10;
    int *arr = ArrayHelper::generateRandomArray(n, 0, n);
    for (int i = 0; i < n; i ++) {
        maxHeap.insert(arr[i]);
    }
    maxHeap.printData();
    maxHeap.extractItem();
    maxHeap.printData();
    delete []arr;
    return 0;
}