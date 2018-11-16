from random import*
def maks(x):
    slow = {}
    for i in x:
        w = 0
        try:
            l = int(slow[i])
            l += 1
            slow[i] = l
        except Exception:
            slow[i] = 1
    maksym = 0
    for i in slow:
        if int(slow[i])> maksym:
            maksym = slow[i]
            wyn = i
    return wyn 
    
def imie(pocz):
    tab = []
    napis = pocz
    dlugosc = randint(4,10)
    for i in range(2,dlugosc):
        for x in open("imiona.txt").read().split():
            f = napis[i-2] + napis[i-1]
            if f in x:
                try:
                    tab.append(x[x.index(f) + 2])
                except Exception:
                    continue
        napis += maks(tab)
        tab = []
    return napis
          
print(imie('ma'))    
