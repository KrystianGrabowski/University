:-module(krystian_grabowski, [solve/2]).

:- op(200, fx, ~).
:- op(500, xfy, v).

solve(Clauses,Solution) :-
	separator(Clauses,T),
	sort(T,T2),
	flatten(T2,Zmienne),
	usuwanienegacji(Zmienne,ZmienneBN),
	sort(ZmienneBN,ZmienneS),
	kombinacje_all(ZmienneS,Solution),
	spelnialne(Solution,T2).
	
separator([],[]).	
separator([K|ZK],X):-
	rozbicie(K ,R),
	sort(R,R1),
	X = [R1|X1],
	separator(ZK,X1).

rozbicie([],[]):-!.	
rozbicie(A v B,[A|X]):-
	rozbicie(B,X),!.
rozbicie(A,[A]).

usuwanienegacji([],[]).
usuwanienegacji([~H|T],Nowa):-
	usuwanienegacji(T,Nowak),!,
	Nowa = [H|Nowak].
	
usuwanienegacji([H|T],Nowa):-
	usuwanienegacji(T,Nowak),!,
	Nowa = [H|Nowak].
	
kombinacje_all([],[]).
kombinacje_all([H|T],W):-
	wartosci(H,X),
	kombinacje_all(T,W1),
	W = [X|W1].
	
wartosci(X,Wartosc):-
	Wartosc = (X,f).
wartosci(X,Wartosc):-
	Wartosc= (X,t).
	
spelnialne(_,[]):-!.
spelnialne(X,[K|ZK]):-
	sprawdz(X,K),
	spelnialne(X,ZK).
	

sprawdz(X,K):-sprawdz(X,K,X).
sprawdz([W|_],[E|_],_):-
	W = (E,t),!.
sprawdz([W|_],[~E|_],_):-
	W = (E,f),!.
	
sprawdz([_|RW],Y,X):-
	sprawdz(RW,Y,X).
sprawdz([],[_|R],X):-sprawdz(X,R,X).
	
	

	
	
	
	
	
	






	

	



  
  
  
	