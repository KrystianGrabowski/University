def tabliczka(x1, x2, y1, y2):
    print(" ", end=" ")
    for i in range (x1,x2 + 1):
        print(i,end = "  ")
    for j in range (y1, y2 + 1):
        print()
        print(j, end = " ")
        for k in range (x1, x2 + 1 ):
            if k*j < 10 :
                print(k*j, end = "  ")
            else : 
                print(k*j, end = " ")
tabliczka(3,9,2,4)
