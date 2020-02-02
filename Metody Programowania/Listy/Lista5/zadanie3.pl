halve(X,L,R):- halve(X,L,R,X),!.

halve(X,[],X,[_]).
halve(X,[],X,[]).

halve([H|T],[H|L],R,[_,_|T1]):-
	halve(T,L,R,T1).