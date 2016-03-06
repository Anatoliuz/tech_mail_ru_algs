#include <iostream>
#include <cassert>


/*
 Задача 2_4:
 “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N.
 Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
 (Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й,
 затем 2-й, затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й.
 Таким образом, уцелеет 4-й.) Необходимо определить номер уцелевшего.
 N, k ≤ 10000.
 */

//Решение:
/*
 Задача решается при помощи закольцованного односвязного списка.
 Каждый узел списка будет хранить первоначальный номер узла
 (на момент инициализации) и указатель на следующий элемент.
 У последнего элемента в списке указатель на следующий элемент последнего узла
 будет указывать на "голову" списка.
 Каждый k-ый элемент будем удалять, а у элемента,
 стоящего перед ним, указатель на следующий узел списка
 будем менять на элемент, находящийся после удаляемого.
 Цикл решения продолжается до тех пор, пока у "головы" списка указатель на следующий
 не станет равным нулем.
 У оставшегося элемента смотрим его номер, это и будет ответом.
 
 */


/*
 Класс, хранящий числа N, k из условия задачи,
 структуру(макет списка) и указатель на "голову" + все методы,
 необходимые для решения задачи
 */

class Count{
private:
    int maxNum; //число N из условия задачи
    int curNum; //номер элемента, который в данный момент проверяется на
    struct meStruct{ //описание узлов списка
        int numberOfNode; //номер узла на момент инициализации
        meStruct* next; //указатель на следующий элемент
    };
    meStruct* head;
public:
    
    Count(int _maxNum){
        maxNum = _maxNum;
        curNum = 1;
        head = new meStruct;
        head->numberOfNode = curNum;
        head->next = head;
        AddNumberOfNodes(head, curNum);
    }
    void AddNumberOfNodes(meStruct* last, int _curNum){
        while ( _curNum != maxNum)  {
            Add(last, ++_curNum);
            last = last->next;
        }
    }
    
    void Add(meStruct* last,int num)
    {
        meStruct* newStruct = new meStruct;
        newStruct->numberOfNode = num;
        newStruct->next = head;
        last->next = newStruct;
    }
    void DeleteAtK(int k){
        meStruct* node = head;
        node = OffsetByKMinusOne(node, k);
        DeleteNodeAfter(node);
        while (head -> next != head ) {
            node = OffsetByKMinusOne(node, k + 1);
            DeleteNodeAfter(node);
        }
    }
    
    meStruct* OffsetByKMinusOne(meStruct* node, int offset)
    {
        while (offset != 2) {
            node = node->next;
            offset--;
        }
        return node;
    }
    void DeleteNodeAfter(meStruct* node)
    {
        assert(node);
        if( node -> next == head)
        {
            meStruct* tempo;
            tempo = head -> next;
           // delete head; ??
            head = tempo;
            node->next = head;
            return true;
        }
        
        meStruct* temp = node -> next -> next;
        delete node->next;//?
        node->next = temp;
        //return true;
        
        
        //   std::cout << "we have problems";
     //   return false;
        
    }
 

    //

    

    int Result()
    {
        return head -> numberOfNode;
    }
    ~Count(){//Деструктор
        while (head != NULL)  //Пока по адресу не пусто
        {
            meStruct *temp=head->next; //Временная переменная для хранения адреса следующего элемента
            delete head; //Освобождаем адрес обозначающий начало
            head=temp; //Меняем адрес на следующий
        }
    }
};


int main(int argc, const char * argv[])
{
    int size = 0;
    scanf("%d", &size);
    int offset = 0;
    scanf("%d", &offset);
    
    Count* myClass = new Count(size);
    myClass -> DeleteAtK(offset);
    int res = myClass -> Result();
    printf("%d", res);
    return 0;
}

