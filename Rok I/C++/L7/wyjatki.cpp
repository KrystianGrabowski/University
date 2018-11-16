#include "stdafx.h"
#include <iostream>
#include <exception>
#include <stdexcept>
class Wyjatek_wymierny //: public exception
{
private:
	std::string blad;
public:
	Wyjatek_wymierny()	{blad = "Wyjatek wymierny!";}
	Wyjatek_wymierny(std::string str)	{blad = str;}
	const char* what() {return blad.c_str();}
};
class Zero : Wyjatek_wymierny
{
private:
	std::string blad;
public:
	Zero() { blad = "Zero w niedozwolonym miejscu!"; }
	Zero(std::string str) { blad = str; }
	std::string what() { return blad; }
};
class Dzielenie_przez_zero : Zero
{
private:
	std::string blad;
public:
	Dzielenie_przez_zero() { blad = "Dzielenie przez zero!"; }
	Dzielenie_przez_zero(std::string str) { blad = str; }
	std::string what() { return blad; }
};

class NWD_zero : Zero
{
private:
	std::string blad;
public:
	NWD_zero() { blad = "NWD rowny zero!"; }
	NWD_zero(std::string str) { blad = str; }
	std::string what() { return blad; }
};

class Zakresy : Wyjatek_wymierny
{
private:
	std::string blad;
public:
	Zakresy() { blad = "Blad zakresu!"; }
	Zakresy(std::string str) { blad = str; }
	std::string what() { return blad; }
};

class Przekroczenie_zakresu : Wyjatek_wymierny
{
private:
	std::string blad;
public:
	Przekroczenie_zakresu() { blad = "Przekroczenie zakresu!"; }
	Przekroczenie_zakresu(std::string str) { blad = str; }
	std::string what() { return blad; }
};
