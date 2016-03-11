//
//  main.cpp
//  workingproject
//
//  Created by fix on 07/03/16.
//  Copyright (c) 2016 Anatoly Filinov. All rights reserved.
//
// Задача 3.1
/* Дан отсортированный массив целых чисел A[0..n­1] и массив целых чисел B[0..m­1]. Для каждого
 элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или
 превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. Время работы поиска k для каждого
 элемента B[i]: O(log(k)).
 
 n, m ≤ 10000.
 */

//Решение
/*
	Функция Output()  считывает данные пользователя и в цикле для каждого
	элемента из В вызывает функцию LogSearch, которая за логарифмическое время 
	возвращает индекс элемента из массива А, большего либо равного данному элементу.
*/

#include <iostream>
#include <math.h>

int BinSearch(int* array, int searchingElement, int left, int right){
    
    if(left > right){
        return left; //возвращаем ближайший больший элемент
    }
    int mid = (left+right)/2;
    
    if (array[mid] == searchingElement) {
        return mid;
    }
    if (array[mid] > searchingElement) {
        return BinSearch(array, searchingElement, left, mid - 1);
    }
    else  {
        return BinSearch(array, searchingElement, mid + 1, right);
    }
}

int LogSearch(int* Array, int sizeOfA, int findNum){
    int powOfTwoIndex = 1; 
    if (findNum == Array[0]) {
        return 0;
    }
    if (Array[sizeOfA - 1] < findNum ) {
        return sizeOfA;
    }
    for(int posA = 1; posA < sizeOfA; ) {
        if (findNum == Array[posA]) {
            return posA;
        }
        else if (Array[posA] > findNum) {
            if (pow(2, powOfTwoIndex - 1) == 1) { //если posA = 0
                return BinSearch(Array, findNum, 0, 1);//ищем в массиве А в интервале
                									// от 0 до 1 
            }
            else{ //иначе в интервале от 2^k-1 до 2^k
                return BinSearch(Array, findNum, pow(2, powOfTwoIndex - 1), posA);
            }     
        }
        else {
            posA = pow(2, ++powOfTwoIndex);//увеличиваем верхнюю границу поиска
            if (posA > sizeOfA - 1) {
                posA = sizeOfA - 1; //проверка на не выход за границу массива
            }
        }
    }
    return -1; //ошибка
}


void Output(){
    int sizeOfA = 0;
    int sizeOfB = 0;
    std::cin >> sizeOfA >> sizeOfB;
    int* A = new int[sizeOfA];
    int* B = new int[sizeOfB];
    for (int pos = 0; pos < sizeOfA; ++pos) {
        std::cin >> A[pos];
    }
    for (int pos = 0; pos < sizeOfB; ++pos) {
        std::cin >> B[pos];
    }
    for (int posB = 0; posB < sizeOfB; ++posB)
    {
        std::cout << LogSearch(A, sizeOfA, B[posB]) <<" ";
    }
    delete[] A;
    delete[] B;
}
int main(int argc, const char * argv[])
{
    Output();
    return 0;
}

