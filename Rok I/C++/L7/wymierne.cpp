#include "stdafx.h"
#include <iostream>
#include <climits>
#include <string>
#include "wymierne.h"
#include "wyjatki.cpp"


Wymierna::Wymierna(long long int l, long long int m)
{
	try 
	{			
		int d;
		d = NWD(l, m);
		if (m == 0)
			throw Dzielenie_przez_zero();
		if (d == 0)
			throw NWD_zero();
		if (m < 0)
		{
			m = m * (-1);
			l = l * (-1);
		}
		if (d == 1)
		{
			licz = l;
			mian = m;
		}
		else
		{
			licz = l / d;
			mian = m / d;
		}
	}
	catch (NWD_zero ob)
	{
		std::cerr << ob.what() << std::endl;
	}
	catch (Dzielenie_przez_zero ob)
	{
		std::cerr << ob.what() << std::endl;
	}
	catch (Przekroczenie_zakresu ob)
	{
		std::cerr << ob.what() << std::endl;
	}
}

Wymierna::Wymierna(long long int l)
{
	try
	{
		if (l > INT_MAX || l < INT_MIN)
			throw Przekroczenie_zakresu();
		licz = l;
		mian = 1;
	}
	catch (Przekroczenie_zakresu ob)
	{
		std::cerr << ob.what() << std::endl;
	}

}

Wymierna::Wymierna()
{
	licz = 0;
	mian = 1;
}

void Wymierna::skroc()
{
	int d = NWD(licz, mian);
	if (d != 1)
	{
		licz = licz / d;
		mian = mian / d;
	}
}


int Wymierna::NWD(int a, int b)
{
	try
	{
		if (a == 0 & b == 0)
		{
			throw NWD_zero();
		}
		int c;
		while (b != 0)
		{
			c = a;
			a = b;
			b = c % b;
		}
		if (a == 0)
			throw NWD_zero();
		return labs(a);
	}
	catch (NWD_zero ob)
	{
		std::cerr << ob.what() << std::endl;
	}
}

int Wymierna::NWW(int a, int b)
{
	try
	{
		int nwd;
		nwd = NWD(a, b);
		if (nwd == 0)
		{
			throw NWD_zero();
		}

		return (a*b) / NWD(a, b);
	}
	catch (NWD_zero ob)
	{
		std::cerr << ob.what() << std::endl;
	}
}

std::string Wymierna::wypisz_ulamek()
{
	return "[" + std::to_string(licz) + "/" + std::to_string(mian) + "]";
}

int Wymierna::licznik()
{
	return licz;
}

int Wymierna::mianownik()
{
	return mian;
}


Wymierna::Wymierna(const Wymierna &ob)
{
	licz = ob.licz;
	mian = ob.mian;
}

Wymierna & Wymierna::operator = (const Wymierna &ob)
{
	if (this != &ob)
	{
		licz = ob.licz;
		mian = ob.mian;
	}
	return *this;
}

Wymierna operator + (const Wymierna &wm1, const Wymierna &wm2)
{
	try
	{
		Wymierna Nowa;
		long long int l, m;
		m = Wymierna::NWW(wm1.mian, wm2.mian);
		if (m == 0)
			throw Dzielenie_przez_zero();
		l = ((m / wm1.mian) * wm1.licz) + ((m / wm2.mian) * wm2.licz);
		if (l > INT_MAX || l < INT_MIN)
			throw Przekroczenie_zakresu();
		Nowa.licz = l;
		Nowa.mian = m;

		Nowa.skroc();
		return Nowa;
	}
	catch (Dzielenie_przez_zero ob)
	{
		std::cerr << ob.what() << std::endl;
	}
	catch (Przekroczenie_zakresu ob)
	{
		std::cerr << ob.what() << std::endl;
	}



	
}

Wymierna operator - (const Wymierna &wm1, const Wymierna &wm2)
{
	try
	{
		Wymierna Nowa;
		long long int l, m;
		m = Wymierna::NWW(wm1.mian, wm2.mian);
		if (m == 0)
			throw Dzielenie_przez_zero();
		l = ((m / wm1.mian) * wm1.licz) - ((m / wm2.mian) * wm2.licz);
		if (l > INT_MAX || l < INT_MIN)
			throw Przekroczenie_zakresu();
		Nowa.licz = l;
		Nowa.mian = m;

		Nowa.skroc();
		return Nowa;
	}
	catch (Dzielenie_przez_zero ob)
	{
		std::cerr << ob.what() << std::endl;
	}
	catch (Przekroczenie_zakresu ob)
	{
		std::cerr << ob.what() << std::endl;
	}


}

Wymierna operator * (const Wymierna &wm1, const Wymierna &wm2)
{
	try
	{
		Wymierna Nowa;
		long long int l, m;
		l = wm1.licz * wm2.licz;
		m = wm1.mian * wm2.mian;
		if (m == 0)
			throw Dzielenie_przez_zero();
		if (l > INT_MAX || l < INT_MIN || m > INT_MAX || m < INT_MIN)
			throw Przekroczenie_zakresu();
		Nowa.licz = l;
		Nowa.mian = m;
		Nowa.skroc();
		return Nowa;
	}
	catch (Dzielenie_przez_zero ob)
	{
		std::cerr << ob.what() << std::endl;
	}
	catch (Przekroczenie_zakresu ob)
	{
		std::cerr << ob.what() << std::endl;
	}

}

Wymierna operator / (const Wymierna &wm1, const Wymierna &wm2)
{
	try
	{
		Wymierna Nowa;
		long long int l, m;
		l = wm1.licz * wm2.mian;
		m = wm1.mian * wm2.licz;
		if (m == 0)
			throw Dzielenie_przez_zero();
		if (l > INT_MAX || l < INT_MIN || m > INT_MAX || m < INT_MIN)
			throw Przekroczenie_zakresu();
		Nowa.licz = l;
		Nowa.mian = m;
		Nowa.skroc();
		if (m < 0)
		{
			m = m * (-1);
			l = l * (-1);
		}
		return Nowa;
	}
	catch (Dzielenie_przez_zero ob)
	{
		std::cerr << ob.what() << std::endl;
	}
	catch (Przekroczenie_zakresu ob)
	{
		std::cerr << ob.what() << std::endl;
	}

}


Wymierna operator - (const Wymierna &wm1)
{
	Wymierna Nowa;
	Nowa.licz = wm1.licz * (-1);
	Nowa.mian = wm1.mian;

	return Nowa;	
}

Wymierna operator ! (const Wymierna &wm1)
{
	try
	{
		Wymierna Nowa;
		int l, m;
		if (wm1.licz < 0)
		{
			l = wm1.mian * (-1);
			m = wm1.licz * (-1);
			if (m == 0)
				throw Dzielenie_przez_zero();
			Nowa.licz = l;
			Nowa.mian = m;
		}
		else
		{
			l = wm1.mian;
			m = wm1.licz;
			if (m == 0)
				throw Dzielenie_przez_zero();
			Nowa.licz = l;
			Nowa.mian = m;
		}
		return Nowa;
	}
	catch (Dzielenie_przez_zero ob)
	{
		std::cerr << ob.what() << std::endl;
	}


}

std::ostream& operator << (std::ostream &wyj, const Wymierna &w)
{
	double rz = static_cast<double>(w.licz) / w.mian;
	wyj << rz;
	return wyj;
}

Wymierna::operator double()
{
	return static_cast<double>(licz) / mian;
}

Wymierna::operator int()
{
	return licz / mian;
}