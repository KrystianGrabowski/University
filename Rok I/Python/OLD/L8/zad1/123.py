import random

pol_ang = {}
wl = [1,0]
def brown(ang):
    o = 0
    p = 0
    for k in ang:
        for w in open('brown.txt').read().split():
            if k==w:
                p=p+1
        if p > o:
          o = p
          p = 0
          wynik = k
        if p == o:
          w = choice(wl)
          if w == 1:
            wynik = k
    return wynik
  
for x in open('pol_ang.txt',encoding='utf8'):
  x = x[:-1]
  wiersz = x.split('=')
  if len(wiersz) != 2:
    continue
  pol,ang = wiersz
  
  if not pol in pol_ang:
    pol_ang[pol] = []
  pol_ang[pol].append(ang)
  
def tlumacz(L):
  wynik = []
  for w in L:
    if w in pol_ang:
      wynik.append(brown(pol_ang[w]))
    else:
      wynik.append('?' + w)
  return wynik
  
    
for wiersz in open('tekst.txt'):
  wiersz = wiersz.split()
  print (' '.join(tlumacz(wiersz)))
