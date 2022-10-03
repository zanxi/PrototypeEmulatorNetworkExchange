#pragma once

#include "libH.h"

#define _CRT_SECURE_NO_WARNINGS
#define SIZE 6
void searchMinPath()
{
    int a[SIZE][SIZE]; // матрица связей
    int d[SIZE]; // минимальное расстояние
    int v[SIZE]; // посещенные вершины
    int temp, minindex, min;
    int begin_index = 0;
    system("chcp 1251");
    system("cls");
    // Инициализация матрицы связей
    for (int i = 0; i < SIZE; i++)
    {
        a[i][i] = 0;
        for (int j = i + 1; j < SIZE; j++) {
            printf("Введите расстояние %d - %d: ", i + 1, j + 1);
            scanf("%d", &temp);
            a[i][j] = temp;
            a[j][i] = temp;
        }
    }
    // Вывод матрицы связей
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            printf("%5d ", a[i][j]);
        printf("\n");
    }
    //Инициализация вершин и расстояний
    for (int i = 0; i < SIZE; i++)
    {
        d[i] = 10000;
        v[i] = 1;
    }
    d[begin_index] = 0;
    // Шаг алгоритма
    do {
        minindex = 10000;
        min = 10000;
        for (int i = 0; i < SIZE; i++)
        { // Если вершину ещё не обошли и вес меньше min
            if ((v[i] == 1) && (d[i] < min))
            { // Переприсваиваем значения
                min = d[i];
                minindex = i;
            }
        }
        // Добавляем найденный минимальный вес
        // к текущему весу вершины
        // и сравниваем с текущим минимальным весом вершины
        if (minindex != 10000)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (a[minindex][i] > 0)
                {
                    temp = min + a[minindex][i];
                    if (temp < d[i])
                    {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < 10000);
    // Вывод кратчайших расстояний до вершин
    printf("\nКратчайшие расстояния до вершин: \n");
    for (int i = 0; i < SIZE; i++)
        printf("%5d ", d[i]);

    // Восстановление пути
    int ver[SIZE]; // массив посещенных вершин
    int end = 4; // индекс конечной вершины = 5 - 1
    ver[0] = end + 1; // начальный элемент - конечная вершина
    int k = 1; // индекс предыдущей вершины
    int weight = d[end]; // вес конечной вершины

    while (end != begin_index) // пока не дошли до начальной вершины
    {
        for (int i = 0; i < SIZE; i++) // просматриваем все вершины
            if (a[i][end] != 0)   // если связь есть
            {
                int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
                if (temp == d[i]) // если вес совпал с рассчитанным
                {                 // значит из этой вершины и был переход
                    weight = temp; // сохраняем новый вес
                    end = i;       // сохраняем предыдущую вершину
                    ver[k] = i + 1; // и записываем ее в массив
                    k++;
                }
            }
    }
    // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
    printf("\nВывод кратчайшего пути\n");
    for (int i = k - 1; i >= 0; i--)
        printf("%3d ", ver[i]);
    getchar(); getchar();
    return;
}


// обратная польская запись
//typedef  std::string AnsiString;

struct AnsiString {
    std::string eq;
    int Length() { if (std::empty(eq)) return -1; else return eq.length(); }
    int SetLength(int m) { if (std::empty(eq)) return -1; else return eq.length(); }

    void operator =(AnsiString& ansiEq_)
    {
        this->eq = ansiEq_.eq;
    }

    void operator =(string ansiEq_)
    {
        this->eq = ansiEq_;
    }

    char operator [](int m)
    {
        return eq[m];
    }

    AnsiString operator +=(string streq)
    {
        this->eq = this->eq + streq;
        return *this;
    }

    AnsiString operator +=(char ch)
    {
        this->eq = this->eq + ch;
        return *this;
    }

};

class TStr2PPN {
    AnsiString instr, outstr; //input & output strings
    char curc; //the current character
    int iin; //the index of the input string
    char nextChar(); //get the next character
    void begin(); //handle plus & minus
    void mult_div(); //handle multiplication & division
    void symbol(); //handle characters & brackets

public:
    TStr2PPN() { //constructor
        iin = 1;
    }

    void convert(char* str); //convert to PPN
    AnsiString get_outstr(); //get the output string
};


//get the next character
inline char TStr2PPN::nextChar() {
    if (iin <= instr.Length()) return curc = instr[iin++];
    return curc = '\0';
}
//get the output string
inline AnsiString TStr2PPN::get_outstr() { return outstr; }

class Exception2 : public system_error {
public:
    //Exception2() {}
};

//convert to PPN
void TStr2PPN::convert(char* str) {
    try {
        instr = str;
        outstr.SetLength(0);
        iin = 1;
        nextChar();
        //begin the convertation
        begin();
        if (iin != (instr.Length() + 1)) // curc != '\0') {        
            //throw Exception("Syntax error");
            throw iin;    
        if (!isalpha(instr[instr.Length()]) && instr[instr.Length()] != ')') {
        //throw Exception("Syntax error");
        throw instr;
    }
}
catch (...) { throw; }
}

//handle plus & minus
void TStr2PPN::begin() {
    try {
        mult_div();
        while (curc == '+') // curc=='-') {
        {
            char temp = curc;
            nextChar();
            mult_div();
            outstr += temp;
        }
    }
   catch (...) { throw; }
}

//handle multiplication & division
void TStr2PPN::mult_div() {
    try {
        symbol();
        while (curc == '*')
        { // curc=='/') {
            char temp = curc;
            nextChar();
            symbol();
            outstr += temp;
        }
    
}
catch (...) 
{ 
    throw; 
}
}

//handle characters
void TStr2PPN::symbol() {
    try {
        if (curc == '(') {
            nextChar();
            begin();
            if (curc != ')') {
                //throw Exception("Error: wrong number of brackets");
            }
            else nextChar();
        }
        else
            if (isalpha(curc)) {
                outstr += curc;
                nextChar();
            }
            else { 
                //throw Exception("Syntax error"); 
            }
    }
    catch (...) { throw; }
}
