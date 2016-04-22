//
//  main.cpp
//  m2 p4_1
//
//  Created by fix on 22/04/16.
//  Copyright © 2016 Anatoly Filinov. All rights reserved.
//

#include <iostream>
using namespace std;

void fill_data(int *array, size_t size){
    for (size_t i = 0; !cin.eof() && i < size; ++i) {
        cin >> array[i];
    }
}
void merge_sorted_arrays(int *array_a, size_t sizeA, int *array_b ,size_t sizeB){
    
}
void merge(int *a, size_t a_len, int *b, size_t b_len, int *c) {
    int i=0;
    int j=0;
    for (;i < a_len and j < b_len;) {
        if (a[i] < b[j]) {
            c[i+j] = a[i];
            ++i;
        }
        else {
            c[i+j] = b[j];
            ++j;
        }
    }
    if (i==a_len) {
        for (;j < b_len;++j) {
            c[i+j] = b[j];
        }
    }
    else {
        for (;i < a_len;++i) {
            c[i+j] = a[i];
        }
    }
}
void copy_array(int *array_a, int size_a, int *array_b, int size_b){
    
}
void merge_sort(int *data, size_t size, int *buffer) {
    if (size < 2) return;
    
    merge_sort(data, size / 2, buffer);  merge_sort(&data[size / 2], size - size / 2, buffer);
    
    merge(&data[0], size / 2, &data[size/2], size - size / 2, buffer);
    
    for (size_t pos = 0; pos < size; ++ pos) {
        data[pos] = buffer[pos];  }
}

void print_array(int *array, size_t size){
    for(int i = 0; i < size; ++i){
        cout << array[i] << " ";
    }
    cout << endl;
}
int main(int argc, const char * argv[]) {
    size_t n, k = 0;
    cin >> n >> k;
    int *input_data = new int[k]();
    int *ans = new int[k];
    for (int i = 0; n - i != n % k; i += k) {
        fill_data(input_data, k);
        merge_sort(input_data, k, ans);
        copy_array(<#int *array_a#>, <#int size_a#>, <#int *array_b#>, <#int size_b#>)
    }
        //print_array(input_data, k);
        //print_array(ans, k);
    delete[] input_data;
    delete[] ans;
    return 0;
}
