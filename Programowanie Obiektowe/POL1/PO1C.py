Zesp = [(4,-7,'i'), (-3,2,'i')]
def dodaj(a, b):
    c = a[0] + b[0]
    d = a[1] + b[1]
    return (c, d, 'i')
def odejmij(a, b):
    c = a[0] - b[0]
    d = a[1] - b[1]
    return (c, d, 'i')
def mnoz(a, b):
    c = a[0] * b[0] - a[1] * b[1]
    d = a[0] * b[1] + a[1] * b[0]
    return (c, d, 'i')
def dziel(a, b):
    c = a[0] * b[0] - a[1] * (-b[1])
    d = a[0] * (-b[1]) + a[1] * b[0]
    e = b[0] * b[0] + b[1] * b[1]
    return (c/e, d/e, 'i')

def Zespolone(Zesp, operacja, ktore):
    x = Zesp[ktore[0]]
    y = Zesp[ktore[1]]
    if operacja == 'dodaj':
        return dodaj(x,y)
    elif operacja == 'odejmij':
        return odejmij(x, y)
    elif operacja == 'mnoz':
        return mnoz(x, y)
    elif operacja == 'dziel':
        return dziel(x, y)
    else:
        print("Bledna operacja!")


print(Zespolone(Zesp, 'dodaj', (0,1)))
print(Zespolone(Zesp, 'odejmij', (0,1)))
print(Zespolone(Zesp, 'mnoz', (0,1)))
print(Zespolone(Zesp, 'dziel', (0,1)))
