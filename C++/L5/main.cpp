#include <iostream>
#include "bufor.h"

int main()
{
	std::cout << "---------------- Lista----------------"<<std::endl;
	Lista L;
	std::cout << L;
	L.Dodaj(0, 10);
	std::cout << L;
	L.Dodaj(1, 20);
	std::cout << L;
	L.Dodaj(2, 30);
	std::cout << L;
}


