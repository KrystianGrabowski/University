
import unittest

class SimpleTestCase(unittest.TestCase):
	def setUp(self):
		self.s = statystyka_slow("plik.txt")
		self.w = Wyrazy("plik.txt")
		"""for i in self.s:
				print("%i --> %i" % (i, self.s[i]))"""
	def testA(self):
		for i in self.s:
			assert type(i) == type(5)

	def testB(self):
		for i in self.s:
			assert type(self.s[i]) == type(5)
			assert self.s[i] != 0

	def testC(self):
			assert self.w.dlugosc > 0
			assert type(self.w.tekst) == type("napis")



class Wyrazy:
	"""
	Klasa przechowuje tekst zawarty w pliku
	"""
	def __init__(self, nazwa):
		"""
		Wczytanie nowego tekstu

		@param nazwa : nazwa pliku
		"""
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
		"""
		Metoda zwracająca kolejny wyraz z teksu

		@return: String kolejny wyraz
		"""
		wyraz = ""
		litera = ''
		self.licznik += 1
		if self.licznik >= self.dlugosc:
			raise StopIteration
		litera = self.tekst[self.licznik]


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
	"""
	Metoda konsturuująca słownik mówiący ile wyrazów jakiej długości
	znajduje się w tekście

	@param nazwa : nazwa pliku z tekstem do zestatystykwania
	@return: Słownik kolejny wyraz
	"""
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
	return


unittest.main()
