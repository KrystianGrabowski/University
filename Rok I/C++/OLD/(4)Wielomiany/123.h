#include <iostream>
using namespace std;
class wielomian
{
private:
int n; // stopie� wielomianu
double *a; // wsp�czynniki wielomianu

public:
wielomian (int st=0, double wsp=1.0); // konstruktor tworz�cy jednomian
wielomian (int st, const double wsp[]); // konstruktor tworz�cy wielomian
wielomian (initializer_list<double> wsp); // lista wsp�czynnik�w
wielomian (const wielomian &w); // konstruktor kopij�cy
wielomian (wielomian &&w); // konstruktor przenosz�cy
wielomian& operator = (const wielomian &w); // przypisanie kopij�ce
wielomian& operator = (wielomian &&w); // przypisanie przenosz�ce

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

double operator () (double x) const; // obliczenie warto�ci wielomianu w x-sie
double operator [] (int i) const; // odczytanie i-tego wsp�czynnika
};

