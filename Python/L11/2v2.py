from cesar import*
maks=0
SL=[]
POM = []
for wyraz in open('slowa.txt', encoding='utf8').read().split():
    SL.append(wyraz)
    
for w in SL:
    if len(w) > maks:
        maks = len(w)
        print(w)

print(maks,w)
            

