#include <iostream>
#include <vector>
#include <string>

using namespace std;

int charAt(string s, int d)
{
    if (d < s.size())
        return s[d];
    else
        return -1;
}


void msd_sort(vector<string>& v, vector<string>& aux, int pos, int lo, int hi)
{
    if ( hi <= lo ) return;
    
    vector<int> count;
    count.resize(256);
    
    for ( auto i = lo; i <= hi; ++i )
        ++count[charAt(v[i], pos) + 2];
    
    
    for (auto i = 1; i < count.size(); ++i)
        count[i] += count[i-1];
    
    for ( auto i = lo; i <= hi; ++i )
        aux[count[charAt(v[i], pos)+1]++] = v[i];
    
    for ( int i = lo; i <= hi; ++i )
        v[i] = aux[i - lo];
    
    for ( int r = 0; r < count.size(); ++r )
    {
        msd_sort(v, aux, pos+1, lo + count[r], lo + count[r+1] - 1);
    }
}

void sort(vector<string>& v)
{
    vector<string> aux(v.size());
    msd_sort(v, aux, 0, 0, v.size()-1);
}


int main() {
    int c;
    string str;
    vector<string> str_array;
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
    sort(str_array);
    for (vector<string>::iterator it = str_array.begin(); it < str_array.end(); ++it) {
        cout << *it << endl;
    }
    return 0;
}