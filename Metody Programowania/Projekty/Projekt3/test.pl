/*
Parser czyta napis (wyra¿enie matematyczne w notacji infiksowej) i zwraca zbudowane wyra¿enie w postaci drzewa
*/

parse(N) --> wyrazenie(N).

cyfra(C) --> [Char], {char_type(Char, digit), C is Char-"0"}.

liczba(N) --> cyfra(C), !, opc_liczba(N,C).
opc_liczba(N,A) --> cyfra(C), !, {A1 is A*10+C}, opc_liczba(N,A1).
opc_liczba(N,N) --> [].

wyrazenie(N) --> skladnik(S), !, opc_wyrazenie(N,S).
opc_wyrazenie(N,A) --> "+", skladnik(S), !, opc_wyrazenie(N,op("+",A,S)).
opc_wyrazenie(N,A) --> "-", skladnik(S), !, opc_wyrazenie(N,op("-",A,S)).
opc_wyrazenie(N,N) --> [].

skladnik(N) --> czynnik(S), opc_skladnik(N,S).
opc_skladnik(N,A) --> "*", czynnik(S), !, opc_skladnik(N,op("*",A,S)).
opc_skladnik(N,A) --> "/", czynnik(S), !, opc_skladnik(N,op("/",A,S)).
opc_skladnik(N,N) --> [].

czynnik(N) --> wyrazenie_proste(S), opc_czynnik(N,S).
opc_czynnik(op("^",A,N), A) --> "^", wyrazenie_proste(S), !, opc_czynnik(N,S).
opc_czynnik(N,N) --> [].

wyrazenie_proste(N) --> "(", wyrazenie(N), ")".
wyrazenie_proste(N) --> liczba(N).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

t(In, Out) :-
	string_codes(In, A),
	parse(Out,A,[]).

test(In, Result):-
	print(In),
	print(=),
	print(Result),
	t(In,Result),
	nl.
	
:- test("404", 404).
:- test("2+5", op("+",2,5)).
:- test("2-5", op("-",2,5)).
:- test("2+2*5+3", op("+",op("+",2,op("*",2,5)),3)).
:- test("2+2/5+3", op("+",op("+",2,op("/",2,5)),3)).
:- test("125/5/5", op("/",op("/",125,5),5)).
:- test("2^2", op("^",2,2)).
:- test("2^2^3", op("^",2,op("^",2,3))).
:- test("(2^2)^3", op("^",op("^",2,2),3)).
:- test("(2+2)*5+3^(2+1)", op("+",op("*",op("+",2,2),5),op("^",3,op("+",2,1)))).
