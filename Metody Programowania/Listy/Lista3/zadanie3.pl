factorial(0,1).
factorial(N,M) :-
    N1 is N - 1,
    factorial(N1,M1),!,
    M is M1 * N.
	
concat_number(D,N):-
	concat_number(D,0,N).
concat_number([],N,N).
concat_number([H|T],A,N):-
	A1 is (A*10) + H,
	concat_number(T,A1,N).
	
decimal(N,D):-
	decimal(N,[],D).

decimal(0,A,D):-
	!,
	A = D.
	
decimal(N,A,D):-
	A1 is N mod 10,
	N1 is N // 10,
	decimal(N1,[A1|A],D).
