#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include "kolejka.h"
using namespace std;
char wybor;
string elem;
void inter(Kolejka x)
{
        cout << endl;
        cout << "Kolejka"<<endl;
        cout << "---------------------"<<endl;
        cout << "1.Wstaw"<<endl;
        cout << "2.Pobierz"<<endl;
        cout << "3.Sprawdz"<<endl;
        cout << "4.Rozmiar"<<endl;
        cout << "5.Wypisz"<<endl;
        cout << "6.Zakoncz"<<endl;
  while(wybor != '6')
    {
        wybor = getch();

        switch(wybor)
        {
        case '1':
            cout << "Podaj element do wstawienia: ";
            cin >> elem;
            x.wstaw(elem);
        break;
        case '2':
            cout<<x.pobierz()<<endl;
        break;
        case '3':
            cout<<x.sprawdz()<<endl;
        break;
        case '4':
            cout<<x.rozmiar()<<endl;
        break;
        case '5':
            x.wypisz();
        break;
        default:
            if (wybor!='6')
            cout << "Bledna komenda" << endl;
        }
    }
    wybor = NULL;
}

int main()
{

    Kolejka k1(20);
    k1.wstaw("ala");
    k1.wstaw("ma");
    k1.wstaw("kota");
    Kolejka k2(move(k1));
    inter(k2);





return 0;
}
