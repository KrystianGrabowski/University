import itertools
from random import*
def randperm(lista,ile_permutacji):
    L=[]
    d=len(lista)
    permutacje = itertools.permutations(lista, d)
    for p in (permutacje):
        L.append(p)
    for i in range(ile_permutacji):    
        a=choice(L)
        print(a)
randperm([0,1,2,3,4,5,6,7,8,9],10)
