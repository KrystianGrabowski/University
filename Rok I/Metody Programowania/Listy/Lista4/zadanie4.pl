mirror(leaf,leaf).
mirror(node(L,W,P),node(L1,W,P1)):-
	mirror(L,P1),
	mirror(P,L1).
	
flatten(leaf, []). 
flatten(node(Lewy, W, Prawy), L):-
  flatten(Lewy, LL),
  flatten(Prawy, LP),
  append(LL, [W|LP], L).