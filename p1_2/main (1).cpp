#include <iostream>
#include <vector>
//структура хранит координаты точек
struct Point {
    int x;
    int y;
};
//стартовая точка
Point start_point;

//компаратор для нахождения стартовой точки
//согласованный с условием минимальности х и у
bool less(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x ? lhs.y < rhs.y : lhs.x < rhs.x;
}
//компоратор для сортировки точек по убыванию углов лучей
bool bigger_angle(const Point &lhs, const Point &rhs){
    return  (double)(lhs.y - start_point.y)/(double)(lhs.x - start_point.x) <
    (double)(rhs.y  - start_point.y)/(double)(rhs.x - start_point.x)  ;
}

template <typename T>
size_t find_start(std::vector<T> &array, size_t size, bool(*less)(const T& lhs,
                                                                  const T& rhs)){
    size_t start_point_index = 0;
    for (size_t i = 0; i < size; ++i) {
        if(less(array[i], array[start_point_index])){
            start_point_index = i;
        }
    }
    return start_point_index;
}


template <typename T>
void insertion_sort(std::vector<T> &array, size_t size, bool (*bigger_angle)(const T &lhs, const T &rhs)){
    for (size_t i = 1; i < size; ++i){
        size_t j = i;
        T temp = array[i];
        for (; j > 0 && bigger_angle(array[j-1], temp); --j)
            std::swap(array[j], array[j - 1]);
        array[j] = temp;
    }
}

int main() {
    size_t size = 0;
    std::cin >> size;
    std::vector<Point> points;
    points.resize(size);
    for (int i = 0; i < size; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }
    size_t start = 0;
    start = find_start(points,size , less);
    std::cout << points[start].x << " "<< points[start].y <<std::endl;
    start_point = points[start];
    points.erase(points.begin() + start);//удаляем стартовую точку  из массива
    insertion_sort(points, points.size(), bigger_angle);//сортируем по убыванию угла
    for (int i = 0; i < points.size(); ++i)
        std::cout << points[i].x << " " << points[i].y  <<std::endl;
    return 0;
}
