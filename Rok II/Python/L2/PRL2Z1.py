class Wyrazenie:
	pass
	
class Stala(Wyrazenie):
	def __init__(self,x):
		self.x = x
	def oblicz(self,zmienne):
		return self.x

class Zmienna(Wyrazenie):
	def __init__(self,x):
		self.x = x
	def oblicz(self,zmienne):
		return zmienne[self.x]

class Dodaj(Wyrazenie):
	def __init__(self,a,b):
		self.a = a
		self.b = b
	def oblicz(self,zmienne):
		return self.a.oblicz(zmienne) + self.b.oblicz(zmienne)

class Odejmij(Wyrazenie):
	def __init__(self,a,b):
		self.a = a
		self.b = b
	def oblicz(self,zmienne):
		return self.a.oblicz(zmienne) - self.b.oblicz(zmienne)

class Razy(Wyrazenie):
	def __init__(self,a,b):
		self.a = a
		self.b = b
	def oblicz(self,zmienne):
		return self.a.oblicz(zmienne) * self.b.oblicz(zmienne)

class Dziel(Wyrazenie):
	def __init__(self,a,b):
		self.a = a
		self.b = b
	def oblicz(self,zmienne):
		return self.a.oblicz(zmienne) / self.b.oblicz(zmienne)

zmienne = {}
zmienne['x'] = 4
print(zmienne)
o = Dodaj(Razy(Stala(9),Zmienna('x')),Stala(2))
print(o.oblicz(zmienne))














