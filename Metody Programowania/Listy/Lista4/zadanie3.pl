lista([_]).
lista([_|Y]):-
  lista(Y). 

dodaj([]).
dodaj([0|P]):-
  dodaj(P).
dodaj([1|P]):-
  dodaj(P).

bin([0]). 
bin([1]). 
bin([1|X]):-
  lista(X),
  dodaj(X).

rdodaj([0,1]).

rdodaj([0|P]):-
  rdodaj(P).
rdodaj([1|P]):-
	rdodaj(P).	

rbin([0]). 
rbin(X):-
  lista(X),
  rdodaj(X).
  