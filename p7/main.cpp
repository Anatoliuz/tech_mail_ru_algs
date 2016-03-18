#include <iostream>
#include <algorithm>
#include <vector>
/*
 Задача 7_2
 7_2. Заявки на переговоры.
 В большой IT­фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
 Число заявок ≤​100000.
 
 Решение
    Запомним std::array данными начала и конца, затем используя стандартную функцию сортировки отсортируем
    наши структуры массиве в монотонном порядке возрастания по дате окончания.
    Затем используем функцию GreedySelect, которая возвращает максимальное количество удовлетворенных
    заявок.
 
*/



struct meetingData{
    int start;
    int finish;
    meetingData(): start(0), finish(0){}
};

void Add(int start, int finish, meetingData& meeting){
    meeting.start = start;
    meeting.finish = finish;
}
int input(meetingData &data){
    int start  = 0;
    int finish = 0;
    std::cin >> start;
    std::cin >> finish;
    if ( finish > 0 && start >= 0 && start  < finish) {
        Add(start, finish, data);
        return 0;
    }
    else
    {
        return -1;
    }
}

template <typename T>
void FillArray(std::vector<T> &array){
    meetingData meeting;
    while (  input(meeting) >= 0 ) {
        array.push_back(meeting);
        }
    
}

template <typename T>
void Sort(std::vector<T> &array){
    std::sort(array.begin(), array.end(), [](const meetingData &lhs, const meetingData &rhs) { return lhs.finish < rhs.finish; });
}


int GreedySelect(std::vector<int> &starting_vector, std::vector<int>finish_vector){
    int length = starting_vector.size();
    int numOfAsks = 0;
    ++numOfAsks; //первый процесс мы можем удовлетворить всегда
    int latestAddedIndex = 0; //индекс последнего добавления в множество подходящих процессов
    for(int i = 1; i < length; ++i){
        if (starting_vector[i] >= finish_vector[latestAddedIndex]) {
            ++numOfAsks;//можем удовлетворить ещё один запрос
            latestAddedIndex = i;
        }
    }
    return numOfAsks;
}

void ShowAnswer(){
    int numOfAsks = 0;
    std::vector<meetingData> array;
    FillArray(array);
    Sort(array);
    std::vector<int> starting_vector;
    std::vector<int> finish_vector;
    for(int i = 0; i < array.size(); ++i)
    {
        starting_vector.push_back(array[i].start);
        finish_vector.push_back(array[i].finish);
    }
    numOfAsks = GreedySelect(starting_vector, finish_vector);
    std::cout << numOfAsks;
}
int main()
{
    ShowAnswer();
    return 0;
}