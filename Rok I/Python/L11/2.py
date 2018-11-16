from cesar import*
max=0
text= open('slowa.txt', encoding='utf8').readlines()

for w in text: #szukanie najdluzszego wyrazu
    if len(w)>max:
        max=len(w)
for s in text:
    for i in range(max,1,-1):
        for k in range(1,32):
            if len(s)==i:
                if cesar(s,k) in text:
                    print(s)
                
            
