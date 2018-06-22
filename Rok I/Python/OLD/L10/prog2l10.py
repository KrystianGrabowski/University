def perm(L):
  if len(L) == 0:
    return [ [] ]
  return [ p[:i] + [L[0]] + p[i:] for p in perm(L[1:]) for i in range(len(p)+1)]
print (perm([1,2,3]))
