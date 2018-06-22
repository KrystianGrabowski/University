#include <iostream>
#include "123.h"
using namespace std;

int main()
{

    double tab1[] = { 50 ,11 };


    wielomian w1;
    cin >> w1;
    cout << "Strumien wejscia:    "<< w1 <<endl;
    wielomian w;
    cout << "Jednomian bezparametrowy:     " << w << endl;
    wielomian w2(10,2);
    cout << "Jednomian 10 st :    "<< w2 <<endl;
    wielomian w3(1,tab1);
    cout << "Wielomian z podana lista:    "<< w3 << endl;
    wielomian w4({7,6,5});
    cout << "Inicjalizacja lista:    "<< w4 << endl;
    wielomian w5(w3);
    cout << "Kopiuje:    " << w5 << endl;
    wielomian w6(move(w4));
    cout << "Przenosze:     " << w6 << endl;

    double tab2[] = {1,2,3,4,5};
    double tab3[] = {6,7,8,9,10};
    wielomian oper1(4,tab2);
    wielomian oper2(4,tab3);
    cout << endl;
    cout << " -----------------  ----------------     OPERACJE"<< endl;
    cout << oper1 << endl;
    cout << oper2 << endl;
    cout << "Dodajemy    :" << oper1 + oper2 << endl;
    cout << "Odejmujemny    :" << oper2 - oper1 << endl;
    cout << "Mnozymy    :" << oper1 * oper2 << endl;
    cout << "Mnozymy przez stala   :" << oper2 * 3 << endl;
    cout << endl;
    cout << " -----------------  ----------------     OPERACJE Z ="<< endl;
    double tab4[] = {2,2,2,2,2};
    double tab5[] = {3,3,3,3,3};
    wielomian oper3(4,tab4);
    wielomian oper4(4,tab5);
    cout << oper3 << endl;
    cout << oper4 << endl;
    oper3 += oper4;
    cout << "Dodajemy(=)    :" << oper3 << endl;
    oper4 -= oper3;
    cout << "Dodajemy(=)    :" << oper4 << endl;
    oper3 *= oper4;
    cout << "Dodajemy(=)    :" << oper3 << endl;
    oper3 *= 4;
    cout << "Dodajemy(=)    :" << oper3 << endl;

    double tab10[] = {3,1,1,1,1};
    wielomian operk(4,tab10);
    cout << operk << endl;
    cout << "Obliczanie w X:    "<< operk(2) << endl;
    cout << "0 elemen:   "<<operk[0]<<endl;
    return 0;
}
