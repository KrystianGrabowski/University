#Przypadek gdy X<Y
#1.X0,Y0
#2.Xx,Yy
#3.X0,Yy
#4.Xx,Y0
#5.X0,Yx
#6.Xx,Yx
#7.Xx,Y(y-x)
#8.X0,Y(y-x)

X=int(input("Pierwsze wiadro: "))
Y=int(input("Drugie wiadro: "))
S=int(input("Suma jaka chcemy otrzymac: "))

graph = {'1': ((set(['3','4'])), 0),
         '2': ((set(['3','4'])), X+Y),
         '3': ((set(['2','1','7'])), Y),
         '4': ((set(['2','5'])), X), 
         '5': ((set(['4','1','6'])), X),
         '6': ((set(['5','4','2'])), 2*X),
         '7': ((set(['8','2','3'])), X+(Y-X)),
         '8': ((set(['7','1','3'])), Y-X)}
graph2 = {'1': ['3','4'],
         '2': ['3','4'],
         '3': ['2','1','7'],
         '4': ['2','5'], 
         '5': ['4','1','6'],
         '6': ['5','4','2'],
         '7': ['8','2','3'],
         '8': ['7','1','3']}
def drukowanie(b):
    if b == None:
        return "nie da sie zrobic"
    for i in range(len(b)):
            if b[i]=='1':
                print("Wiadro 1:",0, "Wiadro drugie:",0)
            if b[i]=='2':
                print("Wiadro 1:",X, "Wiadro drugie:",Y)
            if b[i]=='3':
                print("Wiadro 1:",0, "Wiadro drugie:",Y)
            if b[i]=='4':
                print("Wiadro 1:",X, "Wiadro drugie:",0)
            if b[i]=='5':
                print("Wiadro 1:",0, "Wiadro drugie:",X)
            if b[i]=='6':
                print("Wiadro 1:",X, "Wiadro drugie:",X)
            if b[i]=='7':
                print("Wiadro 1:",X, "Wiadro drugie:",Y-X)
            if b[i]=='8':
                print("Wiadro 1:",0, "Wiadro drugie:",Y-X)

L=sorted(list(graph.keys()))
for i in range(len(graph)):
    if S in graph[L[i]]:
        a = str(L[i])
        break
  
def dfs(graph, start, end, path=[]):
        path = path + [start]
        if start == end:
            return path
        shortest = None
        for node in graph[start]:
            if node not in path:
                newpath = dfs(graph, node, end, path)
                if newpath:
                    if not shortest or len(newpath) < len(shortest):
                        shortest = newpath
        return shortest


w=list(dfs(graph2, '1', a))
print(drukowanie(w))




