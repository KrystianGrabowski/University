Kolekcja = ['łoś', 123, 'ryjówka',[1,2,3], 'lis', 123, 'żubr']

def rozmiar(Kolekcja):
    return len(Kolekcja)

def szukaj(Kolekcja, Elem):
    i = 0
    for e in Kolekcja:
        if e == Elem:
            i+=1
    return i

def wstaw(Kolekcja, Elem):
    d = len(Kolekcja)
    Kolekcja[d:d] = [Elem]
    return None

def torba (Kolekcja, czynnosc, elem):
    if czynnosc == 'wstaw':
        wstaw(Kolekcja, elem)
    elif czynnosc == 'dlugosc':
        return rozmiar(Kolekcja)
    elif czynnosc == 'szukaj':
        return szukaj(Kolekcja, elem)
    else:
        print("Bledne polecenie")

print(Kolekcja)
torba(Kolekcja, 'wstaw','NOWYELEMENT')
print(Kolekcja)
print(torba(Kolekcja, 'szukaj', 123))
print(torba(Kolekcja, 'dlugosc', 0))
