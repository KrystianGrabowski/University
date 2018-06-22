from itertools import*
lista = [1,2,3,100]
i = 1
M = []
W = []
W2 = []

def cz1(L, i, dl):
    if i == dl:
        s = [sum(L)]
        M.append(s)
    else:
        a = list(combinations(L, i))
        M.append([sum(i) for i in a])
        return cz1(L, i+1, dl)
    P = set(sorted([c for i in M for c in i]))
    return(P)


def cz2(N, A, B):
    if B - A < N - 1:
        return W2
    else:
        c = [i for i in range(A, A + N)]
        W2.append(c)
        return cz2(N, A+1, B)
        




print(cz1(lista, 1, 4))
print()
[print(g) for g in cz2( 10, 1, 30 )]

