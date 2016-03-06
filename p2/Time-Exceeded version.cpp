#include <iostream>
#include <cassert>
using namespace std;
class Count{
private:
    int maxNum;
    int curNum;
    struct meStruct{
        int numberOfNode;
        meStruct* next;
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
    
    meStruct* OffsetByKMinusOne(meStruct* node, int offset)
    {
        while (offset != 2) {
            node = node->next;
            offset--;
        }
        return node;
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
    
    bool DeleteNodeAfter(meStruct* node)
    {
        assert(node);
            if( node -> next == head)
            {
                meStruct* tempo;
                tempo = head -> next;
                delete head;
                head = tempo;
                node->next = head;
                return true;
            }

            meStruct* temp = node -> next -> next;
            delete node->next;//?
            node->next = temp;
            return true;

        
         //   std::cout << "we have problems";
            return false;
        
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
    
    int Result()
    {
        return head -> numberOfNode;
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

