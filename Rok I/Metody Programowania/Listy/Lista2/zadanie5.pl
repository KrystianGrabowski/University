head(H,[H|_]).

last(H,[H|[]]).
last(H, [_|G]):-
	last(H,G).

tail(T, [_|T]).

init([], [_]).
init([H|X],[H|T]):-
	init(X,T).

prefix([],_).
prefix([X|P], [X|L]):-
    prefix(P,L).

sufix(S,S).
sufix([_|L], S):-
    sufix(L,S).