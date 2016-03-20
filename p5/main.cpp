#include <iostream>
#include <cstdlib>
#define MAX 2000 //размер строки выражения в обратной польской записи
#define STACK_SIZE 200 //стек операторов
using namespace std;
char str[MAX] = {};
int sp = 0;

int opPriority[256];
//приоритет операция
void Init(int* priorityArray){
    priorityArray['('] = 0;
    priorityArray['+'] = 1;
    priorityArray['-'] = 1;
    priorityArray['*'] = 2;
    priorityArray['/'] = 2;
    
}/* на инициализацию вида int opPriority[256] = { ['('] = 0, ['+'] } ;
    компилятор g++ с ключем static выдавал ошибку:
    "sorry unimplemented:non-trivial designated initializers not supported"   
*/

char stack[STACK_SIZE];
long longs[MAX];
char PopOperator(void) {
    if (sp > 0) {
        return stack[--sp];
    } else {
        return 0;
    }
};
char PeekOperator(void) {
    int a = sp;
    a--;
    if (a >= 0)
    {
        return stack[a];
    } else {
        return 0;
    }
};
void PushOperator(char a) {
    stack[sp++] = a;
};
bool IsEmptyOperatorsStack() {
    if (sp <= 0)
        return 1;
    else
    {
        return 0;
    }
}
long np = 0;
long PopNumber(void) {
    if (np > 0) {
        return longs[--np];
    } else {
        return 0;
    }
};
long PeekNumber(void) {
    long a = np;
    --a;
    if (a >= 0)
    {
        return longs[a];
    } else {
        return 0;
    }
};
void PushNumber(long a) {
    longs[np++] = a;
};
bool IsEmptyLong() {
    if (np <=  0)
        return 1;
    else
    {
        return 0;
    }
}
int LengthOfMas(char* array)
{
    int length = 0;
    for (int index = 0; array[index] != '\0' && array[index] !='\n'; ++index) {
        ++length;
    }
    return length;
}
//вставка разелителя
void insert_sign(char *str, int& index){
    if (str[index-1] != '|') {
        str[index] = '|';
        ++index;
    }
}
char* DoPolishNotion(char* inputArray,  int length)
{
    
    int jndex = 0;
    int op1 = 0;
    int curPriority = 0;
    int stackPriority = 0;
    
    for (int i = 0; i < length; ++i) {
        if (isspace(inputArray[i])) {
            continue;
        }
        if(inputArray[i] >= '0' && inputArray[i] <= '9')
        {
            str[jndex] = inputArray[i];
            jndex++;
        }
        else if(inputArray[i] == '(')
        {
            insert_sign(str, jndex);
            PushOperator(inputArray[i]);
        }
        else if(inputArray[i] == ')')
        {
            insert_sign(str, jndex);
            while (PeekOperator() != '(') {
                str[jndex] = PopOperator();
                jndex++;
            }
            PopOperator();
        }
        else if (inputArray[i] == '+' || inputArray[i] == '-'  || inputArray[i] == '/'
                 || inputArray[i] == '*')
        {
            if (opPriority[(int)inputArray[i]] == 1) {
                curPriority = 1;
            }
            else if(opPriority[(int)inputArray[i]] == 2)
                curPriority = 2;
            if(IsEmptyOperatorsStack())
            {
                insert_sign(str, jndex);
                PushOperator(inputArray[i]);
                insert_sign(str, jndex);
            }
            else if (!IsEmptyOperatorsStack())
            {
                op1 = PeekOperator();
                if ((int)opPriority[op1] == 1) {
                    stackPriority = 1;
                }
                else if ((int)opPriority[op1] == 2)
                {
                    stackPriority = 2;
                }
                else if (opPriority[op1] == 0)
                {
                    stackPriority = 0;
                }
                while (curPriority <= stackPriority) {
                    if(!IsEmptyOperatorsStack()){
                        insert_sign(str, jndex);
                        str[jndex] = PopOperator();
                        jndex++;
                        op1 = PeekOperator();
                        if ((int)opPriority[op1] == 1) {
                            stackPriority = 1;
                        }
                        else if ((int)opPriority[op1] == 2)
                        {
                            stackPriority = 2;
                        }
                        else if ((int)opPriority[op1] == 0)
                        {
                            stackPriority = 0;
                        }
                        // else curPriority = (stackPriority + 1);
                    }
                    
                }
                insert_sign(str, jndex);
                PushOperator(inputArray[i]);
                insert_sign(str, jndex);
            }
        }
        
    }
    insert_sign(str, jndex);
    while (!IsEmptyOperatorsStack()) {
        str[jndex] = PopOperator();
        jndex++;
        insert_sign(str, jndex);
    }
    return str;
}


//вычисляем выражение в обратной польской записи
void CountInPolishNotion(char* polishNotion, int length)
{
    long num = 0;
    for (int i = 0; i < length ; ++i)
    {
        int j  = 0;
        int k = 0;
        int sizeOfTempArray = 20;
        if(polishNotion[i] >= '0' && polishNotion[i] <= '9')
        {
            char* charToNumArray = new char[sizeOfTempArray]();
            delete[] charToNumArray;
            
            j = i;
            while (polishNotion[j] >= '0' && polishNotion[j] <= '9') {
                charToNumArray[k] = polishNotion[j];
                j++;
                k++;
            }
            num = atol(charToNumArray);
            PushNumber(num);
            k = 0;
            i = j - 1;
        }
        else if (polishNotion[i] == '+'){
            PushNumber(  PopNumber() + PopNumber() );
        }
        else if (polishNotion[i] == '-'){
            PushNumber(  -PopNumber() + PopNumber() );
        }
        else if (polishNotion[i] == '*'){
            PushNumber(  PopNumber() * PopNumber() );
        }
        else if (polishNotion[i] == '/'){
            long delimiter  = PopNumber();
            PushNumber(  PopNumber() / delimiter);
        }
    }
}
int main()
{
    char* inputCharArray = new char[MAX]();
    int c = 0;
    int i = 0;
    while ((c = fgetc(stdin)) != EOF && c !='\n') {
        inputCharArray[i] = c;
        i++;
    }
    i = 0;
    
    Init(opPriority);
    int length_input = LengthOfMas(inputCharArray);
    
    char* polishNotion = DoPolishNotion(inputCharArray, length_input);
    int length = LengthOfMas(polishNotion);
    CountInPolishNotion(polishNotion, length);
    if (length_input > 0) {
        cout <<  PeekNumber();
    }
    
    
    return 0;
}
