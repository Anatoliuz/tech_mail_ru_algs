#include <iostream>
#include <cstdlib>
#define MAX 1000

using namespace std;
char str[MAX];
int sp = 0;

int opPriority[256];
void Init(int* priorityArray){
    priorityArray['('] = 0;
    priorityArray['+'] = 1;
    priorityArray['-'] = 1;
    priorityArray['*'] = 2;
    priorityArray['/'] = 2;

}
char stack[MAX];
int ints[MAX];
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
int IsEmptyOperatorsStack() {
    if (sp <= 0)
        return 1;
    else
    {
        return 0;
    }
}
int np = 0;
int PopNumber(void) {
    if (np > 0) {
        return ints[--np];
    } else {
        return 0;
    }
};
int PeekNumber(void) {
    int a = np;
    --a;
    if (a >= 0)
    {
        return ints[a];
    } else {
        return 0;
    }
};
void PushNumber(int a) {
    ints[np++] = a;
};
int IsEmptyLong() {
    if (np <=
        0)
        return 1;
    else
    {
        return 0;
    }
}
int LengthOfMas(char* array)
{
    int length = 0;
    for (int index = 0; array[index] != '\0'; ++index) {
        ++length;
    }
    return length;
}
char* DoPolishNotion(char* inputArray,  int length)
{

    int jndex = 0;
    char op1;
    int curPriority = 0;
    int stackPriority = 0;
    for (int i = 0; i < MAX; ++i) {
        str[i] = '\0';
    }
    for (int i = 0; i < length; ++i) {
        if (isspace(inputArray[i])) {}
        
        if(inputArray[i] >= '0' && inputArray[i] <= '9')
        {
            str[jndex] = inputArray[i];
            jndex++;
        }
        else if(inputArray[i] == '(')
        {
            str[jndex] = '|';
            jndex++;
            PushOperator(inputArray[i]);
        }
        else if(inputArray[i] == ')')
        {
            while (PeekOperator() != '(') {
                str[jndex] = PopOperator();
                jndex++;
            }
            PopOperator();
            
        }
        else if (inputArray[i] == '+' || inputArray[i] == '-'  || inputArray[i] == '/' || inputArray[i] == '*')
        {
            if (opPriority[(int)inputArray[i]] == 1) {
                curPriority = 1;
            }
            else if(opPriority[(int)inputArray[i]] == 2)
                curPriority = 2;
            
            if(IsEmptyOperatorsStack())
            {
                str[jndex] = '|';
                jndex++;
                PushOperator(inputArray[i]);
                //printf("empty stack in oper processing)\n");
            }
            else if (!IsEmptyOperatorsStack())
            {
                op1 = PeekOperator();
                if ((int)opPriority[(int)op1] == 1) {
                    stackPriority = 1;
                }
                else if ((int)opPriority[(int)op1] == 2)
                {
                    stackPriority = 2;
                }
                else if ((int)opPriority[(int)op1] == 0)
                {
                    stackPriority = 0;
                }
                while (curPriority <= stackPriority) {
                    if(!IsEmptyOperatorsStack()){
                        str[jndex] = '|';
                        jndex++;
                        str[jndex] = PopOperator();
                        jndex++;
                        op1 = PeekOperator();
                        if ((int)opPriority[(int)op1] == 1) {
                            stackPriority = 1;
                        }
                        else if ((int)opPriority[(int)op1] == 2)
                        {
                            stackPriority = 2;
                        }
                        else curPriority = (stackPriority + 1);
                    }
                    
                }
                str[jndex] = '|';
                jndex++;
                PushOperator(inputArray[i]);
            }
        }
        
    }
    str[jndex] = '|';
    jndex++;
    while (!IsEmptyOperatorsStack()) {
        str[jndex] = PopOperator();
        jndex++;
    }
    return str;
}



void CountInPolishNotion(char* polishNotion, int length)
{
    int num = 0;
    for (int i = 0; i < length ; ++i)
    {
        int j  = 0;
        int k = 0;
        if(polishNotion[i] >= '0' && polishNotion[i] <= '9')
        {
            int sizeOfTempArray = 200;
            char* charToNumArray = new char[sizeOfTempArray]();
            j = i;
            while (polishNotion[j] >= '0' && polishNotion[j] <= '9') {
                charToNumArray[k] = polishNotion[j];
                j++;
                k++;
            }
            num = atof(charToNumArray);
            PushNumber(num);
            k = 0;
            i = j - 1;
            delete[] charToNumArray;
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
            int delimiter  = PopNumber();
            PushNumber(  PopNumber() / delimiter);
        }
        
    }
}
int main()
{
    char* inputCharArray = new char[MAX]();
    int size = MAX;
        for (int i = 0;  i < size; ++i) {
            char buf;
            cin >> buf;
            if(cin.eof()){
                break;
            }
            inputCharArray[i] = buf;
        }
    Init(opPriority);
    int length =  LengthOfMas(inputCharArray);
    char* polishNotion = DoPolishNotion(inputCharArray, length);
    length = LengthOfMas(polishNotion);
    CountInPolishNotion(polishNotion, length);
    int a = PeekNumber();
    cout << a;
    delete [] inputCharArray;
    return 0;
}
