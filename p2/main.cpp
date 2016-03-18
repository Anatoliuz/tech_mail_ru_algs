#include <iostream>

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



class ForwardList{
public:
    struct node{
        int numberOfNode;
        node* next; //указатель на следующий элемент
    };
   

    int max_size(){
        return maxNum;
    }
    int order_number(){
        return curNum; //номер элемента, добавленного последним в список
    }
    node* next_after(node* find_next){
        return find_next->next;
    }

    node* next_after(node* find_next, int number){
        if (number == 0) {
            return find_next;
        }
        int counter = 1;
        node* temp = find_next;
        while(counter <= number){
            counter++;
            temp = temp -> next;
        }
        return temp;
    }
    
    node* end(){
        node* temp = head->next;
        node* end = nullptr;
        while (temp->next != head) {
            temp = temp -> next;
            end = temp;
        }
        return temp;
    }
    node *&getHead() {
        return head;
    }
    
    void push_back(node* last)
    {
        if (!getHead()) {
            curNum = 1; //текущая позиция счёта(начинаем счёт с 1)
            head = new node;
            head->numberOfNode = curNum;
            head->next = head; //удовлетворяем критерию закольцованности списка
        }
        else {
            node* newStruct = new node;
            newStruct->numberOfNode = last->numberOfNode + 1;
            newStruct->next = head;
            last->next = newStruct;
            curNum = newStruct->numberOfNode;
        }
    }
    
    void push_back(node* last, int num)
    {
        push_back(last);
        end()->numberOfNode = num;
    }
    
    
    void remove_after(node* prev_node)
    {
        if(  prev_node -> next == head)
        {
            node* next =  prev_node->next;//сохраняем новую голову списка
            head = prev_node->next->next;
             prev_node->next =  prev_node->next->next;
            delete next; //освобождыем память
        }
        else {
            node *next =  prev_node->next;
             prev_node->next =  prev_node->next->next;
            delete next;
        }
    }
    
    ForwardList(int _maxNum){
        maxNum = _maxNum;
    }
    ~ForwardList(){//Деструктор
        while (head != NULL)  //Пока по адресу не пусто
        {
            node *temp=head->next; //Временная переменная для хранения адреса следующего элемента
            delete head; //Освобождаем адрес обозначающий начало
            head=temp; //Меняем адрес на следующий
        }
    }

private:
    int maxNum; //число N из условия задачи
    int curNum; //номер элемента, который в данный момент проверяется
    node* head; //указатель на колову списка
};


void delete_every_offset(ForwardList &list, int offset){
    int counter = 0;
    ForwardList::node *node = list.getHead();
    for (int i = 0; i < offset - 2; ++i) { //при первом удалении нужно пройти на 1 указатель меньше
        node = node -> next;
    }
    list.remove_after(node);
    for (; list.getHead()->next != list.getHead(); node = node->next) {
        if (counter == offset - 1) {
            list.remove_after(node);
            counter = 0;
        }
        counter++;
    }
    
    
}


void fill_list(ForwardList &list, int number){ //заполняем список
    if (list.getHead() == 0) {
        list.push_back(list.getHead());
    }
    for(int i = 0; ( i < list.max_size() - 1) && i < number; ++i)
        list.push_back(list.end(), list.order_number() + 1);
}

int main(int argc, const char * argv[])
{
    int size = 0; //N
    scanf("%d", &size);
    int offset = 0; //k
    scanf("%d", &offset);
    ForwardList* list = new ForwardList(size);
    fill_list(*list, size);
    delete_every_offset(*list, offset);
    printf("%d", list->getHead()->numberOfNode);
    return 0;
}
