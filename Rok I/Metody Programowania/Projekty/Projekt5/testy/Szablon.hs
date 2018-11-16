{------------------------------}
{- AUTOR ----------------------}
{- Anna Karaś -----------------}
{------------------------------}
{- KONSULTACJA POPRAWNOŚCIOWA -}
{- Mariusz Bielecki -----------}
{------------------------------}

{------------------------------}
{- STRUKTURA TESTÓW - OGÓLNIE -}
{------------------------------}

--wynik obliczalny, bez inputów:
Test "nazwa" (SrcString "2") (Eval [] (Value 2))

--wynik obliczalny, z inputami, ujemną liczbą ujętą w nawiasy:
Test "nazwa" (SrcString "input x y in x - y - 2") (Eval [1, 1] (Value (-2)))

--error - dzielenie przez zero:
Test "nazwa" (SrcString "3 mod 0") (Eval [] RuntimeError)

--error - złe typy:
Test "nazwa" (SrcString "true div true") TypeError

--test z pliku:
(SrcFile "plik.pp5") zamiast (SrcString "program inline")

{-----------------}
{- NOWA SKŁADNIA -}
{-----------------}

--identyfikatory funkcji
zaczynają się od litery lub podkreślenia, po którym następuje ciąg znaków [a-z] [0-9] ' _ 

--aplikacja funkcji
konstrukcja: identyfikator(wyrażenie)
np.
fib() 							<- argument to unit ()
fib(n) 							<- argument to zmienna n
fib(n-1) 						<- argument to wynik wyrażenia (n-1)
fib(if n <= 5 then 3 else 8)	<- argument to wynik ifa
fib((1,2)) 						<- argument to para (1,2)
fib([1,2,3]:int list) 			<- argument to lista [1,2,3]

--para
konstrukcja: (wyrażenie1, wyrażenie2)
np. 
(1,2)
(2+3,8+5)

typowanie par:
np. 
(1,2) 							<- ma typ int*int
(true,1) 						<- ma typ bool*int
co może być przydatną informacją, gdy funkcja ma zwracać parę 

--pierwsza/druga projekcja
konstrukcja: fst wyrażenie/snd wyrażenie (gdzie wyrażenie oblicza się do pary)
np.
fst (2,5)
snd (true, false)

--lista pusta
konstrukcja: []:typ_elementów list
np.
[]: int list
[]: bool list

--konstruktor listy niepustej cons
konstrukcja: wyrażenie::wyrażenie::[]: typ_elementów list
zawsze na końcu dołączamy []

np.
1::2::[]: int list
if x < 5 then 8 else 5 :: 5::[]: int list
true::false::[]: bool list

--dopasowanie wzorca do listy
konstrukcja: match lista with [] -> wyrażenie1 | x::xs -> wyrażenie2

czyli
mecz lista with
jeśli pusta, zwróć wynik wyrażenia takiego
jeśli niepusta, zwróć wynik wyrażenia tamtego

np.
match [1,2,3]: int list with
| [] -> true
| x::xs -> false

---

match [1,2,3]: int list with
| [] -> 0
| x::xs -> if x > 0 then 15 else 888

--definicje funkcji
konstrukcja: fun identyfikator_funkcji(argument:typ_argumentu):typ_wartości_zwracanej = wyrażenie_czyli_ciało_funkcji

np.
fun suma(a:int, b:int):int = a+b 	<-- funkcja z "normalnym" argumentem
suma(2,3) 							<-- wywołanie

fun ffff(u:unit) = cośtam 			<-- funkcja z unitem
ffff() 								<-- wywołanie

--programy
konstrukcja: ciąg definicji funkcji, deklaracji zmiennych wejściowych oraz wyrażenia 
definicje funkcji i deklaracje zmiennych wejściowych są opcjonalne, ale jeśli występują, to od wyrażenia powinny być oddzielone słowem in

np.
definicja funkcji
definicja funkcji
definicja funkcji
input x1 x2 x3
in
wyrażenie

---

definicja funkcji
in
wyrażenie

---

input x1 x2 x3
in
wyrażenie