// ConsoleApplication4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "manipnp.h"
#include "manipwp.h"
#include "wrapp.h"
#include <vector>
#include <fstream>

int main()
{
	std::string linia;
	fstream plik;
	std::vector<std::string> V;
	plik.open("plik.txt", ios::in);
	int nr = 1;
	if (plik.good() == true)
	{
		while (!plik.eof())
		{
			getline(plik, linia);
			V.push_back(linia);
			std::cout << Index(nr,6) << linia<<std::endl;
			nr++;
		}
		plik.close();
	}
	else
	{
		std::cout << "Nie wczytano";
	}

	std::cout << comma;
	std::cout << colon;
	getchar();
    return 0;
}

