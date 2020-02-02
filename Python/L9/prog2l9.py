from turtle import*
from random import*
speed('fastest')
lt(90)
pu()
bk(200)
pd()
def drzewo(dl):
    a = randrange(15, 30)
    print(dl)
    if dl < 30:
        return 0
    else:
        fd(dl)
        rt(a)
        drzewo(dl - 10)
        lt(2 * a)
        drzewo(dl - 10)
        rt(a)
        bk(dl)

drzewo(100)
