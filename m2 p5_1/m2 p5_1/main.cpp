#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;
bool less(const int &lhs, const int& rhs){
    return lhs < rhs;
}
int charAt(string s, int d)
{
    
    if (d < s.size())
        return s[d];
    else
        return -1;
}

class MSD
{
private:
    int capacity = 256;
    vector<string> aux;       // auxiliary array for distribution
    
public:
    
    
    void sort(vector<string>& a)
    {
        aux.resize(a.size());
        msd_sort(a, 0, a.size(), 0);
    }
    
    void msd_sort(vector<string>& a, int l, int r, int d)
    {  // Sort from a[lo] to a[hi], starting at the dth character.
        // int* count = new int[capacity+1]()
        
        
        if (r <= l + 1) return;
        int* count = new int[256]();
        for (int i = l; i < r; i++)
            count[charAt(a[i], d) + 1]++;
        for (int k = 1; k < 256; k++)
            count[k] += count[k-1];
        for (int i = l; i < r; i++)
            aux[count[charAt(a[i], d)]++] = a[i];
        for (int i = l; i < r; i++)
            a[i] = aux[i];
        for (int i = 1; i < 255; i++)
            msd_sort(a, l + count[i], l + count[i+1] - 1 , d+1);
    }
    
};




int main() {
    int c;
    string str;
    vector<string> str_array;
    MSD msdclass;
    
    
    while((c = getc(stdin)) != EOF){
        if(c == '\n' && !str.empty()){
            str_array.push_back(str);
            str.clear();
        }
        else str.push_back(c);
    }
    if( c == EOF && !str.empty() ){
        str_array.push_back(str);
        str.clear();
    }
    
    msdclass.sort(str_array);
    
    cout << "After sort" << endl;
    for (vector<string>::iterator it = str_array.begin(); it < str_array.end(); ++it) {
        cout << *it << endl;
    }
    // MSD_sort(str_array);
    return 0;
}