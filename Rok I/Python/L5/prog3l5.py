from operator import itemgetter
L=[341,24,24,123,123]
def only_one_v2(L):
    L1 = []
    for x in range(len(L)):
        L1.append((L[x], x))
    L1.sort()    
    L2 = []
    a0 = L1[0]
    a = a0[0]
    L2.append(a0)
    for i in L1[1:]:
        if a != i[0]:
            a = i[0]
            L2.append(i)

    L2.sort(key = itemgetter(1))
    print(L2)
    L3 = [ ]
    for j in L2:
        k = itemgetter(0)(j)
        L3.append(k)
    print(L3)        
                
only_one_v2(L)
