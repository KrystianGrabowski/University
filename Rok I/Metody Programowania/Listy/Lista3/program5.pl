insert([],C,[C]).
insert([H|T], Elem, Res):-
	Elem =< H,!,
	Res=[Elem,H|T].
	
insert([H|T],Elem,Res):-
	insert(T,Elem,Res1),
	Res=[H|Res1].
	
int_sort([],[]).
int_sort([H|L],P):-
	int_sort(L,P1),
	insert(P1,H,P).
	