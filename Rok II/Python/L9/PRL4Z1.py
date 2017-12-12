from time import clock
from itertools import*


def pierwsze_funkcyjna(n):
	return list(filter(lambda x: all(x % d == 0 for d in range(2,x//2+1)), range(2, n+1)))
	
def pierwsze_skladane(n):
	return [l for l in range(2,n + 1) if ([i for i in range (2,l//2 + 1) if l%i == 0]) == []]


#########V1
class Pierwsze:
	def __init__(self,n):
		self.limit = n
		self.liczba = 1

	def __iter__(self):
		return self

	def __next__(self):
		pierwsza = True	 
		while True:
			self.liczba += 1
			for d in range(2, self.liczba//2 + 1):
				if (self.liczba % d == 0):
					pierwsza = False
					break
			if self.liczba > self.limit : raise StopIteration
			if pierwsza:
				return self.liczba
			else:
				pierwsza = True


def pierwsze_iteracyjne(n):
	lista = []
	i = Pierwsze(n)
	try:
		while True:
			lista.append(i.__next__())
	except StopIteration:
		pass
	finally:
		del i
	return lista		
	
czasy = [10,100,1000,10000]

print("       | funkcyjna | skladana  | iterator")
for i in czasy:
	temp2 = clock()
	(pierwsze_funkcyjna(i))
	a = (clock() - temp2)

	temp1 = clock()
	(pierwsze_skladane(i)) 
	b = (clock() - temp1)

	temp = clock()
	(pierwsze_iteracyjne(i))
	c = (clock() - temp)
	l = (5-len(str(i))) * " "
	print("%s %i | %.7f | %.7f | %.7f" % (l,i,a,b,c))


# INNE WERSJE NA WYPADEK GDYBYM ŹLE ZROZUMIAŁ POLECENIE
""" 
###########V2
def pierwsze_iteracyjnie(n):
	lista = []
	pierwsze = filter(lambda x: all(x % d for d in range(2, x//2 +1)) , count(2))
	while (True):
		p = pierwsze.__next__()
		if (p > n):
			break			
		lista.append(p)
	return lista;

###########V3
def wsp():
	liczba = 1
	pierwsza = True	 
	while True:
		liczba += 1
		for d in range(2, liczba//2 + 1):
			if (liczba % d == 0):
				pierwsza = False
				break
		if pierwsza:
			yield liczba
		else:
			pierwsza = True

def pierwsze_iteracyjnie2(n):
	lista = []
	i = wsp()
	F = True
	while F:
		p = i.__next__()
		if (p > n):
			break
		lista.append(p)
	return lista
"""
