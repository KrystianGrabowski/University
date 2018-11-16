empty([]).
put(E,S,[E|S]).
get([H|T],H,T).
addall(E, G, S, R):-
	findall(E, G, L),
	append(L,S,R).

empty_K(X-X).
get_K([H|T]-X,H,T-X).
put_K(E,A-[E|B],A-B).
addall_K(E,G,X-Y,X-Z):-
    findall(E,G,Y,Z).
