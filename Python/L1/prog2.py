def silnia(n):
    if n>1:
        return  n * silnia(n-1)
    else:
        return 1

for i in range(100):
	zamiana=str(silnia(i+1))
	ilosc_cyfr=len(zamiana)
	print(i+1,"! ma ",ilosc_cyfr," liczby")
