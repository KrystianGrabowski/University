insert([],H,[H]).
insert([H|T], Elem, Res):-
	Elem =< H,!,
	Res=[Elem,H|T].
	
insert([H|T],Elem,Res):-
	insert(T,Elem,Res1),
	Res=[H|Res1].
	
sel_sort([],[]).
sel_sort([H|L],P):-
	sel_sort(L,P1),
	insert(P1,H,P).
	