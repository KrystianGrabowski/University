#klucz = 'aąbcćdeęfghijklmnoópqrstuvwxyzźż'

def cesar(tekst,k):
    wynik = ''
    alf = 'aąbcćdeęfghijklmnoópqrstuvwxyzźż'
    for l in tekst.lower():
        try:
            i = (alf.index(l) + k) % 32
            wynik += alf[i]
        except ValueError:
            wynik += l

    return wynik.lower()







