from functools import *
from time import clock

def doskonale_funkcyjna(n):
	return list(filter(lambda x : x == reduce(lambda a,b: (a + b), filter(lambda d : x % d == 0, range(1,x//2+1))), range(2,n+1)))

def doskonale_skladana(n):
	return [x for x in range(2,n + 1) if sum([d for d in range (1,x//2 + 1) if x%d == 0]) == x]
	
	
	
def perfect(x):
	suma = 0
	for i in range(1, x//2 +1):
		if (x % i == 0):
			suma = suma + i;
	if (x == suma):
		return True
	return False
	
def doskonale_funkcyjna2(n):
	return list(filter(perfect,range(2,n+1))) 
		
		
		
		
		
temp = clock()	
print(doskonale_funkcyjna(10000))
print(clock() - temp)

temp1 = clock()
print(doskonale_skladana(10000))
print(clock() - temp1)






















"""def doskonale_funkcyjna(n):
	DOSKONALE = range(2,n+1)
	for i in range(2,n+1):
		print(i)
		b = filter(lambda x: x == (reduce(lambda o,y: (o + y), filter(lambda d : i % d == 0, range(1,i//2+1)))), DOSKONALE)
		a = reduce(lambda x,y: (x + y), filter(lambda d : i % d == 0, range(1,i//2+1)))
		c = filter(lambda d : i % d == 0, range(1,i//2+1))
		print(i,a)
		
		
	return 0

def doskonale_funkcyjna3(n):
	doskonale = []
	for i in range(2,n):
		a = list(filter(lambda y: (i % y == 0), range(1, i//2 + 1)))
		if (sum(a) == i):
			doskonale.append(i); 
	return doskonale
"""

