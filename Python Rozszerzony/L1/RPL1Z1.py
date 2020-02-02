import random

def rzut_kostka():
    return random.randint(1,6)

def prosta_gra(n):
    punkty_zawodnik1 = 0
    punkty_zawodnik2 = 0
    i = 0
    while i != n:
        rzut1 = rzut_kostka()
        rzut2 = rzut_kostka()
        print(rzut1, rzut2)
        if rzut1 > rzut2 :
            punkty_zawodnik1 += 1
        elif rzut2 > rzut1 :
            punkty_zawodnik2 += 1
        print("bilans -> ", punkty_zawodnik1, punkty_zawodnik2)
        print("=================")
        if punkty_zawodnik1 == punkty_zawodnik2 and i == n-1 :
               print ("Dogrywka")
        else:
            i += 1
        

prosta_gra(100)

