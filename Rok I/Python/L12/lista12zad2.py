import random
#1. K,KO,W,P 2.       (start na pierwszym brzegu)
#2.          2.K,Ko,W,P(koiec na drugim brzegu)
#3. W,K,P    2.KO
#4. KO       2.W.K.P
#5. W,KO,P   2.K
#6. K        2.W,KO,P
#7. Ko,K,P   2.W
#8. W        2.KO,K,P
#9. KO,P     2.W,K
#10.W,K      2.KO,P

#w reszcie stanow nastapi konsumpcja

def drukowanie(a):
    for i in range(len(a)):
        print("Droga", i+1, ": ")
        for j in range(len(a[i])):
            if a[i][j]=='1':
                print("Wilk, koza i kapusta na pierwszym brzegu")
            if a[i][j]=='2':
                print("Wilk, koza i kapusta na drugim brzegu")
            if a[i][j]=='3':
                print("Wilk, kapusta i przewoznik na pierwszym brzegu. Koza na drugim brzegu")
            if a[i][j]=='4':
                print("Koza na pierwszym brzegu. Przewoznik, wilk, kapusta na drugim brzegu")
            if a[i][j]=='5':
                print("Wilk, koza i przewoznik na pierwszym brzegu. Kapusta na drugim")
            if a[i][j]=='6':
                print("Kapusta na pierwszym brzegu. Wilk, koza i przewoznik na drugim")
            if a[i][j]=='7':
                print("Kapusta, koza i przewoznik na pierwszym brzegu. Wilk na drugim")
            if a[i][j]=='8':
                print("Wilk na pierwszym brzegu. Koza, kapusta i przewoznik na drugim")
            if a[i][j]=='9':
                print("Koza i przewoznik na pierwszym brzegu. Wilk i kapusta na drugim brzegu")
            if a[i][j]=='10':
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

def dfs_paths(graph, start, goal):
    stack = [(start, [start])]
    while stack:
        (vertex, path) = stack.pop()
        for next in graph[vertex] - set(path):
            if next == goal:
                yield path + [next]
            else:
                stack.append((next, path + [next]))


a=(list(dfs_paths(graph, '1','2')))     

print(drukowanie(a))


