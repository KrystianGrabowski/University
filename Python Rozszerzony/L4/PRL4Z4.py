class Wyrazy:
	def __init__(self, nazwa):
		self.ok = [97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
			122, 261, 263, 281, 322, 324, 243, 347, 378, 380,
			48, 49, 50, 51, 52, 53, 54, 55, 56, 57]
		plik = open(nazwa,'r')
		self.tekst = plik.read()
		plik.close()
		self.licznik = -1
		self.dlugosc = len(self.tekst)
	
	def __iter__(self):
		return self

	def __next__(self):
		wyraz = ""
		litera = ''
		self.licznik += 1
		if self.licznik >= self.dlugosc: 
			raise StopIteration
		litera = self.tekst[self.licznik]
		
# Nie byłem pewien czy można było użyć isalpha
		
		while (ord(litera.lower()) not in self.ok):			
			self.licznik += 1
			if (self.licznik >= self.dlugosc):
				raise StopIteration
			litera = self.tekst[self.licznik]

		while (ord(litera.lower()) in self.ok):
			wyraz = wyraz + litera
			self.licznik += 1
			litera = self.tekst[self.licznik]

		if (litera == '-' and self.tekst[self.licznik + 1] == '\n' and wyraz != ""):
			wyraz = wyraz + self.__next__()
		return wyraz



def statystyka_slow(nazwa):
	w = Wyrazy(nazwa)
	stat = {}
	while(True):
		try:
			dlugosc = len(w.__next__())
			if (dlugosc in stat):
				stat[dlugosc] += 1
			else:
				stat[dlugosc] = 1
		except StopIteration:
			break
	return stat

def wypisz():
	w = Wyrazy("plik.txt")
	while (True):
		try:
			print(w.__next__())
		except StopIteration:
			break	

s = statystyka_slow("plik.txt")
for i in s:
	print("%i --> %i" % (i, s[i]))





		
