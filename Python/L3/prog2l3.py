from turtle import*
def funkcja(dlugosc,ilosc,odstep,szybkosc_powiekszania):
    for i in range(ilosc):
        for j in range(4):
            fd(dlugosc)
            rt(90)
        if i != ilosc - 1:
            pu()
            lt(90)
            fd(odstep)
            lt(90)
            fd(odstep)
            dlugosc=dlugosc+(2 * odstep)
            rt(180)
            pd()
            odstep = odstep * szybkosc_powiekszania
         

            
funkcja(50,10,4,1.1)
        
