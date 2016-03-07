
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
            cout << "pos " << pos << "temp " << temp;
                temp = (temp + 1) % bufferSize;
            
        }
        cout << endl;
        
        head = 0;
        tail = bufferSize - 1;
        bufferSize *= 2;
        delete[] buffer;
        buffer = newBuffer;
        buffer[tail] = num;
        tail = ( tail + 1 ) % bufferSize;
        cout << "Added:" << num << endl;
        for (int index = 0; index < bufferSize; ++index) {
            cout<< "!!!" <<buffer[index] <<" " ;
        }
        cout<< endl;
    }
    else{
    buffer[tail] = num;
    tail = ( tail + 1 ) % bufferSize;
    for (int index = 0; index < bufferSize; ++index) {
        cout<< buffer[index] <<" " ;
    }
    cout<<endl;
    cout<< " head " << head << " tail " << tail <<  " ";
    cout<<endl;
    }

}

int MyQueue::PopFront(){
    if (head == tail) {
        cout << "QUEUE IS EMPTY";
        return -1;
    }
    int res = buffer[head];
    head = (head + 1) % bufferSize;
    for (int index = 0; index < bufferSize; ++index) {
        cout<<buffer[index] <<" " << endl;
    }

    cout<<endl;
    cout<< " head " << head << " tail " << tail <<  " ";
    cout<<endl;
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
        cin >> command;
        cin >> operand;
        if (command == POPFRONT && queue.IsEmpty() && operand == -1) {
            flagNo = 1;
        }
        if (command == POPFRONT &&  !queue.IsEmpty()) {
            if(operand != queue.PopFront()){
                flagNo = 1;
            }
        }
        if(command == PUSHBACK){
            queue.PushBack(operand);
        }
    }
    if (flagNo) {
        cout << "NO";
    }
    else{
        cout << "YES";
    }

    return 0;
}

