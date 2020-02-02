def czestotliwosc(ang):
    p=0
    l={}
    for i in ang:
        for w in open('brown.txt').read().split():
            if w==i:
                p=p+1
        l[i]=p
    maks=0
    for j in l:
        a=l[j]
        a=int(a)
        if a>maks:
            wynik=j
    return wynik        

pol_ang = {} # pusty slownik

pol_ang['dziewczyna'] = 'girl','maid'
pol_ang['chłopiec'] = 'boy'
pol_ang['dom'] = 'house'
pol_ang['samochód'] = 'char'
pol_ang['dom'] = 'home'
print(pol_ang)
for pol,ang in pol_ang.items():
    print (pol,'najczesciej tlumaczymy na', czestotliwosc(ang))
