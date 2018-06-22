def Duze(n):
	from duze_cyfry import dajCyfre
	dajCyfre(3)
	d=len(str(n))
	t=[]
	while n>0:
		t.append(n%10)	
		n=n//10
	for l in range (d):
		print()
		for r in dajCyfre(t[l]):
			print (r)
		


Duze(12345)



