from turtle import*
def Kwadrat():
    for i in range(4):
        fd(50)
        rt(90)
def Duze(n):
	from duze_cyfry import dajCyfre
	dajCyfre(3)
	d=len(str(n))
	t=[]
	while n>0:
		t.append(n%10)	
		n=n//10
	for l in range (d):
		for r in dajCyfre(l):
                    print(r)
                    
		


Duze(12345)





