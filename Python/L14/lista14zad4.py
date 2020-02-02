
#a
def prefix(s,t):
    return s == t[0:len(s)]
print('a',prefix('kol','kolejka'))

#b
def drabina(L):
    return len(set(L)) == 1 or len(set(L)) == 2 and all([False for i in range(len(L)-1) if L[i]==L[i+1]])

print('b0',drabina([1,2,1,2,2,2,1]))
print('b1',drabina([1,1,1,1,1,1]))
print('b2',drabina([1,2,1,2,1,2,1,2])) #dwie powtarzające sie wartośći występująće na zmianę


#c
def maleRybyWDuzych(L):
    return len([1 for i in L for j in L if i in j and j!=i]) >= len(L)

print('cT',maleRybyWDuzych(['rekinisko', 'rekin', 'eki','megarekinisko', 'megarekiniskozilla']))    
print('cF',maleRybyWDuzych(['karp', 'karpik' , 'płotka', 'sum'] ))

#d
def sumaDlugosciABC(L):
    return sum([len(i) for i in L if i.count("a")+i.count("b")+i.count("c")==len(i)])
print('d',sumaDlugosciABC(['baba', 'ma', 'kota', 'a', 'ty?']))

#e
def poltaksowkowa(N): #zakladam że 0 należy do naturalnych 
    return any([True for i in range(int(N**(1/3)+2)) for j in range(int(N**(1/3)+2)) if j**3 + i**3 == N])
print('e0',poltaksowkowa(27))

#jeśli ma być od 1:

def poltaksowkowa(N): # 0 nie należy do naturalnych
    return any([True for i in range(1,int(N**(1/3)+2)) for j in range(1,int(N**(1/3)+2)) if j**3 + i**3 == N])
print('e1',poltaksowkowa(27))
