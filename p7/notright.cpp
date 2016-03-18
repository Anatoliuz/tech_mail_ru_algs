#include <iostream>
#include <cassert>
#include <algorithm>
#define ERROR -1000
struct meetingData{
    int start;
    int finish;
    int duration;
    bool visited;
    meetingData(): start(0), finish(0), duration(0), visited(false){}
};
void Add(int start, int finish, meetingData& meeting){
    meeting.start = start;
    meeting.finish = finish;
    meeting.duration = finish - start;
}
template <typename T>
struct dynamicArray{
    T *buffer;
    size_t size;
    size_t capacity;
    
    dynamicArray(): buffer(NULL), size(0), capacity(0){}
};
template <typename T>
void DynamicArrayInit(dynamicArray<T> &array){
    array.buffer = NULL;
    array.size   = 0;
    array.capacity = 0;
}
size_t max(size_t a, size_t b){
   return a > b ? a : b;
}
template <typename T>
T min(T a, T b){
    return a < b ? a : b;
}
template <typename T>
void swap(T &a, T &b){
    T temp = a;
    a = b;
    b = temp;
}
template <typename T>
void DynamicArrayResize(dynamicArray<T> &array, size_t new_capacity)
{
    T *temp = new T[new_capacity];
    for (int i = 0; i < array.size && i < new_capacity;  ++i) {
        swap(temp[i], array.buffer[i]);
    }
    swap(array.buffer, temp);
    delete []temp;
    
    array.capacity = new_capacity;
    if (new_capacity  < array.size) {
        array.size = new_capacity;
    }
}
template <typename T>
void DynamicArrayAdd(dynamicArray<T> &array, T value)
{
    if (array.size == array.capacity) {
        DynamicArrayResize(array, max(1, array.capacity*2) );
    }
    array.buffer[array.size] = value;
    ++array.size;
}
template <typename T>
size_t GetAt(dynamicArray<T> &array, size_t index){
    assert(array && index < array.size && index >= 0);
    return array.buffer[index];
}
template <typename T>
void DynamicArrayClear(dynamicArray<T> &array){
    delete[] array.buffer;
    array.buffer = NULL;
    array.capacity = 0;
    array.size = 0;
    
}
meetingData input(){
    
    meetingData meeting;
    int start  = 0;
    int finish = 0;
    std::cin >> start;
    std::cin >> finish;
    if ( (finish - start) || start  < finish) {
        Add(start, finish, meeting);
        return meeting;
    }
    else{
        meeting.duration = -1;
        return meeting;
    }
}
bool CompareByDuration(const meetingData &a, const meetingData &b)
{
    return a.duration < b.duration;
}
template <typename T>

size_t FindeNextMinDuration(dynamicArray<T> &array, meetingData &minDuration){

    bool flag = false;
    int indexOfNewMinData = 0;
    std::cout << "Visited? ";
    for (int i = 0; i < array.size; ++i) {
        std::cout << " " << array.buffer[i].visited;
    }
    std::cout << std::endl;
    if(minDuration.visited) {
        for (int index = 0; index < array.size; ++index) {
            if(!array.buffer[index].visited)
            {
             minDuration = array.buffer[index];
            return  FindeNextMinDuration(array, minDuration);
            }
        }
    }
    else   if (!minDuration.visited) {
        for (int ind = 0; ind < array.size; ++ind) {
            if (array.buffer[ind].duration < minDuration.duration &&
                array.buffer[ind].duration && !array.buffer[ind].visited ) {
                minDuration = array.buffer[ind];
                indexOfNewMinData = ind;
                flag = true;
            }
            else if (!flag){
                if (array.buffer[ind].duration == minDuration.duration &&
                    array.buffer[ind].duration && !array.buffer[ind].visited ) {
                    minDuration = array.buffer[ind];
                    indexOfNewMinData = ind;
                    flag = true;
                }
            }
        }
        std::cout << std::endl;
        std::cout << "minDuration start " << minDuration.start <<" finish "<< minDuration.finish << std::endl;
        return indexOfNewMinData;
    }
    return indexOfNewMinData;
}

template <typename T>
size_t FindLatestTime(dynamicArray<T> &array){
    
    int latestTime = array.buffer[0].finish;
    for (int i = 0; i < array.size; ++i) {
        if (array.buffer[i].finish > latestTime) {
            latestTime = array.buffer[i].finish;
        }
    }
    return latestTime;
}
template <typename T>
void FillVisited(dynamicArray<T> &array, bool* section, meetingData& meeting)
{
    for (int i = meeting.start; i <= meeting.finish; ++i) {
        section[i] = true;
    }
}
int main()
{
    dynamicArray<meetingData> array;
    DynamicArrayInit(array);
    int counter = 0;
    meetingData meeting = input();
    int numOfAsks = 0;
    while ( meeting.duration > 0) {
        DynamicArrayAdd(array, meeting);
        meeting = input();
    }
    for (int i = 0; i < array.size; ++i) {
        std::cout << array.buffer[i].duration << " ";
    }
    //ввод закончен
    size_t latestTime = FindLatestTime(array);
    bool* section = new bool[latestTime+1]();
    
    std::cout << std::endl;

    meetingData curMinData = array.buffer[0];
    size_t nextMin =  FindeNextMinDuration(array, curMinData);
    ++counter;
    FillVisited(array, section, array.buffer[nextMin] );
    numOfAsks++;
    array.buffer[nextMin].visited = true;
    curMinData = array.buffer[nextMin];
    std::cout << "минимум на отрезке занятого времени: ";
    for (int i = 0; i < latestTime + 1; ++i) {
        std::cout << section[i];
    }
    std::cout << std::endl;
    for (int j = 0 ; j <= array.size; ++j) {
    for (int i = 0; i <= array.size; ++i) {
        std::cout << std::endl << "i " << i << std::endl;
        if (!array.buffer[i].visited && counter <= array.size) {
            size_t nextMin =  FindeNextMinDuration(array, curMinData);
            array.buffer[nextMin].visited = true;
            curMinData = array.buffer[nextMin];

           if (array.buffer[nextMin].duration > 1 &&  !(section[array.buffer[nextMin].start + 1] || section[array.buffer[nextMin].finish-1] ||
                   (section[array.buffer[nextMin].start] && section[array.buffer[nextMin].finish])  ) )
            {
//array.buffer[nextMin].visited = true;
                FillVisited(array, section, array.buffer[nextMin] );
                numOfAsks++;
                std::cout << std::endl <<"added?" << array.buffer[nextMin].start <<
                " " <<array.buffer[nextMin].finish ;
                std::cout << "минимум на отрезке занятого времени: ";
                for (int i = 0; i < latestTime + 1; ++i) {
                    std::cout << section[i];
                }
            }
            else if (array.buffer[nextMin].duration == 1 &&  !( section[array.buffer[nextMin].start] && section[array.buffer[nextMin].finish] ) )
            {
                FillVisited(array, section, array.buffer[nextMin] );
                numOfAsks++;
                std::cout << std::endl <<"added  " << array.buffer[nextMin].start <<
                " " <<array.buffer[nextMin].finish << " " << std::endl;
                std::cout << "минимум на отрезке занятого времени: ";
                for (int i = 0; i < latestTime + 1; ++i) {
                    std::cout << section[i];
                }
            }

            
        }
    }
    }
    std::cout << "numofasks " << numOfAsks;
    DynamicArrayClear(array);
    return 0;
}