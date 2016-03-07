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
 i, j обозначим pos
 n -> sizeOfA
 m -> sizeOfB
 powOfTwoIndex - текущая степень двойки, чтобы вызывать бинарный поиск более эффективно.
 
 Для каждого элемента B[posB] будем проверять выполнимость некоторых условий
 относительно элементов из А.
 В зависимости от условия, выполняем определенные шаги.
 Также имеется немного модифицированный бинарный поиск, который
 в случае не нахождения элемента A[index] == B[jndex] в заданном интервале, воз-
 вращает индекс ближайшего большего элемента.
 Условия и шаги:
 1) Если B[posB] == A[0] мы нашли индекс для i-го B, выведем 0 в поток.
 Приступаем к работе со следующим элементом из В.
 2) Если B[posB] > A[sizeOfA - 1] выведем в поток sizeOfA, приступаем к следующему
 элементу из В.
 Далее posA будет степенью двойки
 3) Если элементы равны, выводим posA, приступаем к следующему элементу из B.
 4) Если A[posA] > B[posB]
     4.1. Если двойка в степени powOfTwoIndex == 1, мы смотрим нулевой элемент из А(т.е.
      делаем первый проход по второму вложенному циклу), вызываем бинарный поиск в интервале
      от 0 до 2^0 = 1; бинарный поиск находит индекс элемента из А либо равного элементу из
      B, либо ближайшего большего числа.
      Выводим индекс, который вернет бинарный поиск, приступаем к следующему элементу из B.
     4.2. Если проход по второму циклу не первый,мы вызываем бинарный поиск в интервале от 2^x-1 до 2^x
      Тем самым удовлетворяя сложности О(logk) 
      Выводим индекс, который вернет бинарный поиск, приступаем к следующему элементу из B.
     4.3. Если мы не нашли элемент в интервале 2^x до 2^x-1, смещаем отрезок поиска, но если двойка
       в новой степени больше sizeOfA - 1 интервал будет иметь вид от 2^x(i)-1 до sizeOfA - 1

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

void FindIndexes(){
    int sizeOfA = 0;
    int sizeOfB = 0;
    std::cin >> sizeOfA >> sizeOfB;
    std::cout << std::endl;
    int A[sizeOfA];
    int B[sizeOfB];
    
    for (int pos = 0; pos < sizeOfA; ++pos) {
        std::cin >> A[pos];
    }
    std::cout << std::endl;
    
    for (int pos = 0; pos < sizeOfB; ++pos) {
        std::cin >> B[pos];
    }
    int powOfTwoIndex = 1;
    for (int posB = 0; posB < sizeOfB; ++posB) {
        //1 шаг
        if (B[posB] == A[0]) {
            std::cout << 0 << " ";   
            continue;
        }
        // 2 шаг
        if (A[sizeOfA - 1] < B[posB] ) {
            std::cout<< sizeOfA << " " ; 
            continue;
        }
        powOfTwoIndex = 1;
        for(int posA = 1; posA < sizeOfA; ) {
             //3 шаг
            if (B[posB] == A[posA]) {    
                std::cout<< posA << " ";
                posA = sizeOfA + 1;
                continue;
            }
            //4 шаг
            else if (A[posA] > B[posB]) { 
                //4.1 шаг
                if (pow(2, powOfTwoIndex - 1) == 1) {
                    int k = BinSearch(A, B[posB], 0, 1);
                    std::cout << k << " ";
                    posA = sizeOfA + 1;
                }
                //4.2 шаг
                else{
                    int k = BinSearch(A, B[posB], pow(2, powOfTwoIndex - 1), posA);
                    std::cout << k << " ";
                    posA = sizeOfA + 1;
                }
                
            }
            //4.3 шаг
            else {
                posA = pow(2, ++powOfTwoIndex);
                if (posA > sizeOfA - 1) {
                    posA = sizeOfA - 1; //проверка на не выход за границу массива
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

