
#include "stdafx.h"
#include "aryt.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	Zmienna *we = new Zmienna();
	we->dodajV("x", 2);
	we->dodajV("y", 3);

	Wyrazenie *w0 = new Odejmij(
		new Pi(),
		new Dodaj(
			new Liczba(2),
			new Mnoz(
				new Zmienna("x"),
				new Liczba(7)
			)
		)
	);
	cout << w0->opis() << endl;;

	Wyrazenie *w1 = new Dziel(
		new Mnoz(
			new Odejmij(
				new Zmienna("x"),
				new Liczba(1)
			),
			new Zmienna("x")
		),
		new Liczba(2)
	);
	cout << w1->opis() << endl;;
	
	Wyrazenie *w2 = new Dziel(
		new Dodaj(
			new Zmienna("y"),
			new Liczba(5)),
		new Dodaj(
			new Liczba(2),
			new Mnoz(
				new Zmienna("x"),
				new Liczba(7)
			)

		)
	);
	cout << w2->opis() << endl;
	cout << std::endl;
	for (double i = 0; i <= 2; i = i + 0.01)
	{
		we->dodajV("x", i);
		std::cout<< w2->oblicz()<<std::endl;
	}

	getchar();
    return 0;
}

