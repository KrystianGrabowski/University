#klucz = 'aąbcćdeęfghijklmnoópqrstuvwxyzźż'

def cesar(tekst,k):
    A = []
    wynik = ''
    alf = 'aąbcćdeęfghijklmnoópqrstuvwxyzźż'
    for l in range(32):
        A.append(l)

    print(list(zip(A,alf)))
        

    return wynik.lower()
print(cesar('konserwa',1))






