:- module(krystian_grabowski, [resolve/4, prove/2]).

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
	dowod(K,Pruf),
	ostatnia(Pruf,Proof).
	

dowod([(E,A)|Zbior],[(E,A)|Wynik]):-
	rozbicie(E,E1),
	zmiennik(E1,E,Zbior,Wynik),
	member(([],X,Y,Z),Wynik).

dowod([E|Zbior],Wynik):-
	dowod(Zbior,Wynik).
	

	
zmiennik([],E,Zbior,[]).
zmiennik([W|S],E,Zbior,Wynik):-
	rezolucja(W,E,Zbior,Wynik,Zbior),!.

zmiennik([W|S],E,Zbior,Wynik):-
	zmiennik(S,E,Zbior,Wynik).
	

	
rezolucja(W,E,[(R,A)|Zbior],Wynik,Z):-
	resolve(W,E,R,Wyn),
	rozbicie(Wyn,Wyn1),
	zmiennik(Wyn1,Wyn,Z,WynikN),!,
	Wynik = [(R,A),(Wyn,W,X,Y)|WynikN].


rezolucja(W,E,[R|Zbior],Wynik,Z):-
	rezolucja(W,E,Zbior,Wynik,Z).

	
	
naax([],[]).	
naax([E|P],[(E,axiom)|NL]):-
	naax(P,NL).

rozmiar([],0).
rozmiar([E|R],N):-
	rozmiar(R,N1),
	N is N1 + 1.

ostatnia(X,Y):- ostatnia(X,Y,1).
ostatnia([A],[A],X).
ostatnia([(H1,A),(H2,B),(H3,W,N1,N2)|R],[(H1,A),(H2,B),(H3,W,O,O1)|R],X):-
	O = X,
	X1 is X + 1,
	O1 = X1,
	X2 is X1 + 1,
	ostatnia([(H3,W,O,O1)|R],[(H3,W,O,O1)|R],X2).
	
	
	

	
	
