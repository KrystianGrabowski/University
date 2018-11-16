def pierwsza(liczba):
    pomoc=liczba // 2
    b = 0
    l = 2
    while l <= pomoc:
        reszta = liczba % l
        if reszta == 0:
            return False
        l = l + 1
    return True
        

czyt = 2
licznik = 0
while czyt < 100000:
    if "777" in str(czyt):
        if pierwsza(czyt):
            print(czyt)
            licznik=licznik + 1
    czyt = czyt + 1
print("Liczb szczesliwych jest", licznik)    
    


