alf = "aąbcćdeęfghijklłmnńoópqrsśtuwyzźż"
def tautologia(F,zm,zmienne):
  for i in F:
    if i in alf:
      zm += i
    elif len(zm) > 0:
      zmienne.append(zm)
      zm = ""
  zmienne = set(zmienne)
  F = F.replace('F', ' False ')
  F = F.replace('T', ' True ')  
  F = F.replace('+', ' or ')
  F = F.replace('*', ' and ')
  F = F.replace('!', ' not ')
  F = F.replace('=', ' == ')
  return  all( eval(F,wart) for wart in wartosciowania(zmienne))

def dict_add(D, k, v):
  D = dict(D)
  D[k] = v
  return D
      
def wartosciowania(Z):
  if len(Z) == 0:
    return [ {} ]
  Z = list(Z)  
  z = Z[0]
  Ws = wartosciowania(Z[1:])
  
  return [ dict_add(d, z, val) for d in Ws for val in [False, True] ]
  
print (tautologia('(!(pe*q)=(!pe+!q))',"",[]))
