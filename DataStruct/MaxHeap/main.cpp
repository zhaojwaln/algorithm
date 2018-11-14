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
#include "Heap.h"

using namespace std;

int main(void) {
    MaxHeap<int> maxHeap = MaxHeap<int>(100);
    int n = 10;
    int *arr = ArrayHelper::generateRandomArray(n, 0, n);
    for (int i = 0; i < n; i ++) {
        maxHeap.insert(arr[i]);
    }
    maxHeap.printData();
    while (!maxHeap.isEmpty()) {
        cout << maxHeap.extractItem() << " ";
    }
    cout << endl;
    delete []arr;
    return 0;
}