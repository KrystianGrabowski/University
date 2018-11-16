#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class PlikWejsciowy
{
private:
	ifstream plik;

public:
	PlikWejsciowy(std::string nazwa);
	std::string linia(int nr);
	~PlikWejsciowy();
	friend std::ostream& operator << (std::ostream &R, PlikWejsciowy &PW);

};

class PlikWyjsciowy
{
public:
	std::string tekst;
	PlikWyjsciowy(std::string nazwa);
	~PlikWyjsciowy();
	friend std::istream& operator >> (std::istream &R, PlikWyjsciowy &PW);

private:
	ofstream plik;

};
