#pragma once
#include <iostream>
class Ignore
{
	int x;
	friend std::istream& operator >> (std::istream &is, const Ignore &ign);
public:
	Ignore(int xks);
};

class Index
{
	int x, w;
	friend std::ostream& operator << (std::ostream &os, const Index &id);
public:
	Index(int xks, int wu);
};
