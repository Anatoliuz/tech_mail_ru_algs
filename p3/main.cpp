//
//  main.cpp
//  workingproject
//
//  Created by fix on 07/03/16.
//  Copyright (c) 2016 Anatoly Filinov. All rights reserved.
//

#include <iostream>
#include <math.h>

int BinSearch(int* array, int searchingElement, int left, int right){
    
    if(left > right){
        return left;
    }
    int mid = (left+right)/2;
    
    if (array[mid] == searchingElement) {
        return mid;
    }
    if (array[mid] > searchingElement) {
        return BinSearch(array, searchingElement, left, mid - 1);
    }
    if (array[mid] < searchingElement) {
        return BinSearch(array, searchingElement, mid + 1, right);
    }
    return -1;
}
void FindIndexes(){
    int sizeOfA = 0;
    std::cin >> sizeOfA;
    int sizeOfB = 0;
    std::cin >> sizeOfB;
    int A[sizeOfA];
    int B[sizeOfB];
    
    for (int pos = 0; pos < sizeOfA; ++pos) {
        std::cin >> A[pos];
    }
    for (int pos = 0; pos < sizeOfB; ++pos) {
        std::cin >> B[pos];
    }
    int powOfTwoIndex = 1;
    for (int posB = 0; posB < sizeOfB; ++posB) {
        if (B[posB] == A[0]) {
            std::cout << 0;
            continue;
        }
        for(int posA = 1; posA < sizeOfA; ) {
            if (A[sizeOfA - 1] < B[posB] ) {
                std::cout<< sizeOfA - 1 ;
                posA = sizeOfA + 1;
                continue;
            }
            if (B[posB] == A[posA]) {
                std::cout<< posA;
                posA = sizeOfA + 1;
                continue;
            }
            else if (A[posA] > B[posB]) {
                if (pow(2, powOfTwoIndex - 1) == 1) {
                    int k = BinSearch(A, B[posB], 0, 1);
                    std::cout << k;
                    posA = sizeOfA + 1;
                }
                else{
                    int k = BinSearch(A, B[posB], 0, posA);
                    std::cout << k;
                    posA = sizeOfA + 1;
                }
                
            }
            else {
                posA = pow(2, ++powOfTwoIndex);
                if (posA > sizeOfA - 1) {
                    posA = sizeOfA - 1;
                }
            }
        }
    }
}

int main(int argc, const char * argv[])
{
    FindIndexes();
       return 0;
}

