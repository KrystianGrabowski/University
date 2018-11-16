import random
def drukowanie(a):
    for i in range(len(a)):
            if a[i]=='1':
                print("Wilk, koza i kapusta na pierwszym brzegu")
            if a[i]=='2':
                print("Wilk, koza i kapusta na drugim brzegu")
            if a[i]=='3':
                print("Wilk, kapusta i przewoznik na pierwszym brzegu. Koza na drugim brzegu")
            if a[i]=='4':
                print("Koza na pierwszym brzegu. Przewoznik, wilk, kapusta na drugim brzegu")
            if a[i]=='5':
                print("Wilk, koza i przewoznik na pierwszym brzegu. Kapusta na drugim")
            if a[i]=='6':
                print("Kapusta na pierwszym brzegu. Wilk, koza i przewoznik na drugim")
            if a[i]=='7':
                print("Kapusta, koza i przewoznik na pierwszym brzegu. Wilk na drugim")
            if a[i]=='8':
                print("Wilk na pierwszym brzegu. Koza, kapusta i przewoznik na drugim")
            if a[i]=='9':
                print("Koza i przewoznik na pierwszym brzegu. Wilk i kapusta na drugim brzegu")
            if a[i]=='10':
                print("Wilk i kapusta na pierwszym brzegu. Przewoznik i koza na drugim brzeg")

graph = {'1': set(['10']),
         '2': set(['9']),
         '3': set(['6','8','10']),
         '4': set(['5','7','9']),
         '5': set(['4','8']),
         '6': set(['3','7']),
         '7': set(['4','6']),
         '8': set(['3','5']),
         '9': set(['2','4']),
         '10': set(['1','3'])}

def srogunia(graph, start, end, droga=[]):
    droga = droga + [start]
    if start == end:
        return droga
    a=random.choice(list(graph[start]))
    if a == end:
        droga.append(a)
        return droga
    else:
        return srogunia(graph, a, end, droga)

b=(list(srogunia(graph, '1', '2')))

print(drukowanie(b))
