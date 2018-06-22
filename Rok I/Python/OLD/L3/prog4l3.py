from math import sqrt
def pierwsza(liczba):
    pomoc = sqrt(liczba)
    b = 0
    l = 2
    while l <= pomoc:
        reszta = liczba % l
        if reszta == 0:
            b = b + 1
        l = l + 1
    if b == 0:
        return 1
    else:
        return 0
def funkcja(ilosc_7,od,ile_liczb,gora_dol):
    z=0
    czyt = od
    while z < ile_liczb:
        if ilosc_7 * '7' in str(czyt):
            if pierwsza(czyt) == 1:
                print(czyt)
                z += 1
        if gora_dol=='gora':
            czyt = czyt + 1
        else:
            czyt = czyt - 1
funkcja(7,10000000000,2,'dol')

    

