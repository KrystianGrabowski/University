mylength(X,Y):-
	mylength(X,Y,0).

mylength([],Y,Y).	

mylength([_|X],Y,A):-
	A \== Y,
	A1 is A+1,
	mylength(X,Y,A1).
	
	