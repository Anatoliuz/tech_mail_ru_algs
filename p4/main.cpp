#include <iostream>
//Код команды извлечь
#define POPFRONT 2
//Добавить
#define PUSHBACK 3
//4_1. Р​еализовать очередь с динамическим зацикленным буфером.
//
//Решение
/* В данной очереди, в отличии от очереди есть одно основное отличие.
    Если мы добавляем элемент и ( tail + 1 ) % bufferSize == head,
    создаем новый буфер, в два раза большего размера и переносим в него все элементы,
    заполняя его с нулевого индекса.
*/

using namespace std;
class MyQueue{
private:
    int* buffer; //динамический буфер
    int bufferSize; //размер буфера
    int head;
    int tail;
public:
    MyQueue(int size); //конструктор(задаем начальный размер очереди и выделяем память)
    ~MyQueue() { delete[] buffer ;}; //деструктор
    void PushBack(int num); //добавляем элемент
    int PopFront(); //извлекаем
    bool IsEmpty() const { return tail == head; } //проверка очереди на пустоту
};

MyQueue::MyQueue(int size ) : 
bufferSize(size), //bufferSize теперь имеет размер size
head(0),
tail(0)
{
    buffer = new int[bufferSize];
}

void MyQueue::PushBack( int num)
{
    if ( ( tail + 1 ) % bufferSize == head) { //если очередь полна
        int* newBuffer = new int[bufferSize*2]; //выделяем новый буфер
        int temp = head; // временная переменная хранящая индекс головы очереди
        //переносим все элементы из старого буфера в новый
        for (int pos = 0; pos < bufferSize - 1; ++pos) { 
            newBuffer[pos] = buffer[temp]; 
            //индекс следующего элемента из старого буфера будем 
            //искать используя старую "адресную" арифметику
            temp = (temp + 1) % bufferSize; 
        }
        //когда новый буфер заполнен
        //необходимо обновить параметры очереди в соответствии с новым буфером
        head = 0;//голова имеет индекс 0
        tail = bufferSize - 1; //обновляем значение указателя(индекс с нуля)
        bufferSize *= 2; //новый bufferSize
        delete[] buffer; //освобождаем память старого буфера
        buffer = newBuffer; //меняем указатель на новую область в памяти
        buffer[tail] = num; //добавляем новый элемент в новый буфер
        tail = ( tail + 1 ) % bufferSize; //обновляем значение индекса ховоста
    }
    else
    {
        //если место есть
        buffer[tail] = num; //добавляем элемент на место хвоста
        tail = ( tail + 1 ) % bufferSize;//сдвигаем хвост
    }
    
}

int MyQueue::PopFront(){
    //если список пуст возвращаем -1
    if (head == tail) {
               return -1;
    }
    int res = buffer[head]; //число извлеченное из очереди
    head = (head + 1) % bufferSize; //обновляем индекс головы
    return res;//возвращаем извлеченное число
}

void CheckFunction(){
    int numOfCommands = 0;
    cin >> numOfCommands; //число команд
    int startingSize = 3; //начальный размер очереди
    MyQueue queue = MyQueue(startingSize); //инициализируем очередь

    bool flagNo = 0; //флаг проверки Yes/No

    //цикл ввода команд и обновления флагов
    for(int index = 0; index < numOfCommands; ++index)
    {
        int command = 0; 
        int operand = 0;
        cin >> command >> operand;
        //Если введена команда извлечь, список пустой, но операнд в коммандной 
        //строке не равен нулю,  флаг равен 1(в конце программы будет напечатано NO)
        if (command == POPFRONT && queue.IsEmpty() && operand != -1) {
                flagNo = 1;
        }
        //Если очередь не пустая
        //Проверяем равен ли элемент на вершине очереди операнду из
        // коммандной строки. Если да, флаг равен 1.
        //(в конце программы будет напечатано NO)
        else if (command == POPFRONT &&  !queue.IsEmpty()) {
            if(operand != queue.PopFront()){
                flagNo = 1;
            }
        }
        //Если команда добавить
        //просто добавляем
        if(command == PUSHBACK){
            queue.PushBack(operand);
        }
    }
    //Если флаг так и не стал единицей
    //выводим да, иначе - нет.
    if (!flagNo) {
        cout << "YES";
    }
    else cout <<"NO";
}
int main(int argc, const char * argv[])
{
    CheckFunction();
    return 0;
}
