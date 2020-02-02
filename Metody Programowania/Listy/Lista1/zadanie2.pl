mily(X) :-
	czlowiek(X),
	odwiedzazoo(X).

stykasie(X,Y) :-
	odwiedzazoo(Y),
	czlowiek(Y),
	mieszkawzoo(X),
	zierze(X).
	
szczesliwe(X) :-
	stykasie(X,Y),
	czlowiek(Y),
	mily(Y).
	zierze(X).

niesmok(X) :-
	szczesliwe(X),
	mieszkawzoo(X).