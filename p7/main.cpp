#include <iostream>

/*
 Задача 7_2
 7_2. Заявки на переговоры.
 В большой IT­фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
 Число заявок ≤​100000.
 
 Решение
 Заполним собственный массив структурами, содержащими данные начала и конца.
 Затем отсортируем массив  в монотонном порядке возрастания по дате окончания,
 используя сортировку кучей за O(nlogn).
 Делаем первый шаг: первый процесс должен завершаться
 как можно раньше, чтобы оставить процессами, выполняющимся после него как можно больше времени.
 Выбрав процесс х1, теперь рассматриваем процессы начинающиеся
 не раньше его окончания. Далее алгоритм повторяется.
 
 Функция OptimalSolution, приняв массивы начала и окончания времения заявок(извлеченные из отсортированного массива), возвращает максимальное количество удовлетворенных заявок.
 
 */



struct meetingData{
    int start;
    int finish;
    meetingData(): start(0), finish(0){}
};

void fill_meetingData(int start, int finish, meetingData& meeting){
    meeting.start = start;
    meeting.finish = finish;
}
//Функция заполнения структуры. Проверка abs(finish-start)>0
int input(meetingData &data){
    int start  = 0;
    int finish = 0;
    std::cin >> start;
    std::cin >> finish;
    if ( finish > 0 && start >= 0 && start  < finish) {
        fill_meetingData(start, finish, data);
        return 0;
    }
    else
    {
        return -1;
    }
}

template <typename T>
struct dynamic_array{
    T *buffer;
    size_t size;
    size_t capacity;
    
    dynamic_array(): buffer(NULL), size(0), capacity(0){}
};


template <typename T>
void dynamic_array_init(dynamic_array<T> &array){
    array.buffer = NULL;
    array.size   = 0;
    array.capacity = 0;
}
size_t max(size_t a, size_t b){
    return a > b ? a : b;
}

template <typename T>
void dynamic_array_resize(dynamic_array<T> &array, size_t new_capacity)
{
    T *temp = new T[new_capacity];
    for (int i = 0; i < array.size && i < new_capacity;  ++i) {
        std::swap(temp[i], array.buffer[i]);
    }
    std::swap(array.buffer, temp);
    delete []temp;
    
    array.capacity = new_capacity;
    if (new_capacity  < array.size) {
        array.size = new_capacity;
    }
}
template <typename T>
void dynamic_array_push_back(dynamic_array<T> &array, T value)
{
    if (array.size == array.capacity) {
        dynamic_array_resize(array, max(1, array.capacity*2) );
    }
    array.buffer[array.size] = value;
    ++array.size;
}
template <typename T>
void dynamic_array_clear(dynamic_array<T> &array){
    delete[] array.buffer;
    array.buffer = NULL;
    array.capacity = 0;
    array.size = 0;
    
}

template <typename T>
void fill_array(dynamic_array<T> &array)
{
    meetingData meeting;
    while (  input(meeting) >= 0 ) {
        dynamic_array_push_back(array, meeting);
    }
}

int OptimalSolution(dynamic_array<int> &starting_vector, dynamic_array<int> &finish_vector){
    int length = starting_vector.size;
    int numOfAsks = 0;
    ++numOfAsks; //первый процесс мы можем удовлетворить всегда
    int latestAddedIndex = 0; //индекс последнего добавления в множество подходящих процессов
    for(int i = 1; i < length; ++i){
        if (starting_vector.buffer[i] >= finish_vector.buffer[latestAddedIndex]) {
            ++numOfAsks;//можем удовлетворить ещё один запрос
            latestAddedIndex = i;
        }
    }
    return numOfAsks;
}

void heapsort(dynamic_array<meetingData> &array)
{
    if(array.size == 0) // check if heap is empty
        return;
    
    meetingData temp;
    unsigned int n = array.size, parent = array.size/2, index, child; /* индексы кучи */
   
    while (1) {
        if (parent > 0) {
            temp = array.buffer[--parent];
        } else {
            n--;                /* уменьшаем размер кучи */
            if (n == 0) {
                return; /* если куча пуста, сортировка завершена  */
            }
            temp = array.buffer[n];
            array.buffer[n] = array.buffer[0];    /* сохраняем значение корня
                                                   за пределами кучи       */
        }
        /*  pushing temp down the heap to replace the parent
            опускаем временный элемент вниз кучи, заменяем parent
         */
        index = parent;
        child = index * 2 + 1; /* значение индекса левого ребенка */
        while (child < n) {
            /* выбираем большего ребенка */
            if (child + 1 < n  &&  array.buffer[child + 1].finish > array.buffer[child].finish) {
                child++; /* он больше и он есть */
            }
        
              //  больше ли он значения temp?
          
            if (array.buffer[child].finish > temp.finish) {
                array.buffer[index] = array.buffer[child];
                index = child;
                child = index * 2 + 1; /* индекс левого ребенка*/
            } else {
                break;
            }
        }
        /* перемещаем временную позицию на новое место */
       array.buffer[index] = temp;
    }
}

void ShowAnswer(){
        int numOfAsks = 0;
        dynamic_array<meetingData> array;
        fill_array(array);
        dynamic_array<int> starting_array;
        dynamic_array<int> finish_array;
    
        for(int i = 0; i < array.size; ++i)
        {
            dynamic_array_push_back(finish_array, array.buffer[i].finish);
        }
    
        heapsort(array);
        dynamic_array_clear(finish_array);
    
        for(int i = 0; i < array.size; ++i)
        {
            dynamic_array_push_back(starting_array, array.buffer[i].start);
            dynamic_array_push_back(finish_array, array.buffer[i].finish);
        }
        numOfAsks = OptimalSolution(starting_array, finish_array);
        std::cout << numOfAsks;
}


int main()
{
    ShowAnswer();
    return 0;
}