from time import clock

def pierwsze_funkcyjna(n):
	return list(filter(lambda x: (list(filter(lambda y: (x%y == 0) and (x != y), range(2, x//2 +1)))) == [] , range(2, n+1)))

def pierwsze_skladane(n):
	return [l for l in range(2,n + 1) if ([i for i in range (2,l//2 + 1) if l%i == 0]) == []]

#######V2

def is_prime(x):
	for i in range(2,x//2+1):
		if (x % i == 0):
			return False;
	return True; 

def pierwsze_funkcyjna2(n):
	return list(filter(is_prime,range(2,n+1)))



temp1 = clock()
print(pierwsze_funkcyjna(100)) #real	0m5.184s
print(clock() - temp1)

temp = clock()
print(pierwsze_skladane(100)) #real	0m2.435s
print(clock() - temp)




















"""def pierwsze_funkcyjna(n):
	pierwsza = True
	Lista_pierwszych = []
	
	for i in range(2, n+1):
		for j in range(2, i // 2 + 1):
			if (i % j == 0):
				pierwsza = False
				
		if (pierwsza):
			Lista_pierwszych.append(i)
		pierwsza = True
	return Lista_pierwszych

def pierwsze_funkcyjna2(n):
	Liczby = range(2,n+1)
	for i in range(2, n//2 + 1):
		Liczby = filter(lambda x: (x%i != 0) or (i == x), Liczby)
"""
