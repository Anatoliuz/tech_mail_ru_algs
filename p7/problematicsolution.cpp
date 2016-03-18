#include <iostream>
#include <cassert>
#include <algorithm>
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
int main()
{
    dynamicArray<meetingData> array;
    DynamicArrayInit(array);
    meetingData meeting = input();
    int min = 0;
    while ( meeting.duration > 0) {
    DynamicArrayAdd(array, meeting);
    meeting = input();
    }
    for (int i = 0; i < array.size; ++i) {
        std::cout << array.buffer[i].duration;
    }
    std::cout << CompareByDuration(array.buffer[0], array.buffer[1]);
    min = array.buffer[0].duration;
    std::sort(array.buffer[0], array.buffer[array.size], CompareByDuration);
    for (int i = 0; i < array.size; ++i) {
        for (int j = 0; j < array.size; ++j) {
            
        }
    }
    DynamicArrayClear(array);
    return 0;
}