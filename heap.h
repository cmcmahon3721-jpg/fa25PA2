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
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = data[idx];
        size++;
        upheap(size - 1, weightArr);
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        int smallest = data[0];
        data[0] = data[size - 1];
        size--;
        downheap(0, weightArr);
        return smallest; // placeholderr
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        int temp = 0;
        int parent = (pos - 1) / 2;
        while (pos > 0 && weightArr[data[pos]] < weightArr[data[parent]]) {
            parent = (pos - 1) / 2;
            temp = data[pos];
            data[pos] = data[parent];
            data[parent] = temp;
            pos = parent;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        int leftChild =  2 * pos + 1;
        int rightChild = 2 * pos + 2;
        int smallest = pos;
        int temp = 0;

        while (true) {
            if (leftChild < size && weightArr[data[leftChild]] < weightArr[data[smallest]]) {
                smallest = leftChild;
            }
            if (rightChild < size && weightArr[data[rightChild]] < weightArr[data[smallest]]) {
                smallest = rightChild;
            }
            if (smallest != pos) {
                temp = data[pos];
                data[pos] = data[smallest];
                data[smallest] = temp;
                pos = smallest;
            }
            else {
                return;
            }
            leftChild = 2 * pos + 1;
            rightChild = 2 * pos + 2;
        }
    }
};


#endif