#include <iostream>
#include <cstdlib>
#include "bufor.h"


std::ostream& operator<<(std::ostream &W, const Lista &E)
{
    if(E.Pierwszy)
    {
        W << "Lista: ";
        Lista::Wezel *P = E.Pierwszy;
        while(P)
        {

            W << P->Wartosc << " ";
            P = P->Nastepny;
        }
    }

    else
        W << "Pusta" << "\n";
    W << "\n";
    return W;

}

Lista::Lista(const Lista &E)
{
    Rozmiar = E.Rozmiar;
    Wezel *Obkt = E.Pierwszy;
    Pierwszy = new Wezel(*Obkt);
    Wezel *Ob = Pierwszy;
    while(Obkt)
    {
        Ob->Nastepny = new Wezel(*Obkt->Nastepny);
        Obkt = Obkt->Nastepny;
        Ob = Ob->Nastepny;

    }

}
Lista::Lista(Lista &&E)
{
    Rozmiar = E.Rozmiar;
    E.Rozmiar = 0;
    Pierwszy = E.Pierwszy;
    E.Pierwszy = nullptr;

}

Lista & Lista::operator = (const Lista &E)
{
    if (this != &E)
    {
    Rozmiar = E.Rozmiar;
    Wezel *Obkt = E.Pierwszy;
    Pierwszy = new Wezel(*Obkt);
    Wezel *Ob = Pierwszy;
    while(Obkt)
    {
        Ob->Nastepny = new Wezel(*Obkt->Nastepny);
        Obkt = Obkt->Nastepny;
        Ob = Ob->Nastepny;
    }
    }

    return *this;
}

Lista& Lista::operator =(Lista &&E)
{
    if (this != &E)
    {
    Rozmiar = E.Rozmiar;
    E.Rozmiar = 0;
    Pierwszy = E.Pierwszy;
    E.Pierwszy = nullptr;
    }
    return *this;
}

const unsigned int W = 999;

Lista::Wezel Tablica[W];
bool Tablica_PF[W]{};

void* Lista::Wezel::operator new(size_t MemSize)
{
    for(int i=0; i<W; ++i)
    {
        if(!Tablica_PF[i])
        {
            Tablica[i] = Lista::Wezel();
            Tablica_PF[i] = true;
            return (Tablica + i);
        }
    }
    return nullptr;
}

void Lista::Wezel::operator delete(void* _Usuwany)
{
    Lista::Wezel *Usuwany = reinterpret_cast<Lista::Wezel*>(_Usuwany);

    for(int i=0; i<W; i++)
    {
        if(Usuwany == Tablica + i)
        {
            Tablica_PF[i] = false;

        }

    }

}


Lista::Wezel* Lista::ElPocz()
{
    return Pierwszy;
}

Lista::Wezel* Lista::ElKon()
{
    return Ostatni;
}

Lista::Lista() : Pierwszy(nullptr), Ostatni(nullptr), Rozmiar(0) {;}

void Lista::Dodaj(int Indeks, double Wartosc)
{

    if (Indeks > Rozmiar + 1 || Indeks < 0)
    {

        std::cout << "Bledny indeks" << "\n";
        return;
    }

    Wezel *Nowy = new Wezel;
    Nowy->Wartosc = Wartosc;


    if (Pierwszy)
    {

        if (Indeks == 0)
        {
            Nowy->Nastepny = Pierwszy;
            Pierwszy->Poprzedni = Nowy;
            Pierwszy = Nowy;
        }
        else if (Indeks == Rozmiar)
        {

            Nowy->Poprzedni = Ostatni;
            Ostatni->Nastepny = Nowy;
            Ostatni = Nowy;


        }
        else
        {
            Wezel *P = Pierwszy;
            while(P->Nastepny && Indeks)
            {
                P = P->Nastepny;
                --Indeks;
            }
            Wezel *P_pop = P->Poprzedni;
            P_pop->Nastepny = Nowy;
            Nowy->Poprzedni = P_pop;
            Nowy->Nastepny = P;
            P->Poprzedni = Nowy;


        }

    }
    else
    {
        Pierwszy = Nowy;
        Ostatni = Nowy;
    }
    ++Rozmiar;
}

bool Lista::Usun(int Indeks)
{
    if(!Rozmiar)
    {
        std::cout << "Pusta" << "\n";
        return false;
    }
    if (Indeks >= Rozmiar || Indeks<0)
    {
        std::cout << "Bledny Indeks" << "\n";
        return false;
    }
    if(Rozmiar == 1)
    {
        delete Pierwszy;
        Pierwszy = nullptr;
        Ostatni = nullptr;
    }
    else
    {
        if(Indeks == 0)
        {
            Wezel *Usuwany = Pierwszy;
            Pierwszy = Pierwszy->Nastepny;
            Pierwszy->Poprzedni = nullptr;
            delete Usuwany;
        }
        else if (Indeks == Rozmiar - 1)
        {
            Wezel *Usuwany = Ostatni;
            Ostatni = Ostatni->Poprzedni;
            Ostatni->Nastepny = nullptr;
            delete Usuwany;
        }
        else
        {
            Wezel *P = Pierwszy;
            while(P->Nastepny && Indeks)
            {
                P = P->Nastepny;
                --Indeks;
            }
            Wezel *Usuwany = P;
            P->Poprzedni->Nastepny = P->Nastepny;
            P->Nastepny->Poprzedni = P->Poprzedni;
            delete Usuwany;
        }

    }
    --Rozmiar;
    return true;
}

void Lista::Wypisz()
{
    if(Pierwszy)
    {
        Wezel *P = Pierwszy;
        while (P)
        {
            std::cout << P->Wartosc << " ";
            P = P->Nastepny;
        }

    }
    else
    {
        std::cout << "Pusta" << "\n";
    }
}

bool Lista::Pusta()
{
    return !Rozmiar;
}
int Lista::Rozmiar_W()
{
    return Rozmiar;
}
double Lista::Przod()
{
    if (Rozmiar)
    {
        return Pierwszy->Wartosc;
    }
    return 0;
}
double Lista::Tyl()
{
    if (Rozmiar)
    {
        return Ostatni->Wartosc;
    }
    return 0;
}
Lista::~Lista()
{
    if(Pierwszy)
    {
        Wezel* Pam = Pierwszy;
        while(Pam)
        {
            delete Pam;
            Pam = Pam->Nastepny;
        }

    }

    Pierwszy = nullptr;
    Ostatni = nullptr;
    Rozmiar = 0;

}


void Kolejka::operator +=(double Wartosc)
{
    Dodaj(Rozmiar_W(), Wartosc);
}
bool Kolejka::operator--()
{
    return Usun(0);
}
void Kolejka::Wypisz()
{
    std::cout << "Kolejka: ";
        if (ElPocz())
        {
            Wezel *P = ElPocz();
            while(P)
            {
                std::cout << P->Wartosc << " ";
                P = P->Nastepny;
            }
        }
        else
            std::cout << "Pusta"<< "\n";

}
Lista::Wezel* Kolejka::GT()
{
    return ElPocz();
}
Lista::Wezel* Kolejka::operator*()
{
    return ElPocz();
}



void Stos::operator +=(double Wartosc)
{
    Dodaj(Rozmiar_W(), Wartosc);
}

bool Stos::operator--()
{
    return Usun((Rozmiar_W()) - 1);
}

void Stos::Wypisz()
{
    std::cout << "Stos: ";
    if (ElKon())
    {
        Wezel *P = ElKon();
        while(P)
        {
            std::cout << P->Wartosc << " ";
            P = P->Poprzedni;

        }
    }
    else
        std::cout << "Pusty" << "\n";

}
Lista::Wezel* Stos::GT()
{
    return ElKon();
}
Lista::Wezel* Stos::operator*()
{
    return ElKon();
}






















