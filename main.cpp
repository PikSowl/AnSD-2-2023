#define RusLoc _setmode(_fileno(stdout), _O_U16TEXT); _setmode(_fileno(stdin),  _O_U16TEXT); _setmode(_fileno(stderr), _O_U16TEXT)
int num[] = {0,1,2,3,4,5,6,7,8,9};
int brack[] = {'[','(','{',']',')','}'};
int oper[] = {'+','-','*','/','^'};

#include <iostream>
#include <fcntl.h>
#include <algorithm>
#include <string>
#include <cmath>

using std::wcout;
using std::wcin;
using std::swap;
using std::endl;
using std::wstring;
using std::find;
using std::sqrt;

double numMaker(wstring& eq, int& i){
    int transfer = int(eq[i])-48;
    int dotPosition = -1;
    while ((int(eq[i+1])-48 < 10 && int(eq[i+1])-48 >=0)||eq[i+1] == '.'){
        if (eq[i+1] == '.') dotPosition = i+1;
        else transfer = transfer*10 + int(eq[i+1])-48;
        i++;
    }
    if (dotPosition == -1) dotPosition = i;
    return transfer / (pow(10,i - dotPosition));
}

double mathematics (double a, double b,char operTipe){
    switch (operTipe) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': {
            if (b == 0) {
                wcout << L"деление на 0" << endl;
                return -9999999;
            }
            else return a / b;
        }
        case '^': return pow(a,b);
        default: return -9999999;
    }
}

int main() {
    RusLoc;
    int len = 10;
    wstring brackets;
    char operTipe = 'o';
    double a = -1, b;
    wstring eq;

    wcout << L"Введите математическое выражение" << endl;
    wcin >> eq;
    len = int(eq.length());

    if (eq[len - 1]!='='){
        wcout << L"Математическое выражение должно оканчиваться =";
        return 0;
    }

    for(int i =0;i < len - 1; i++){
        if (find(brack,brack+3,eq[i]) != brack+3){
            brackets.push_back(eq[i]);
        }

        else if (find(brack+3,brack+6,eq[i]) != brack+6){
            if (!((brackets.back() == brack[0] && eq[i] == brack[3]) || (brackets.back() == brack[1] && eq[i] == brack[4]) || (brackets.back() == brack[2] && eq[i] == brack[5]))){
                wcout << L"Некоректный порядок скобок";
                return 0;
            }
            brackets.pop_back();
        }

        else if (find(num,num+10,int(eq[i]) - 48) != num+10){
            b = a;
            a = numMaker(eq,i);
            if (b != -1) {
                a = mathematics(b, a, operTipe);
                if (a == -9999999) return -1;
                operTipe = 'o';
            }
        }

        else if (find(oper,oper+5,eq[i]) != oper+5){
            if (operTipe != 'o') {
                wcout << L"Нет числа между действиями";
                return 0;
            }
            operTipe = char(eq[i]);
        }
    }

    wcout << a;

    return 0;
}
