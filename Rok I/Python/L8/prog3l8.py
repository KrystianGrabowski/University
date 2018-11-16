def isperm(w1, w2):
    slow1 = {}
    for i in w1:
        l = 0
        for j in w1:
            if i == j:
                l = l + 1
        slow1[i]=l
    slow2 = {}
    for i in w2:
        l = 0
        for j in w2:
            if i == j:
                l = l + 1
        slow2[i]=l
    print(slow1,slow2)
    if slow1==slow2:
        print("w1 jest permutacją z w2")
    else:
        print("w1 NIE JEST permutacją z w2")
        
        
isperm("kajak","ajkak")
