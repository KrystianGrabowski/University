flatten(L, X):-
  flatten(L, X, []).

flatten([], X, X).
flatten([H|T], X, Acc):-
  atomic(H), !,
	X = [H|X1],
  flatten(T, X1, Acc).
flatten([H|T], X, Acc):-
  flatten(H, X, P),
  flatten(T, P, Acc).