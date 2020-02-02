#include "stdafx.h"
#include <iostream>
#include <string>
#include "wymierne.h"


int main()
{
	Wymierna a(1,4);
	std::cout << "a " << a.wypisz_ulamek() << std::endl;
	Wymierna b(9);
	std::cout << "b " << b.wypisz_ulamek() << std::endl;
	Wymierna c;
	std::cout << "c " << c.wypisz_ulamek() << std::endl;
	Wymierna d = a;
	std::cout << "d " << d.wypisz_ulamek() << std::endl;
	Wymierna e(4, 8);
	std::cout << "e " << e.wypisz_ulamek() << std::endl;
	Wymierna f;
	f = a + e;
	std::cout << "a + e " << f.wypisz_ulamek() << std::endl;
	Wymierna g;
	g = a - e;
	std::cout << "a - e " << g.wypisz_ulamek() << std::endl;
	Wymierna h;
	h = a * e;
	std::cout << "a * e " << h.wypisz_ulamek() << std::endl;
	Wymierna i;
	i = a / e;
	std::cout << "a / e " << i.wypisz_ulamek() << std::endl;
	Wymierna j;
	j = -b;
	std::cout << "-b " << j.wypisz_ulamek() << std::endl;
	Wymierna k;
	k = !b;
	std::cout << "!b " << k.wypisz_ulamek() << std::endl;
	Wymierna l(-3, -5);
	std::cout << "l " << l.wypisz_ulamek() << std::endl;
	Wymierna z(7, 0);
	Wymierna err(922337203685477580);


	getchar();


    return 0;
}

