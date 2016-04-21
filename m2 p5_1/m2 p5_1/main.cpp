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
        return 0;
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
        msd_sort(a, 0, a.size() - 1, 0);
    }
    
    void msd_sort(vector<string>& a, int lo, int hi, int d)
    {  // Sort from a[lo] to a[hi], starting at the dth character.
        // int* count = new int[capacity+1]();
        int count[capacity + 1];
        for (int i = 0; i <= capacity; ++i) {
            count[i] = 0;
        }
        if(hi <= lo) return;
        
        for (size_t i = lo; i <= hi; ++i)
            ++count[charAt(a[i], d) + 1];
        for (size_t i = 1; i < 256; ++i)
            count[i] += count[i - 1];
        for (size_t i = lo; i <= hi; ++i)
            aux[count[charAt(a[i], d)]++] = a[i];
        for (size_t i = lo; i <= hi; ++i)
            a[i] = aux[i];
        for (int r = 0; r < capacity-1; r++)
            msd_sort(a, lo + count[r], lo + count[r+1] - 1, d+1);
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