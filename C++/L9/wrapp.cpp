#include "stdafx.h"
#include "wrapp.h"


PlikWejsciowy::PlikWejsciowy(std::string nazwa)
{
	plik.open(nazwa.c_str());
	if (!plik.good())
		throw "Blad wczytywania";
}

std::string PlikWejsciowy::linia(int nr)
{
	int nr_linii = 1;
	std::string linia;
	while (getline(plik, linia))
	{
		if (nr_linii == nr)
		{
			return linia;
		}
		nr_linii++;
	}
	return "Brak linii";
}
	/*	{
	char c;
	while (plik.get(c) || c != '\n')
	std::cout << c;
	return "ad"	;

	}*/

std::ostream& operator << (std::ostream &R, PlikWejsciowy &PW)
{
	std::string linia;
	while (getline(PW.plik, linia))
	{
		R << linia;
	}
	return R;
}

PlikWejsciowy::~PlikWejsciowy()
{
	plik.close();
}

PlikWyjsciowy::PlikWyjsciowy(std::string nazwa)
{
	plik.open(nazwa.c_str());
	if (!plik.good())
		throw "Blad wczytywania";
}
std::istream& operator >> (std::istream &R, PlikWyjsciowy &PW)
{
	return R;
}
PlikWyjsciowy::~PlikWyjsciowy()
{
	plik.close();
}