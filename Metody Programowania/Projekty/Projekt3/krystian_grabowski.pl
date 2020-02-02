:- module(krystian_grabowski, [parse/3]).

parse(_Path, Codes, Program) :-
	string_codes(Codes, A),
	program(Program,A,[]).

  
program(X) --> definicje(X).

definicje(X) --> definicja(X1),spacje, definicje(R),!, {X = [X1|R]}.
definicje([]) --> [].

definicja(X1) --> "def", spacje, identyfikator(NameP), {atom_codes(Name,NameP)},
				  "(", wzorzec(P), ")", spacje, "=", spacje, wyrazenie(E),
				  definicja(X1,def(Name,P,E)).
definicja(N,N) --> [].

wzorzec(W) --> "_", {W = wildcard(no)}.
wzorzec(W) -->	zmienna(Z), {atom_codes(M,Z),W = var(no,M)}.
wzorzec(W) -->	"(", wzorzec(W), ")".
wzorzec(W) -->	wzorzec(A), ",", spacje, wzorzec(B), {W = pair(no,A,B)}.

wyrazenie(E) --> "if",spacje , wyrazenie(E1), spacje,
				 "then", spacje, wyrazenie(E2),spacje,
				 "else", spacje, wyrazenie(E3), 
				 {E = if(no,E1,E2,E3)}.	 
wyrazenie(E) --> "let", spacje, wzorzec(P), spacje,
				 "=",spacje ,wyrazenie(E1),spacje,
				 "in",spacje , wyrazenie(E2), 
				 {E = let(no,P,E1,E2)}. 
wyrazenie(E) --> wyrazenieop(E1), spacje, ",",spacje, wyrazenie(E2),
				 {E = pair(no,E1,E2)}.
wyrazenie(E) --> wyrazenieop(E).


wyrazenieop(O) --> operatorunarny(Uop), wyrazenieop(E1), 
				   {(E1 == var(no,'') -> fail; O = op(no,Uop,E1))}.
wyrazenieop(O) --> wyrazenieop1(E1),  operatorbinarny(Op), wyrazenieop(E2),
				   {O = op(no,Op,E1,E2)}.
wyrazenieop(O) --> wyrazenieproste(O).
wyrazenieop1(O) --> wyrazenieproste(O).

spacje --> [Char], { code_type(Char, space) }, !, spacje.
spacje --> [].

operatorbinarny(Op) --> " = ", {Op = '='};
						" <> ", {Op = '<>'};
						" < ", {Op = '<'};
						" > ", {Op = '>'};
						" => ", {Op = '=>'};
						" <= ", {Op = '<='};
						" ^ ", {Op = '^'};
						" | ", {Op = '|'};
						" + ", {Op = '+'};
						" - ", {Op = '-'};
						" & ", {Op = '&'};
						" * ", {Op = '*'};
						" / ", {Op = '/'};
						" % ", {Op = '%'};
						" @ ", {Op = '@'};
						" , ", {Op = ','}.

operatorunarny(Op) --> "-", {Op = '-'};
                       "#", {Op = '#'};
                       "~", {Op = '~'}.

wyrazenieproste(T) --> 	"(",wyrazenie(T),")";
						wyborbitu(T);
						wyborbitow(T);
						atomowe(T).	

atomowe(A) --> 	pustywektor(A);
				wywolaniefunkcji(A);
				pojedynczybit(A);
				zmienna(P), {atom_codes(P1,P), A = var(no,P1)}.

wywolaniefunkcji(Wf) --> identyfikator(Name1), "(", wyrazenie(E), ")",
						 {atom_codes(Name,Name1),Wf = call(no,Name,E)}.
					 
pustywektor(Pw) --> "[","]",{Pw = empty(no)}.
					
pojedynczybit(Pb) --> "[", wyrazenie(E), "]", {Pb = bit(no,E)}.
					  
wyborbitu(WB) --> identyfikator(E12), "[",wyrazenie(E2), "]", 
				  {(E12 == [] -> fail; atom_codes(E1,E12), WB = bitsel(no,E1,E2))}.		
				  
wyborbitow(WBW) --> identyfikator(E12), "[", wyrazenie(E2), "..", wyrazenie(E3), "]", 
					{atom_codes(E1,E12), WBW = bitsel(no,E1,E2,E3)}.	


zmienna(Z) --> identyfikator(Z).				   
identyfikator(I) --> reszta(I).
reszta(C) --> nazwa(L),{C = [L|R]}, reszta(R).
reszta([]) --> [].
nazwa(L) --> [Char], {char_type(Char, csym), L is Char}.


