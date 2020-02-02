polaczenie(wroclaw, warszawa).
polaczenie(wroclaw, krakow).
polaczenie(wroclaw, szczecin).
polaczenie(szczecin, lublin).
polaczenie(szczecin, gniezno).
polaczenie(warszawa, katowice).
polaczenie(gniezno, gliwice).
polaczenie(lublin, gliwice).
polaczenie(gliwice, berlin).
polaczenie(warszawa, wroclaw).


trip(S,K,D):-
trip(S,K,D,[K]).

trip(X,X,Y,Y).

trip(S,K,D,A):-
	polaczenie(X,K),
	\+ member(X,A),
	A1 = [X|A],
	trip(S,X,D,A1).
	

