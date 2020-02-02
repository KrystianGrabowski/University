from turtle import *

speed('fastest')

BOK = 20

def kwadrat(bok, kolor):
    
    fillcolor(kolor)
    #pencolor(kolor)
    begin_fill()
    for i in range(4):
        fd(bok)
        rt(90)  
    end_fill()  

def mieszanina(k1, k2, a):
    #r1,g1,b1 = k1
    r1 = k1[0]
    g1 = k1[1]
    b1 = k1[2]
  
    r2,g2,b2 = k2
  
    r3 = (1-a) * r1 + a * r2
    g3 = (1-a) * g1 + a * g2
    b3 = (1-a) * b1 + a * b2
  
    return (r3,g3,b3)

def liczba(l):
    p= l
    for k in range(l):
        p = p +(l - 1)
        l = l - 1
    return(p)

def murek(l, k1, k2):
    kolor = k1
    N = liczba(l)
    pozycja = 0
    p = 1
    h = 0
    o = 1
    for x in range (N):
        if h == o + p:
            rt(90)
            fd(BOK)
            o=h
            p=p+1
        a = pozycja / N
        kwadrat(BOK, mieszanina(k1,k2, a))
        pozycja += 1
        fd(BOK)
        h=h+1

murek(18, ((1,1,0)), (1,0,0.4) )
