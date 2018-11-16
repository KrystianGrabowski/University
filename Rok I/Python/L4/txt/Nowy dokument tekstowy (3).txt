from math import sqrt
def pierwsza(liczba):
    pomoc = sqrt(liczba)
    b = 0
    l = 2
    while l <= pomoc:
        reszta = liczba % l
        if reszta == 0:
            b = b + 1
        else: return False    
        l = l + 1
    if b == 0:
        return True
def funkcja(od,do):
    z=0
    czyt = od
    while czyt < do:
        if '7777777' in str(czyt):
            if czyt%2>0 and czyt%3>0 and czyt%5>0 and czyt%7>0:
                if pierwsza(czyt) == True:
                    z=z+1
                    print(z)        
        czyt=czyt+1
print(funkcja(1007777777,10000000000))
    

