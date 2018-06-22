from string import*
alf = 'aąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż'
ALF = alf.upper()
def Przekaz(x):
    napis=''
    l = 0
    przekaz = ''
    zdanie = ''
    slownik = {}
    zn=[]
    for wiersz in open(x).read().split():
        if wiersz[0] in ALF or alf:
            napis = napis + wiersz[0]
            napis = napis.lower()
            slownik[l] = wiersz
            l += 1
    for w in open('slowa.txt', encoding='utf8').read().split():
        if w in napis and 11>len(w)>2:
            zn.append(w)
    zn = set(zn)
    for i in zn:
        if len(i)>len(przekaz):
            przekaz = i
    print(przekaz)
    maks = len(napis)
    a = napis.find(przekaz)
    g = len(przekaz)
    if a < 3:
        p = 0
    else:
        p  = a - 3
    if maks - a + g < 3:
        k = maks
    else:
        k = a + g + 3
    for r in range(p, k):
        zdanie += slownik[r]+' '
    print(zdanie)
Przekaz("fragment.txt")
