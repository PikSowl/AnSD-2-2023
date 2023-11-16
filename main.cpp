#define RusLoc _setmode(_fileno(stdout), _O_U16TEXT); _setmode(_fileno(stdin),  _O_U16TEXT); _setmode(_fileno(stderr), _O_U16TEXT)

#include <iostream>
#include <fcntl.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <stack>

using std::wcout;
using std::wcin;
using std::swap;
using std::endl;
using std::wstring;
using std::find;
using std::sqrt;
using std::stack;

double numMaker(wstring& eq, int& i){
    int transfer = int(eq[i])-48;
    int dotPosition = -1;
    for (;int(eq[i+1])-48 < 10 && int(eq[i+1])-48 >=0;i++) transfer = transfer*10 + int(eq[i+1])-48;
    if (eq[i+1] == '.') {
        dotPosition = i+1;
        i++;
    }
    for (;int(eq[i+1])-48 < 10 && int(eq[i+1])-48 >=0;i++) transfer = transfer*10 + int(eq[i+1])-48;
    if (dotPosition == -1) dotPosition = i;
    return transfer / (pow(10,i - dotPosition));
}

double mathematics (double &a, double &b,wchar_t operation){
    switch (operation) {
        case '+':{
            return a += b;
        }
        case '-':{
            return a -= b;
        }
        case '*':{
            return a *= b;
        }
        case '/': {
            if (b == 0) {
                wcout << L"деление на 0" << endl;
                return - 999999;
            }
            else return a /= b;
        }
        default:
            return - 999999;
    }
}

double mathReader (wstring &eq, int &i){
    double temp;
    stack<double> numbers;
    stack<wchar_t> operations;
    int len = eq.length();
    int bt;

    for (; i < len; i++){
        if (eq[i] == '[' || eq[i] == '(' || eq[i] == '{'){
            bt =i;
            i++;
            numbers.push(mathReader(eq,i));
            if (numbers.top() == -999999) return - 999999;
            if (!((eq[bt] == '[' && eq[i] == ']')||(eq[bt] == '(' && eq[i] == ')')||(eq[bt] == '{' && eq[i] == '}'))){
                wcout << L"Ошибка в записи скобок" << endl;
                return - 999999;
            }
        }
        else if (eq[i] == '=' && i + 1 != len){
            wcout << L"Равенство не в конце выражения" << endl;
            return - 999999;
        }

        else if (int(eq[i])-48 < 10 && int(eq[i])-48 >=0) numbers.push(numMaker (eq, i));

        else if (eq[i] == '+' || eq[i] == '-' || eq[i] == '*' || eq[i] == '/') {
            operations.push(eq[i]);
            if (operations.size() > numbers.size()) {
                wcout << L"Ошибка в записи действий" << endl;
                return - 999999;
            }
            if(!operations.empty() && operations.size() < numbers.size())
                if (operations.top() == '*' || operations.top() == '/') {
                    temp = numbers.top();
                    numbers.pop();
                    numbers.top() = mathematics(numbers.top(), temp, operations.top());
                    operations.pop();
                }
        }

        else if (eq[i] == ']' || eq[i] == ')' || eq[i] == '}'){
            i--;
            len = i;
        }
    }
    while (!operations.empty()){
        temp = numbers.top();
        numbers.pop();
        numbers.top() = mathematics(numbers.top(), temp, operations.top());
        operations.pop();
    }

    return numbers.top();
}

int main() {
    RusLoc;
    wstring eq;
    int i = 0;

    wcout << L"Введите математическое выражение" << endl;
    wcin >> eq;

    if (eq[eq.length() - 1]!='='){
        wcout << L" Математическое выражение должно оканчиваться =";
        return 0;
    }

    wcout << mathReader(eq,i);
    return 0;
}
