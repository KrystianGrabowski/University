halve(X,L,R):- halve(X,L,R,X),!.

halve(X,[],X,[_]).
halve(X,[],X,[]).

halve([H|T],[H|L],R,[_,_|T1]):-
	halve(T,L,R,T1).

merge(L1,[],L1):-!.
merge([],L2,L2):-!.

merge([H1|L1],[H2|L2],[H1|L3]):-
	H1 =< H2,
	merge(L1,[H2|L2],L3),!.
	
merge(L1,[H2|L2],[H2|L3]):-
	merge(L1,L2,L3).
	
mergesort([],[]):-!.	
mergesort([X],[X]):-!.		
mergesort(X,Y):-
	halve(X,C1,C2),
	mergesort(C1,Y1),
	mergesort(C2,Y2),
	merge(Y1,Y2,Y).
	

