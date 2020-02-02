def szachownica(n,k):
	for i in range (2 * n):      #przesowanie sie miedzy kolumnami	
		for _ in range (k):			#przesowanie sie miedzy wierszami
			if i % 2 == 0:
				for _ in range (n):
					print (k * " " + k * "#", end = "")
				print()
			else:
				for _ in range (n):
					print (k * "#" + k * " ", end = "")
				print()
	return
szachownica(4,3)
