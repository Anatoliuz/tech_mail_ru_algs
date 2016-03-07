#include <iostream>
#include <cassert>
#define POPFRONT 2
#define PUSHBACK 3

using namespace std;
class MyQueue{
private:
    int* buffer;
    int bufferSize;
    int head;
    int tail;
public:
    MyQueue(int size);
    ~MyQueue() { delete[] buffer ;};
    void PushBack(int num);
    int PopFront();
    bool IsEmpty() const { return tail == head; }
};

MyQueue::MyQueue(int size ) :
bufferSize(size),
head(0),
tail(0)
{
    buffer = new int[bufferSize];
}

void MyQueue::PushBack( int num)
{
    if ( ( tail + 1 ) % bufferSize == head) {
        int* newBuffer = new int[bufferSize*2];
        int temp = head;
        
        for (int pos = 0; pos < bufferSize - 1; ++pos) {
            newBuffer[pos] = buffer[temp];
            temp = (temp + 1) % bufferSize;
        }
        head = 0;
        tail = bufferSize - 1;
        bufferSize *= 2;
        delete[] buffer;
        buffer = newBuffer;
        buffer[tail] = num;
        tail = ( tail + 1 ) % bufferSize;
    }
    else
    {
        buffer[tail] = num;
        tail = ( tail + 1 ) % bufferSize;
    }
    
}

int MyQueue::PopFront(){
    if (head == tail) {
               return -1;
    }
    int res = buffer[head];
    head = (head + 1) % bufferSize;
    return res;
}
int main(int argc, const char * argv[])
{
    int numOfCommands = 0;
    cin >> numOfCommands;
    int startingSize = 3;
    MyQueue queue = MyQueue(startingSize);
    bool flagNo = 0;
    for(int index = 0; index < numOfCommands; ++index)
    {
        int command = 0;
        int operand = 0;
        cin >> command >> operand;
        if (command == POPFRONT && queue.IsEmpty() && operand != -1) {
                flagNo = 1;
        }
        else if (command == POPFRONT &&  !queue.IsEmpty()) {
            if(operand != queue.PopFront()){
                flagNo = 1;
            }
        }
        if(command == PUSHBACK){
            queue.PushBack(operand);
        }
    }
    if (!flagNo) {
        cout << "YES";
    }
    else cout <<"NO";
    
    return 0;
}
