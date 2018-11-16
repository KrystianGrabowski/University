def przeksztalc(slowo):
    pomoc = []
    wynik = []
    final = ""
    for i in slowo:
        if i not in wynik:
            pomoc.append(i)
    print(pomoc)
    
    for x in slowo:
        wynik.append(pomoc.index(x) + 1)
    print(wynik)

    for q in range(len(wynik)):
        if q == (len(wynik) - 1):
            final += str(wynik[q])
        else:
            final += str(wynik[q])
            final += "-"


    return final
        



print(przeksztalc("abrakadabra"))
