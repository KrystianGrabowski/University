-- Wymagamy, by moduł zawierał tylko bezpieczne funkcje
{-# LANGUAGE Safe #-}
-- Definiujemy moduł zawierający testy.
-- Należy zmienić nazwę modułu na {Imie}{Nazwisko}Tests gdzie za {Imie}
-- i {Nazwisko} należy podstawić odpowiednio swoje imię i nazwisko
-- zaczynające się wielką literą oraz bez znaków diakrytycznych.
module KrystianGrabowskiTests(tests) where

-- Importujemy moduł zawierający typy danych potrzebne w zadaniu
import DataTypes

-- Lista testów do zadania
-- Należy uzupełnić jej definicję swoimi testami
tests :: [Test]
tests =
  [ Test "anon1"  (SrcString "input x in fn(x:int)->x")                     (Eval [3] (Value 3))
  , Test "anon2"  (SrcString "input x in fn(x:int)->x+x")                   (Eval [4] (Value 8))
  , Test "anon3"  (SrcString "input x in fn(x:int)->x-2")                   (Eval [8] (Value 6))
  , Test "anon4"  (SrcString "input x in fn(x:int)->9-3")                   (Eval [5] (Value 6))
  , Test "anon5"  (SrcString "input x y in fn(x:int)->fn(y:int)->x*y")      (Eval [2,3] (Value 6))
  , Test "anon6"  (SrcFile   "if.pp6")                                            (Eval [1,5,6,7] (Value 8)) 
  , Test "anon6a" (SrcFile   "ifv2.pp6")                                          (Eval [1,2,3,4] (Value 24))
  , Test "anon7"  (SrcString "input x in let y = 2 in fn(x:int)->x mod y")        (Eval [11] (Value 1)) 
  , Test "anon8"  (SrcString "let x = (1,2) in fn(x:int*int)->fst(x) * snd(x)")  (Eval [] (Value 2))
  , Test "anon9"  (SrcString "input x in fn(x:int)->let y = 4 in x + y")         (Eval [5] (Value 9))

  , Test "anon10TP" (SrcString "input x y in fn(x:int)->fn(y:int)->true and false")   TypeError
  , Test "anon11TP" (SrcString "input x y in fn(x:int)->fn(y:int)->false")            TypeError
  , Test "anon12TP" (SrcString "input x y in fn(x:int)->fn(y:int)->not 2")            TypeError
  , Test "anon13TP" (SrcString "input x y in fn(x:int)->fn(y:int)->not y")            TypeError
  , Test "anon14TP" (SrcString "input x y in fn(x:int)->fn(y:int)->x < y")            TypeError
  , Test "anon15TP" (SrcString "input x y in fn(x:int)->fn(y:int)->x = y")            TypeError
  , Test "anon16TP" (SrcString "input x y in fn(x:int)->fn(y:int)->true")             TypeError
  , Test "anon16aTP" (SrcString "input x y in fn(x:int)->fn(y:int)->if x < 4 then true else false")   TypeError

  , Test "anon17RTE" (SrcString "input x y in fn(x:int)->fn(y:int)->x div y")      (Eval [1,0] RuntimeError)
  , Test "anon18RTE" (SrcString "let x = 0 in fn(x:int)->2 div x")                 (Eval [] RuntimeError)
  , Test "anon19RTE" (SrcString "input x in fn(x:int)->let y = 9 in y div x")     (Eval [0] RuntimeError)
  ]
