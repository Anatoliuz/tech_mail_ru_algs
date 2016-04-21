#include <iostream>
#include <vector>
#include <string>
#define capacity 257
using namespace std;

int charAt(string word, int pos_int_word)
{
    if (pos_int_word < word.size())
        return word[pos_int_word];
    else
        return 0;
}


void msd_sort(vector<string>& str_array, int lo, int hi, vector<string>& aux, int pos_in_word )
{
    if ( hi <= lo ) return;
    
    vector<int> count;
    count.resize(capacity);
   
    for ( int i = lo; i <= hi; ++i )
        ++count[charAt(str_array[i], pos_in_word) + 1];
    
    for (int i = 1; i < count.size(); ++i)
        count[i] += count[i-1];
    
    for ( int i = lo; i <= hi; ++i )
        aux[count[charAt(str_array[i], pos_in_word) ]++] = str_array[i];
    
    for ( int i = lo; i <= hi; ++i )
        str_array[i] = aux[i - lo];
    
    for ( int r = 0; r < count.size(); ++r )
    {
        msd_sort(str_array,  lo + count[r], lo + count[r+1] - 1, aux,  pos_in_word+1);
    }
}

void sort(vector<string>& v)
{
    vector<string> aux(v.size());
    msd_sort(v, 0, v.size()-1, aux, 0);
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