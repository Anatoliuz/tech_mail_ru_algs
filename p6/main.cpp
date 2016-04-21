/* Задача 6_1
 
 Дано N кубиков. Требуется определить каким количеством способов можно выстроить
 из этих кубиков пирамиду.
 В​ысокая пирамида. К​аждый вышележащий слой пирамиды должен быть не больше нижележащего. N ≤​ 200 .

 */

/*
 Решение. Будем использовать восходящий подход динамического программирования.
 Структурой данных будет матрица лонгов.
 Ряды матрицы - высоты пирамид, столбцы - число кубиков.
 Матрица будет верхней треугольной матрицей, т.к. невозможно из column < row кубиков составить пирамиду.
 Соответственно в каждой ячейке  row и column будет находится
 число различных пирамид из column кубиков высоты row,а сумма каждого столбца - числом
 всевозможны пирамид из N кубиков.
 Для простоты восприятия матрица будет иметь размер n+1, а начинать отсчет будем
 из ячейки [1][1].
 Первый ряд заполним единицами т.к. из n кубиков можно составить лишь только одну пирамиду
 высоты 1. То же самое проделаем с диаганалью.
 Следующие ячейки заполняются в 2 шага:
 1. Для высоты row нам понадобится как минимум количество кубиков, равное этой высоте.
 Соотвественно прибавляем значение из matrix[row][row] к значению ячейки.
 2. Оставшиеся кубики (column - row) штук можно расположить числом способов равным
 сумме значений в столбце column - row от второй строчки до высоты равной row.
 Первую строчку не рассматриваем, значения из этого ряда учитываются в шаге 1.
 
 В конце суммируем значения интересующего нас столбца.
 */
#include <iostream>
using namespace std;

void find_pyramids_num(int number_of_blocks){
    
    long** matrix = new long*[number_of_blocks+1]();
    for (int i = 0; i <= number_of_blocks; ++i) {
        matrix[i] = new long[number_of_blocks+1];
    }
    
    for (int i = 1; i <= number_of_blocks; ++i) {
        matrix[1][i] = 1;//1 ряд единиц
    }
    for (int row = 2; row <= number_of_blocks; ++row) {
        for (int column = 1;  column <= number_of_blocks; ++column) {
            if (row == column)
                matrix[row][column] = 1;
        }
    }
    for (int column = 3; column <= number_of_blocks; ++column) {
        for (int row = 2;  row < column ; ++row) {
            matrix[row][column] += matrix[row][row];//минимум row кубиков для создания
                                                    //пирамиды высоты row

            for(int k = 2; k <= row ;++k){
                matrix[row][column] += matrix[k][column - row ]; //прибавляем сумму числа комбинаций
                                                                 //оставшихся кубиков
            }
        }
    }
    long ans = 0;

    for (int i = 1; i <= number_of_blocks  ; ++i) {
        ans += matrix[i][number_of_blocks];
    }
    cout << ans;
    for(int i = 0; i < number_of_blocks; ++i) {
        delete [] matrix[i];
    }
    delete[] matrix;
}

int main(){
    int number_of_blocks = 0;
    cin >> number_of_blocks;
    find_pyramids_num(number_of_blocks);
    return 0;
}