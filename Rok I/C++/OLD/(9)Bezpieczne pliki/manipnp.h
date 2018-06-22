#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

ostream& comma(ostream &output)
{
	output << ", ";
	return output;
}

ostream& colon(ostream &output)
{
	output << ": ";
	return output;
}

istream& clearline(istream &input)
{
	while (input.get() != '\n' && input.peek() != EOF);
	return input;
}
#pragma once
