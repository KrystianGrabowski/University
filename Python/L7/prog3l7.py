from turtle import*
import linecache
BOK = 10
tracer(1,delay=0)
speed('fastest')
count = len(open('1.txt', 'rU').readlines())
for j in range(1,count+1):
    l = linecache.getline('1.txt', j)
    l = l.strip().split()
    d=len(l)
    for i in range(d):
        colormode(255)
        a = l[i]
        a = a.strip("()")
        a = a.split(",")
        a[0]=float(a[0])
        a[1]=float(a[1])
        a[2]=float(a[2])
        kolor=(int(a[0]), int(a[1]), int(a[2]))
        fillcolor(kolor)
        begin_fill()
        for i in range(4):
            fd(BOK)
            rt(90)
        fd(BOK)
        end_fill()
    pu()
    goto(0, 0)
    pd()
    rt(90)
    fd(j * BOK)
    lt(90)

