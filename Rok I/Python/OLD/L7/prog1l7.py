import string
a="aąbcćdeęfghijklłmnoópqrsśtuvwxyzźż"
def zliczanie(x):
    w = {}
    for i in a:
        w[i] = 0
    for i in x:
        l = 0
        for j in x:
            if i == j:
                l = l + 1
        w[i] = l
    return w
    
def program(sl1, sl2):
    w2=zliczanie(sl2)
    w1=zliczanie(sl1)    
    for c in sl2:
        if w2[c] > w1[c]:
            return print("Słowo",sl1,"NIE jest układalne ze słowa",sl2)
    return print("Słowo",sl1,"JEST układalne ze słowa",sl2)       
program("lokomotywa","motyl")

    
