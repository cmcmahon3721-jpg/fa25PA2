//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);


    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    MinHeap heap;
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);            //push indices into heap
    }

    while (heap.size > 1) {
        int index1 = heap.pop(weightArr);
        int index2 = heap.pop(weightArr);

        weightArr[nextFree] = weightArr[index1] + weightArr[index2];
        leftArr[nextFree] = index1;
        rightArr[nextFree] = index2;

        heap.push(nextFree, weightArr);
        nextFree++;
    }
    int root = heap.pop(weightArr);
    return root;
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    stack<pair<int, string>> stack;

    pair<int, string> x = pair<int, string>(root, "");
    stack.push(x);   //push root

    int tempIndex;
    string tempCode;

    while (!stack.empty()) {
        tempIndex = stack.top().first;
        tempCode = stack.top().second;
        stack.pop();

        if (leftArr[tempIndex] == -1 && rightArr[tempIndex] == -1) {    //if node is leaf then save code created
            codes[tempIndex] = tempCode;
        }
        else {
            if (rightArr[tempIndex] != -1) {   //if not leaf node continue adding to code
                pair<int, string> y = pair<int, string>(rightArr[tempIndex], tempCode + "1");
                stack.push(y);
            }
            if (leftArr[tempIndex] != -1) {
                pair<int, string> z = pair<int, string>(leftArr[tempIndex], tempCode + "0");
                stack.push(z);
            }
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << "   " << char('a' + i) << "      :  " << codes[i] << "\n";    //there is an issue with the given
    }                                                                        //code here. It will only output letters
                                                                                //in alphabetical order, representing
                                                                                //letters that are not in input.txt

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}