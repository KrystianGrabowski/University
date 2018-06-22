def krzyzyk(n):
	for i in range(n):
		print((n-1)*" ",n*"*")
	for j in range(n):
		print(3*n*"*")
	for k in range(n):
		print((n-1)*" ",n*"*")

print(krzyzyk(4))
