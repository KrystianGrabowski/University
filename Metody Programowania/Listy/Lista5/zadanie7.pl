split([],_,[],[]):-!.

split([H|List],Med,Small,[H|Big]):-
	H >= Med,
	split(List,Med,Small,Big),!.
	
split([H|List],Med,[H|Small],Big):-
	split(List,Med,Small,Big).

qsort(List, Sorted):-
	qsort(List, Sorted, []).

qsort([], Sorted, Sorted).

qsort([E|Tail], Sorted, Acc):-
	split(Tail, E, Small, Big),

	qsort(Big, NextAcc, Acc),
		qsort(Small, Sorted, [E|NextAcc]).
