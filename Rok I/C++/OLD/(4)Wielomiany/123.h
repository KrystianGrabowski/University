#include <iostream>
using namespace std;
class wielomian
{
private:
int n; // stopieñ wielomianu
double *a; // wspó³czynniki wielomianu

public:
wielomian (int st=0, double wsp=1.0); // konstruktor tworz¹cy jednomian
wielomian (int st, const double wsp[]); // konstruktor tworz¹cy wielomian
wielomian (initializer_list<double> wsp); // lista wspó³czynników
wielomian (const wielomian &w); // konstruktor kopij¹cy
wielomian (wielomian &&w); // konstruktor przenosz¹cy
wielomian& operator = (const wielomian &w); // przypisanie kopij¹ce
wielomian& operator = (wielomian &&w); // przypisanie przenosz¹ce

~wielomian (); // destruktor

friend istream& operator >> (istream &we, wielomian &w);
friend ostream& operator << (ostream &wy, const wielomian &w);

friend wielomian operator + (const wielomian &u, const wielomian &v);
friend wielomian operator - (const wielomian &u, const wielomian &v);
friend wielomian operator * (const wielomian &u, const wielomian &v);
friend wielomian operator * (const wielomian &u, double c);

wielomian& operator += (const wielomian &v);
wielomian& operator -= (const wielomian &v);
wielomian& operator *= (const wielomian &v);
wielomian& operator *= (double c);

double operator () (double x) const; // obliczenie wartoœci wielomianu w x-sie
double operator [] (int i) const; // odczytanie i-tego wspó³czynnika
};

