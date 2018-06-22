from turtle import*
from random import*
speed("fastest")
def Kwadrat(kolor):
    fillcolor(kolor)
    begin_fill()
    for i in range(4):
        fd(10)
        rt(90)
    fd(10)
    end_fill()
def Duze(n):
    from duze_cyfry import dajCyfre
    dajCyfre(3)
    d=len(str(n))
    m=[]
    t=[]
    while n>0:
        m.append(n%10)
        n=n//10
    print(m)
    dl=d-1
    while dl>=0:
        t.append(m[dl])
        dl-=1
        
    print(t)
        
    p1=1
    p2=0
    for l in range (d):
        kolor=random(),random(),random()
        p=1
        for r in dajCyfre(t[l]):
            for i in range(5):
                if r[i]=="#":
                    Kwadrat(kolor)
                else:
                    pu()
                    fd(10)
                    pd()
            pu()
            goto(p2*60,0)
            rt(90)
            fd(10*p)
            lt(90)
            pd()
            p+=1
        pu()
        goto(0,0)
        fd(60*p1)
        pd()
        p1+=1
        p2+=1
		


Duze(12345)





