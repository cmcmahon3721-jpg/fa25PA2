//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        data[size] = idx;                   //pushing indices into data[] to use for upheap/downheap
        size++;                             //account for change in size
        upheap(size - 1, weightArr);
    }

    int pop(int weightArr[]) {
        int smallest = data[0];             //to return smallest index
        data[0] = data[size - 1];
        size--;                             //account for change in size
        downheap(0, weightArr);
        return smallest;
    }

    void upheap(int pos, int weightArr[]) {
        int temp = 0;
        int parent = (pos - 1) / 2;
        while (pos > 0 && weightArr[data[pos]] < weightArr[data[parent]]) { //if node is smaller than parent
            parent = (pos - 1) / 2;
            temp = data[pos];
            data[pos] = data[parent];
            data[parent] = temp;
            pos = parent;
        }
    }

    void downheap(int pos, int weightArr[]) {
        int leftChild =  2 * pos + 1;  //index of left child
        int rightChild = 2 * pos + 2;  //index of right child
        int smallest = pos;
        int temp = 0;
        bool isPercolating = true;

        while (isPercolating) {
            if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[smallest]]) {    //if left or right child nodes are smaller than current smallest node
                smallest = leftChild;
                temp = data[pos];               //swap left child with parent
                data[pos] = data[smallest];
                data[smallest] = temp;
                pos = smallest;
            }
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[smallest]]) {
                smallest = rightChild;          //swap right child with parent
                temp = data[pos];
                data[pos] = data[smallest];
                data[smallest] = temp;
                pos = smallest;
            }
            else {
                isPercolating = false;  //if neither right or left children nodes are smaller than parent, exit loop.
            }
            leftChild = 2 * pos + 1;
            rightChild = 2 * pos + 2;
        }
    }
};


#endif