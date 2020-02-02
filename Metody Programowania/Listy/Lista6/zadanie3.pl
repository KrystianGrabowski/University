insert(leaf, E, node(leaf, E, leaf)).
insert(node(L, IE, P), E, node(L, IE, IP)):-
	E >= IE,
	insert(P, E, IP),!.
insert(node(L, IE, P),E, node(IL, IE, P)):-
	E < IE,
	insert(L, E, IL).
  
find(E,node(_,E,_)):-
	E == E,!.
find(E,node(L,_,_)):-
	find(E,L),!.
find(E,node(_,_,P)):-
	find(E,P),!.
	

findMax(node(_,E,leaf),E):-!.
findMax(node(_,_,P),M):-
	findMax(P,M).
findMin(node(leaf,E,_),E):-!.
findMin(node(L,_,_),Mi):-
	findMin(L,Mi).
empty(leaf).

del(node(leaf, E, leaf),E,leaf).
del(node(leaf, E, P),E,P).
del(node(L, E, leaf),E,L).
del(node(L, E, P),E,node(L,Min,NP)):-
	findMin(P,Min),
	del(P,Min,NP).
	
del(node(L, IE, P), E, node(L, IE, IP)):-
	E > IE,
	del(P, E, IP),!.
del(node(L, IE, P), E, node(IL, IE, P)):-
	E < IE,
	del(L, E, IL).
	
delMax(D,E,W):-
	findMax(D,E),
	del(D,E,W).
  
  