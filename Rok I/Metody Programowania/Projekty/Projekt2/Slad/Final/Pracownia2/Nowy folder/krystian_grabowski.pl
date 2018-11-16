%:- module(krystian_grabowski, [resolve/4, prove/2]).

:- op(200, fx, ~).
:- op(500, xfy, v).

rozbicie([],[]):-!.	
rozbicie(A v B,[A|X]):-
	rozbicie(B,X),!.
rozbicie(A,[A]).

usun(Z,[],[]):-!.
usun(Z,[Z|L1],NL):-
	usun(Z,L1,NL),!.
usun(Z,[E|L1],NL):-
	usun(Z,L1,NNL),
	NL = [E|NNL].

naklauzle([],[]).
naklauzle([E],E):-!.	
naklauzle([E|X], W):-
	naklauzle(X,W1),
	W = E v W1.
resolve(~W, Klauzula1, Klauzula2,Wynik):-
	rozbicie(Klauzula1,W1),
	rozbicie(Klauzula2,W2),
	member(W,W2),!,
	usun(~W,W1,NW1),
	usun(W,W2,NW2),
	append(NW1,NW2,WynikP),
	sort(WynikP,WynikL),
	naklauzle(WynikL,Wynik).
	
	
resolve(W, Klauzula1, Klauzula2,Wynik):-
	rozbicie(Klauzula1,W1),
	rozbicie(Klauzula2,W2),
	member(~W,W2),!,
	usun(W,W1,NW1),
	usun(~W,W2,NW2),
	append(NW1,NW2,WynikP),
	sort(WynikP,WynikL),
	naklauzle(WynikL,Wynik).

prove(Klauzule, Proof):-
	naax(Klauzule,K),
	dowod(K,Proof).

dowod([(E,A,N)|Zbior],[(E,A,N)|Wynik]):-
	rozbicie(E,E1),
	zmiennik(E1,E,Zbior,Wynik),
	member(([],(X,Y,Z)),Wynik).

dowod([E|Zbior],Wynik):-
	dowod(Zbior,Wynik).


	
zmiennik([],E,Zbior,[]).
zmiennik([W|S],E,Zbior,Wynik):-
	rezolucja(W,E,Zbior,Wynik,Zbior),!.

zmiennik([W|S],E,Zbior,Wynik):-
	zmiennik(S,E,Zbior,Wynik).
	
rezolucja(W,E,Z,Wynik,Z):-rezolucja(W,E,Z,Wynik,Z,0).
rezolucja(W,E,[(R,A,N)|Zbior],Wynik,Z,Axx):-
	Ax is Axx + 1,
	resolve(W,E,R,Wyn),
	rozbicie(Wyn,Wyn1),
	zmiennik(Wyn1,Wyn,Z,WynikN),!,
	Wynik = [(R,A,N),(Wyn,(W,N,Ax))|WynikN].


rezolucja(W,E,[R|Zbior],Wynik,Z):-
	rezolucja(W,E,Zbior,Wynik,Z).
	
naax(X,Y):-
	naax(X,Y,Z,X).	
naax([],[],Z,X):- 
	rozmiar(X,Z1),
	Z is Z1 + 1.
naax([E|P],[(E,axiom,L)|NL] ,L,X):-
	naax(P,NL,L1,X),
	L is L1 - 1.
	
rozmiar([],0).
rozmiar([H|T],N):-
	rozmiar(T,N1),
	N is N1 + 1.

	
	
