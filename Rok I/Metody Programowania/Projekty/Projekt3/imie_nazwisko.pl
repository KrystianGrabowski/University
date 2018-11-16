

parse(_Path, Codes, Program) :-
	string_codes(Codes, A),
	program(Program,A,[]).

  
program(X) --> definicje(X).

definicje(X) --> definicja(X1), !, definicje(R), {X = [X1|R]}.
definicje([]) --> [].

definicja(X1) --> "def ", identyfikator(NameP), {atom_codes(Name,NameP)}, "(", wzorzec(P), ")", " = ", wyrazenie(E),  definicja(X1,def(Name,P,E)) .
definicja(N,N) --> [].

wzorzec(W) --> "_", {W = wildcard(no)}.
wzorzec(W) --> zmienna(Z), {atom_codes(M,Z),W = var(no,M)}.
wzorzec(W) --> "(", wzorzec(W), ")".
wzorzec(W) --> wzorzec(A), ", ", wzorzec(B), {W = pair(no,A,B)}.

wyrazenie(E) --> "if ", wyrazenie(E1), " then ", wyrazenie(E2), " else ", wyrazenie(E3), {E = if(no,E1,E2,E3)}.
wyrazenie(E) --> "let ", wzorzec(P), " = ", wyrazenie(E1), " in ", wyrazenie(E2), {E = let(no,P,E1,E2)}.
wyrazenie(E) --> wyrazenieop(E).

wyrazenieop(O) --> operatorunarny(Uop), wyrazenieop(E1), {O = op(no, Uop, E1)};
				   identyfikator(P), {atom_codes(P1,P), O = P1};
                   wyrazenieop(E1), !, operatorbinarny(Op), wyrazenieop(E2), {O = op(no, Op, E1, E2)}.

operatorbinarny(Op) --> " = ", {Op = "="};
						" <> ", {Op = "<>"};
						" < ", {Op = "<"};
						" > ", {Op = ">"};
						" => ", {Op = "=>"};
						" <= ", {Op = "<="};
						" ^ ", {Op = "^"};
						" | ", {Op = "|"};
						" + ", {Op = "+"};
						" - ", {Op = "-"};
						" & ", {Op = "&"};
						" * ", {Op = "*"};
						" / ", {Op = "/"};
						" % ", {Op = "%"};
						" @ ", {Op = "@"};
						" , ", {Op = ","}.

operatorunarny(Op) --> "-", {Op = "-"};
                       "#", {Op = "#"};
                       "~", {Op = "~"}.

identyfikator(I) --> reszta(I).
reszta(C) --> nazwa(L),{C = [L|R]}, reszta(R).
reszta([]) --> [].
nazwa(L) --> [Char], {char_type(Char, csym), L is Char}.

zmienna(Z) --> identyfikator(Z).

