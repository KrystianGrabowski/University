from turtle import fd, rt, lt, bk, speed, pu, pd, pensize
def rysunek(dlugosc):
    for i in range (10):
        fd(dlugosc)
        for i in range (10):
            fd(dlugosc / 5)
            bk(dlugosc / 5)
            rt(360 / 10)
        bk(dlugosc)
        rt(360 / 10)
rysunek(200)
