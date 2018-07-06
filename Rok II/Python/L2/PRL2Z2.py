from itertools import*

class Formula:
	def oblicz(self,zmienne):
		pass
	
class Impl(Formula):
	def __init__(self,x,y):
		self.x = x
		self.y = y
	def oblicz(self,zmienne):
		if (self.x.oblicz(zmienne) and self.y.oblicz(zmienne) == False):
			return False
		else:
			return True
	def __str__(self):
		return("%s => %s" % (self.x.__str__(), self.y.__str__()))


class Koniu(Formula):
	def __init__(self,x,y):
		self.x = x
		self.y = y
	def oblicz(self,zmienne):
		if (self.x.oblicz(zmienne) == True and self.y.oblicz(zmienne) == True):
			return True
		return False
	def __str__(self):
		return("%s ^ %s" % (self.x.__str__(), self.y.__str__()))

class Alt(Formula):
	def __init__(self,x,y):
		self.x = x
		self.y = y
	def oblicz(self,zmienne):
		if (self.x.oblicz(zmienne) == False and self.y.oblicz(zmienne) == False):
			return False
		return True
	def __str__(self):
		return("%s v %s" % (self.x.__str__(), self.y.__str__()))

class Rown(Formula):
	def __init__(self,x,y):
		self.x = x
		self.y = y
	def oblicz(self,zmienne):
		if (self.x.oblicz(zmienne) == False and self.y.oblicz(zmienne) == False):
			return True
		if (self.x.oblicz(zmienne) == True and self.y.oblicz(zmienne) == True):
			return True
		return False
	def __str__(self):
		return("%s <=> %s" % (self.x.__str__(), self.y.__str__()))

class true(Formula):
	def __init__(self):
		self.x = True
	def oblicz(self,zmienne):
		return True
	def __str__(self):
		return("True")

class false(Formula):
	def __init__(self):
		self.x = False
	def oblicz(self,zmienne):
		return False
	def __str__(self):
		return("False")

class Zmienna(Formula):
	def __init__(self,x):
		self.x = x
	def oblicz(self,zmienne):
		return zmienne[self.x]
	def __str__(self):
		return(self.x)


	
def tautologia(F,z):
	S = {}
	B = [True,False]
	T = []
	A = product(B, repeat=len(z))
	for i in A:
		for j in range(len(z)):
			S[z[j]] = i[j] 
		T.append(S)
		S = {}
	for p in T:
		if (F.oblicz(p) == False):
			return False
	return True

			

	
zmienne = {}
zmienne["p"] = True
zmienne["q"] = False
zmienne["r"] = False
f2 = Impl(Impl(Alt(Zmienna("p"),Zmienna("q")),Zmienna("r")),Impl(Zmienna("p"),Zmienna("r")))
f1 = Koniu(Zmienna("p"), Alt(Zmienna("r"),Zmienna("q")))
f0 = Alt(Zmienna("r"),Zmienna("q"))
print(f0.oblicz(zmienne))
print(f1)
print(tautologia(f1,["p","q","r"]))
print(f2.__str__())
print(tautologia(f2,["p","q","r"]))



