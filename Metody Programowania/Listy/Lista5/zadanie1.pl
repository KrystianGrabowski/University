appn([X],X):-!.
appn([L1,L2|R],X):-
	append(L1,L2,X1),
	appn([X1|R],X).