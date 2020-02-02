alf = "aąbcćdeęfghijklłmnńoóprsśtuwyzźż"
def ceasar(s, k):
    slownik = {}
    slownik1 = {}
    l=0
    for i in alf:
        slownik[i]=l
        l+=1
    print(slownik)
    slownik1=slownik
    res=list(zip(slownik,slownik1))
    print(res)





ceasar("kanapka",5)
