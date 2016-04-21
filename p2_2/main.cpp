#include <iostream>
#include <vector>

//Задача 2_2
bool less(const  int & lhs, const  int& rhs ){
    return lhs < rhs;
}

template <typename T>
class Heap{
public:
    Heap();
    ~Heap();
    
    size_t get_size();
    T extract();//O(logn)
    void make_heap(); //O(n)
    void insert(T key);//O(logn)
private:
    T* data;
    size_t size;
    
    void fill_data(); //O(n)
    bool isEmpty();//O(1)
    void siftDown(size_t); //O(logn)
    void siftUp(size_t);//O(logn)
};

template <typename T>
Heap<T>::Heap(){
    size = 0;
    std::cin >> size;
    data = new  int[size]();
    for (int i = 0; i < size; ++i) {
        std::cin >> data[i];
    }
}

template <typename T>
Heap<T>::~Heap(){
    if(data)
        delete[] data;
}

template <typename T>
size_t Heap<T>::get_size(){
    return size;
}

template <typename T>
T Heap<T>::extract(){
    T min = data[0];
    data[0] = data[size - 1];
    --size;
    Heap::siftDown(0);
    return min;
}


template <typename T>
void Heap<T>::make_heap(){
    for (int i = size / 2 ; i >= 0; --i)
        siftDown(i);
}


template <typename T>
void Heap<T>::insert(T key){
    size = size + 1;
    data[size - 1] = key;
    siftUp(size - 1);
}

template <typename T>
void Heap<T>::siftUp(size_t i){
    while ( less(data[i], data[ (i - 1) / 2] ) ) {   // i == 0 — мы в корне
        std::swap(data[i], data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

template <typename T>
void Heap<T>::siftDown(size_t i){
    while (2 * i + 1 < size){
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t j = left;
        if(right < size && less( data[right] , data[left] ) ){
            j = right;
        }
        if(less( data[i] , data[j] ) || data[i] == data[j]){
            break;
        }
        std::swap(data[i], data[j]);
        i = j;
    }
}

int main() {
    Heap<int> heap;
    heap.make_heap();
    unsigned int time = 0; //время выполнения

    //О(n) * O(logn)
    while( heap.get_size() != 1){
        int lhs = heap.extract();
        int rhs = heap.extract();
        time = time + lhs  + rhs;
        heap.insert(lhs+rhs);
    }
    
    std::cout << time;
    return 0;
}
