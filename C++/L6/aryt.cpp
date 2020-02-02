#include "stdafx.h"
#include <iostream>
#include "aryt.h"
#include <sstream>
#include <math.h>
#include <vector>
#include <map>

// ###################################  LICZBA  ###################################
Liczba::Liczba(double wrt)
{
	w = wrt;
}
double Liczba::oblicz()
{
	return w;
}
std::string Liczba::opis()
{
	std::stringstream ss;
	ss << w;
	std::string l = ss.str();
	return l;
}

std::map<std::string, double> Stala::stale;
Stala::Stala()
{
	stale["pi"] = 3.14;
	stale["e"] = 2.71;
	stale["fi"] = 1.61;

}
double Stala::zwraca(std::string s)
{
	return stale[s];
}
// ###################################  STA£A PI  ###################################

double Pi::oblicz()
{
	return zwraca("pi");
}
std::string Pi::opis()
{
	return "pi";
}
// ###################################  STA£E E  ###################################
double E::oblicz()
{
	return zwraca("e");
}
std::string E::opis()
{
	return "e";
}
// ###################################  STA£E FI  ###################################
double Fi::oblicz()
{
	return zwraca("fi");
}
std::string Fi::opis()
{
	return "fi";
}
// ###################################  ZMIENNA  ###################################
std::vector<std::pair<std::string, double>> Zmienna::zmienne;
Zmienna::Zmienna() {}
Zmienna::Zmienna(std::string nowa)
{
	n = nowa;
}
double Zmienna::oblicz()
{
	return wartoscV(n);
}
std::string Zmienna::opis()
{
	return n;
}
void Zmienna::dodajV(std::string n, double w)
{
	if (istniejeV(n) == false)
	{
		zmienne.push_back(std::make_pair(n, w));
	}
	else
	{
		zamien(n, w);
	}
}

bool Zmienna::istniejeV(std::string n)
{
	int w = zmienne.size();
	for (int i = 0; i < w; i++)
	{
		if (zmienne[i].first == n)
		{
			return true;
		}
	}
	return false;
}	
double Zmienna::wartoscV(std::string n)
{

	int w = zmienne.size();

	for (int i = 0; i < w; i++)
	{
		if (zmienne[i].first == n)
		{
			return zmienne[i].second;
		}
	}
	return 0;
}

void Zmienna::zamien(std::string n, double w)
{
	int p = zmienne.size();

	for (int i = 0; i < p; i++)
	{
		if (zmienne[i].first == n)
		{
			zmienne[i].second = w;
		}
	}
}



// ###################################  1ARG  ###################################
Operator1arg::Operator1arg(Wyrazenie *a)
{
	w1 = a;
}
Wyrazenie* Operator1arg::zwrot()
{
	return w1;
}
// ###################################  1ARG FUNKCJE  ###################################

// ============================== BEZWZGLEDNA ==============================
Bezwzgl::Bezwzgl(Wyrazenie *a) : Operator1arg(a) {}

double Bezwzgl::oblicz()
{
	wn = zwrot()->oblicz();
	return fabs(wn);
}

std::string Bezwzgl::opis()
{
	return "|" + zwrot()->opis() + "|";
}

// ============================== SINUS ==============================
Sin::Sin(Wyrazenie *a) : Operator1arg(a) {}

double Sin::oblicz()
{
	wn = zwrot()->oblicz();
	return sin(wn);
}
std::string Sin::opis()
{
	return "sin(" + (zwrot()->opis()) + ")";
}

// ============================== COSINUS ==============================
Cos::Cos(Wyrazenie *a) : Operator1arg(a) {}

double Cos::oblicz()
{
	wn = zwrot()->oblicz();
	return cos(wn);
}
std::string Cos::opis()
{
	return "cos(" + (zwrot()->opis()) + ")";
}
// ============================== EXP ==============================
Exp::Exp(Wyrazenie *a) : Operator1arg(a) {}

double Exp::oblicz()
{
	wn = zwrot()->oblicz();
	return exp(wn);
}
std::string Exp::opis()
{
	return "exp(" + (zwrot()->opis()) + ")";
}

// ============================== LN ==============================
Ln::Ln(Wyrazenie *a) : Operator1arg(a) {}

double Ln::oblicz()
{
	wn = zwrot()->oblicz();
	return log(wn);
}
std::string Ln::opis()
{
	return "ln(" + (zwrot()->opis()) + ")";
}

// ============================== PRZECIWNA ==============================
Przeciw::Przeciw(Wyrazenie *a) : Operator1arg(a) {}

double Przeciw::oblicz()
{
	wn = zwrot()->oblicz();
	return (-wn);
}
std::string Przeciw::opis()
{
	return "przeciw(" + (zwrot()->opis()) + ")";
}

// ============================== ODWROTNA ==============================
Odwrot::Odwrot(Wyrazenie *a) : Operator1arg(a) {}

double Odwrot::oblicz()
{
	wn = zwrot()->oblicz();
	return (1/wn);
}
std::string Odwrot::opis()
{
	return "odwrot(" + (zwrot()->opis()) + ")";
}

// ###################################  2ARG  ###################################
Operator2arg::Operator2arg(Wyrazenie *a, Wyrazenie *b) : Operator1arg(a) { this->b = b; }
Wyrazenie* Operator2arg::zwrot2()
{
	return b;
}
std::string Operator2arg::ostatni()
{
	return POP_O;
}
std::string Operator2arg::POP_O;
void Operator2arg::zmien(std::string n)
{
	POP_O = n;
}
// ###################################  2ARG FUNKCJE  ###################################

// ============================== DODAWANIE ==============================
Dodaj::Dodaj(Wyrazenie *a, Wyrazenie *b) : Operator2arg(a, b) { POP_O = ""; }
double Dodaj::oblicz()
{
	wa = zwrot()->oblicz();
	wb = zwrot2()->oblicz();
	return wa + wb;
}

std::string Dodaj::opis()
{
	OST = ostatni();
	if (OST == "*" ||OST == "/" || OST == "-")
	{
		zmien("+");
		return "(" + zwrot()->opis() + "+" + zwrot2()->opis() + ")";
	}
	zmien("+");
	return zwrot()->opis() + "+" + zwrot2()->opis() ;
}

// ============================== ODEJMOWANIE ==============================
Odejmij::Odejmij(Wyrazenie *a, Wyrazenie *b) : Operator2arg(a, b) { POP_O = ""; }
double Odejmij::oblicz()
{
	wa = zwrot()->oblicz();
	wb = zwrot2()->oblicz();
	return wa - wb;
}

std::string Odejmij::opis()
{
	OST = ostatni();
	if (OST == "*" || OST == "/")
	{
		zmien("-");
		return "(" + zwrot()->opis() + "-" + zwrot2()->opis() + ")";
	}
	zmien("-");
	return zwrot()->opis() + "-" + zwrot2()->opis();
}

// ============================== MNO¯ENIE ==============================
Mnoz::Mnoz(Wyrazenie *a, Wyrazenie *b) : Operator2arg(a, b) { POP_O = ""; }
double Mnoz::oblicz()
{
	wa = zwrot()->oblicz();
	wb = zwrot2()->oblicz();
	return wa * wb;
}

std::string Mnoz::opis()
{
	OST = ostatni();
	if (OST == "-" || OST == "/")
	{
		zmien("*");
		return "(" + zwrot()->opis() + "*" + zwrot2()->opis() + ")";
	}
	zmien("*");
	return zwrot()->opis() + "*" + zwrot2()->opis();
}


// ============================== DZIELENIE ==============================
Dziel::Dziel(Wyrazenie *a, Wyrazenie *b) : Operator2arg(a, b) { POP_O = ""; }
double Dziel::oblicz()
{
	wa = zwrot()->oblicz();
	wb = zwrot2()->oblicz();
	return wa / wb;
}

std::string Dziel::opis()
{
	OST = ostatni();
	if (OST == "*" || OST == "-")
	{
		zmien("/");
		return "(" + zwrot()->opis() + "/" + zwrot2()->opis() + ")";
	}
	zmien("/");
	return zwrot()->opis() + "/" + zwrot2()->opis();
}

// ============================== LOGARYTM ==============================
Log::Log(Wyrazenie *a, Wyrazenie *b) : Operator2arg(a, b) {}
double Log::oblicz()
{
	wa = zwrot()->oblicz();
	wb = zwrot2()->oblicz();
	return (log(wa) / log(wb));					// (PODSTAWA TO WB A LICZBA TO WA)
}

std::string Log::opis()
{
	return  "log(" + zwrot2()->opis() + ")" + zwrot()->opis();
}

// ============================== MODULO ==============================
Modulo::Modulo(Wyrazenie *a, Wyrazenie *b) : Operator2arg(a, b) {}
double Modulo::oblicz()
{
	wa = zwrot()->oblicz();
	wb = zwrot2()->oblicz();
	return  fmod(wa, wb);
}

std::string Modulo::opis()
{
	return "(" + zwrot()->opis() + "%" + zwrot2()->opis() + "(" ;
}

// ============================== POTEGA ==============================
Potega::Potega(Wyrazenie *a, Wyrazenie *b) : Operator2arg(a, b) {}
double Potega::oblicz()
{
	wa = zwrot()->oblicz();
	wb = zwrot2()->oblicz();
	return  pow(wa, wb);
}

std::string Potega::opis()
{
	return zwrot()->opis() + "^" + zwrot2()->opis();
}




