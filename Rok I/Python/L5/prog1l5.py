def F(n):
    if n%2 == 0:
        return n / 2
    else:
        return 3 * n + 1
l = []
def ciag(n):
    l.append(n)
    i = 1
    en = 0
    while n != 1:
        l.append(F(n))
        n = F(n)
        i += 1
        en += 1
    return en
def analizaCollatza(a,b):
    sredia_energia = 0
    mediana = 0
    maks = 0
    mini = 0
    l = 0
    l1=[]
    for j in range(a, b + 1):  #dodawnie do tablicy
        l1.append(ciag(j))
        l += 1

    for i in range(l): #srednia energia
        sredia_energia = sredia_energia + l1[i]
    sredia_energia = sredia_energia / l
    print('Srednia energia = ',sredia_energia)

    l1.sort()
    mini = l1[0]
    maks = l1[l - 1]
    print('max = ',maks)
    print('min = ',mini)
    if l%2==0:
        w0 = int(l / 2) - 1
        w1 = w0+1
        w = (l1[w0] + l1[w1]) / 2
        mediana = int(w)
    else:
        w0 = int(((l+1)/2)-1)
        mediana = l1[w0]
    print("mediana = ", mediana)
    
analizaCollatza(7,9)
    
        
    

    
    
