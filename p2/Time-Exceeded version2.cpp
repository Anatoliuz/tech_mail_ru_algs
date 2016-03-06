#include <iostream>
#include <cassert>
using namespace std;


int Survived(int size, int offset){
   
    int doArray[size];
    
    for (int pos = 0; pos < size; ++pos) {
        doArray[pos] = pos + 1;
    }
    int numOfEx = size - 1;
    int count = 0;
    int positive = 0;
    for (int j = 0 ; j < numOfEx ; ++j) {
        for (int i = 0; i < size ; ++i) {
            if ( doArray[i] >0 ) {
                count++;
                
                if ( (count) % offset == 0 ) {
                    doArray[i] = -1;
                    count = 0;
                }
                else if  (i + 1 == size && doArray[i] != -1) {
                    continue;
                }
            }
            for (int i = 0; i < size ; ++i){
                if (doArray[i] > 0) {
                    positive++;
                }
            }
            if (positive == 1) {
                for (int pos = 0; pos < size; ++pos) {
                    if (doArray[pos] > 0) {
                        return doArray[pos];
                    }
                }
                return 0;
            }
            else positive = 0;
        }
    }
    return -1;
}


int main(int argc, const char * argv[])
{
    int n = 0;
    scanf("%d", &n);
    int k = 0;
    scanf("%d", &k);
    int res = 0;
    res = Survived(n, k);
    printf("%d", res);
    return 0;
}
