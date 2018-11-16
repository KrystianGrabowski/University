#pragma once
#include <iostream>
#include <vector>
#include <map>

class Wyrazenie
{
public:
	virtual double oblicz() = 0;
	virtual std::string opis() = 0;
};

// #########################  LICZBA  #########################
class Liczba : public Wyrazenie
{
private:
	double w;
public:
	Liczba(double wrt);
	virtual double oblicz();
	virtual std::string opis();
};

class Stala : public Wyrazenie
{
private:
	static std::map<std::string, double> stale;
public:
	Stala();
	static double zwraca(std::string s);
};
// #########################  STA£A PI  #########################
class Pi : public Stala
{
public:
	virtual double oblicz();
	virtual std::string opis();
};
// #########################  STA£A E  #########################
class E : public Stala
{
public:
	virtual double oblicz();
	virtual std::string opis();
};
// #########################  STA£A FI  #########################
class Fi : public Stala
{
public:
	virtual double oblicz();
	virtual std::string opis();
};
// #########################  ZMIENNA  #########################
class Zmienna : public Wyrazenie
{
private:
	static std::vector<std::pair<std::string, double>> zmienne;
	std::string n;
public:
	Zmienna();
	Zmienna(std::string nowa);
	virtual double oblicz();
	virtual std::string opis();
	static void dodajV(std::string n, double w);
	static double wartoscV(std::string n);
	static bool istniejeV(std::string n);
	static void zamien(std::string n, double w);

};
// #########################  1ARG  #########################
class Operator1arg : public Wyrazenie
{
protected:
	double wn;
private:
	Wyrazenie *w1;
public:
	Operator1arg(Wyrazenie *a);
	Wyrazenie* zwrot();

};

// #########################  1ARG FUNKCJE  #########################
class Bezwzgl : public Operator1arg
{
public:
	Bezwzgl(Wyrazenie *a) ;
	virtual double oblicz();
	virtual std::string opis();
};

class Sin : public Operator1arg
{
public:
	Sin(Wyrazenie*a);
	virtual double oblicz();
	virtual std::string opis();
};

class Cos : public Operator1arg
{
public:
	Cos(Wyrazenie*a);
	virtual double oblicz();
	virtual std::string opis();
};

class Exp : public Operator1arg
{
public:
	Exp(Wyrazenie*a);
	virtual double oblicz();
	virtual std::string opis();
};

class Ln : public Operator1arg
{
public:
	Ln(Wyrazenie*a);
	virtual double oblicz();
	virtual std::string opis();
};

class Przeciw : public Operator1arg
{
public:
	Przeciw(Wyrazenie*a);
	virtual double oblicz();
	virtual std::string opis();
};

class Odwrot : public Operator1arg
{
public:
	Odwrot(Wyrazenie*a);
	virtual double oblicz();
	virtual std::string opis();
};



// #########################  2ARG  #########################
class Operator2arg : public Operator1arg
{
protected:
	static std::string POP_O;
	std::string OST;
	double wa, wb;
private:
	Wyrazenie *b;
public:
	static std::string ostatni();
	static void zmien(std::string n);
	Operator2arg(Wyrazenie *a, Wyrazenie *b);
	Wyrazenie* zwrot2();

};

// #########################  2ARG FUNKCJE  #########################
class Dodaj : public Operator2arg
{
public:
	Dodaj(Wyrazenie *a, Wyrazenie *b);
	virtual double oblicz();
	virtual std::string opis();
};

class Odejmij : public Operator2arg
{
public:
	Odejmij(Wyrazenie *a, Wyrazenie *b);
	virtual double oblicz();
	virtual std::string opis();
};

class Mnoz : public Operator2arg
{
public:
	Mnoz(Wyrazenie *a, Wyrazenie *b);
	virtual double oblicz();
	virtual std::string opis();
};

class Dziel : public Operator2arg
{
public:
	Dziel(Wyrazenie *a, Wyrazenie *b);
	virtual double oblicz();
	virtual std::string opis();
};

class Log : public Operator2arg
{
public:
	Log(Wyrazenie *a, Wyrazenie *b);
	virtual double oblicz();
	virtual std::string opis();
};

class Modulo : public Operator2arg
{
public:
	Modulo(Wyrazenie *a, Wyrazenie *b);
	virtual double oblicz();
	virtual std::string opis();
};

class Potega : public Operator2arg
{
public:
	Potega(Wyrazenie *a, Wyrazenie *b);
	virtual double oblicz();
	virtual std::string opis();
};