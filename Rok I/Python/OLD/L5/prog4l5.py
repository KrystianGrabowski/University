from turtle import *

speed('fastest')

BOK = 20
K=[(1,1,0),(0,1,0),(0,0,1),(1,0,0)]

def kwadrat(bok, kolor):
    fillcolor(kolor)
    begin_fill()
    for i in range(4):
        fd(bok)
        rt(90)
    end_fill()  

    

def murek(prog, kolory):
    for x in prog:
        if x == 'f':
            kwadrat(BOK,kolor)
            fd(BOK)
        elif x == 'r':
            rt(90)
            fd(BOK)
        elif x == 'l':
            bk(BOK)
            lt(90)
        elif x == 'u':
            pu()
        elif x == 'd':
            pd()
        elif x == 'b':
            bk(BOK)      
        else :
            x=int(x)
            kolor = kolory[x]
    
murek((4*"0fffff1fffffubbbbbbbbbbrd"),K )
  
