filter([],[]).

filter([H|T],[H|P]):-
	H >= 0,
    !,
	filter(T,P).
	
filter([H|T],P):-
	H < 0,
	filter(T,P).
	
	
count(_, [], 0).

count(X, [X|L], N):-
	count(X, L, C),!,
	N is C+1.

count(X, [_|L], N):-
	count(X, L, N).
	
exp(B,E,R):-
	R is B^E.