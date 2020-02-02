from turtle import*
from random import *
speed('fastest')
def kwadrat(bok):
    #fillcolor(random(),random(),random())
    L=[(1,1,0), (0,1,0), (0,0,1), (1,0,0)]
    fillcolor(choice(L))
    begin_fill()
    for i in range(4):
        fd(bok)
        rt(90)
    end_fill()
    fd(bok)

def szachownica(wymiar,bok):
    for j in range (wymiar): 
        for i in range(wymiar):
            kwadrat(bok)
        bk(wymiar*bok)
        rt(90)
        fd(bok)
        lt(90)

szachownica(10,10)
        
        
        
    
