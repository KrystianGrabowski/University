#pragma once
#include  <iostream>

class Wymierna
{
	int licz, mian;
public:
	Wymierna(long long int l, long long int m);
	Wymierna(long long int l);
	Wymierna();
	Wymierna(const Wymierna &ob);
	Wymierna& operator = (const Wymierna &ob);
	static int NWD(int a, int b);
	static int NWW(int a, int b);
	std::string wypisz_ulamek();
	int licznik();
	int mianownik();
	void skroc();

	friend Wymierna operator + (const Wymierna &wm1, const Wymierna &wm2);
	friend Wymierna operator - (const Wymierna &wm1, const Wymierna &wm2);
	friend Wymierna operator * (const Wymierna &wm1, const Wymierna &wm2);
	friend Wymierna operator / (const Wymierna &wm1, const Wymierna &wm2);
	friend Wymierna operator - (const Wymierna &wm1);
	friend Wymierna operator ! (const Wymierna &wm1);
	operator double();
	explicit operator int();
	friend std::ostream& operator << (std::ostream &wyj, const Wymierna &w);
};


