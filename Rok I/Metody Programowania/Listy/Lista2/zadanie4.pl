a)
even([]).
even([_,_|X]) :-
    even(X).

b)
append([], X, X).
append([H|T], X, [H|Y]):-
    append(T, X, Y).
reverse([],[]).
reverse([H|T], X) :-
    reverse(T,Y),
    append(Y,[H],X).
palindrom(X) :-
    reverse(X,X).

c)
singletion([_]).