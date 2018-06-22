def pot(a, b):
    print(a)
    if not b:
        return 1
    if b%2:
        return a*pot(a*a,b//2)
    return pot(a*a,b//2)
print(pot(2,17))
