
select_min([X],X,[]).

select_min([H|T],H,[M|R]):-
	select_min(T,M,R),
	M > H.
select_min([H|T],M,[H|R]):-
	select_min(T,M,R).
	