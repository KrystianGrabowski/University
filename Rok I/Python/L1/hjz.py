from losowanie_fragmentow import losuj_fragment
n=12
while (n>0):
	a=(losuj_fragment())
	d=len(a)
	if (n-d)>=0 and (n-d)!=1 :	
		print(a)
		n=n-d
		
