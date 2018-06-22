from string import*
slownik = {}
napis=''
zn=[]
alf = 'aąbcćdeęfghijklłmnńoópqrsśtuvwxyzźż'
ALF = alf.upper()
l = 0
przekaz = ''
zdanie = ''
for wiersz in open('fragment.txt').read().split():
    if wiersz[0] in ALF or alf:
        napis = napis + wiersz[0]
        napis = napis.lower()
        slownik[l] = wiersz
        l += 1
print(napis)
for w in open('slowa.txt', encoding='utf8').read().split():
    if w in napis and 10>len(w)>2:
        zn.append(w)
zn = set(zn)
for i in zn:
    if len(i)>len(przekaz):
        przekaz = i
print(przekaz)
a = napis.find(przekaz)
g = len(przekaz)
for k in range(a-3,a+g+3):
    
    zdanie += slownik[k]+' '
print(zdanie)
