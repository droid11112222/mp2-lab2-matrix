// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include <string>
#include "tmatrix.h"
using namespace std;
//---------------------------------------------------------------------------

int main()
{
    int sizek;
    string act;
    cout << "enter a matrixes size: ";
    cin >> sizek;

    TDynamicMatrix<int> a(sizek), b(sizek);
    TDynamicMatrix<int> c(sizek);
    int i, j;

    setlocale(LC_ALL, "Russian");

    cout << "enter a matrix A (" << sizek * sizek << " elemets): ";
    cin >> a;

    cout << "enter a matrix B (" << sizek * sizek << " elemets): ";
    cin >> b;

    cout << "enter the action  (+, -, *): ";
    cin >> act;

    if (act == "+") {
        c = a + b;
    }
    else if (act == "-") {
        c = a - b;
    }
    else if (act == "*") {
        c = a * b;
    }
    else {
        c = a + b;
        cout << "Undefined action." << endl;
    }

    cout << "Matrix a = " << endl << a << endl;
    cout << "Matrix b = " << endl << b << endl;
    cout << "Matrix c = " << endl << c << endl;

    return 0;
}
//---------------------------------------------------------------------------
