#include "stdafx.h"
#include "manipwp.h"


Ignore::Ignore(int xks)
{
	x = xks;
}

std::istream& operator >> (std::istream &is, const Ignore &ign)
{
	is.ignore(ign.x, '\n');
	return is;
}

Index::Index(int xks, int wu)
{
	x = xks;
	w = wu;
}

std::ostream& operator << (std::ostream &os, const Index &id)
{
	os << "[";
	os.width(id.w - 2);
	os << id.x << "]";
	return os;
}