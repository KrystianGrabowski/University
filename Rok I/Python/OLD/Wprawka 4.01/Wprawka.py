tab1 = []
tab2 = []
tab3 = []
l = 1
TAB = tab1

for wiersz in open("definicja.txt"):
    for i in wiersz.split():
        TAB.append(int(i))
    l += 1
    if l == 2 :
        TAB = tab2
    elif l == 3 :
        TAB = tab3


def wyrazy_ciagu(T, tab2, tab3):
    Wyniki = []
    maks = tab3[0]
    for k in tab3:
        if k > maks:
            maks = k
    for n in range(len(T), maks + 1):
        T.append(0)
        poz = 1
        for wart in tab2:
            T[n] += wart * T[n - poz]
            poz += 1
    for w in tab3:
        Wyniki.append(T[w])
    return Wyniki

print(wyrazy_ciagu(tab1, tab2, tab3))
            
        
