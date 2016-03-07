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
        return -1;
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


int main(int argc, const char * argv[])
{
    int B[4] = { 6, 9, 10, 12 };
    int A[4] = { 8, 7, 9, 10 };
 //   int i = BinSearch(temp, 2, 0, 5);
    int sizeOfA = 4;
    int sizeOfB = 4;
//    //scanf("%d", &sizeOfA);
//   // scanf("%d", &sizeOfB);
//    int A[sizeOfA];
//    int B[sizeOfB];
//    
//    for (int pos = 0; pos < sizeOfA; ++pos) {
//        scanf("%d", &A[pos]);
//        printf("%d", A[pos]);
//    }
//    
//    for (int pos = 0; pos < sizeOfB; ++pos) {
//        scanf("%d", &B[pos]);
//        printf("%d", B[pos]);
//    }
    int powOfTwoIndex = 1;
    for (int posB = 0; posB < sizeOfB; ++posB) {
        if (B[posB] == A[0]) {
            std::cout << 0 << " ";
            continue;
        }

        for(int posA = 1; posA < sizeOfA; ) {
            if (B[posB] == A[posA]) {
                std::cout << posA << " ";
                posA = sizeOfA + 1;
            }
           else if (A[posA] > B[posB]) {
                if (posA > sizeOfA) {
                    return -1;
                }
               int k = BinSearch(A, B[posB], pow(2, powOfTwoIndex - 1), posA);
               if (k >= 0) {
                   std::cout <<"k" << k << " ";
               }
               if (k < 0){
                 std::cout <<"SolveIt" << posA << " ";
               }
               posA = sizeOfA + 1;

            }
            else posA = pow(2, ++powOfTwoIndex);
            if (A[sizeOfA - 1] < B[posB] ) {
                std::cout<< sizeOfA - 1 << " " ;
                posA = sizeOfA + 1;
            }
        }
        powOfTwoIndex = 1;
    }
  
    return 0;
}

