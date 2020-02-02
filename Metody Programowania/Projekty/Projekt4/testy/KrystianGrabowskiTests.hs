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
-- Należy uzupełnić jej definicję swoimi testami
tests :: [Test]
tests =
  [ Test "wart"      (SrcString "input x in x")           (Eval [66] (Value 66))
  , Test "aryt1"     (SrcString "input x in 9 + x")       (Eval [31] (Value 40))
  , Test "aryt2"     (SrcString "input x in x - 8")       (Eval [21] (Value 13))
  , Test "aryt3"     (SrcString "input x in 5 * x")       (Eval [5]  (Value 25))
  , Test "aryt4"     (SrcString "input x in x div 2")    (Eval [18] (Value 9))
  , Test "aryt5"     (SrcString "input x in x mod 10")    (Eval [21] (Value 1))
  , Test "div0"      (SrcString "input x in x div 0")     (Eval [10] RuntimeError)
  , Test "unar1"     (SrcString "input x in -8 + x")      (Eval [9] (Value 1))
  , Test "unar2"     (SrcString "input x in -5 * -5 * x") (Eval [2] (Value 50))
  , Test "typdef"    (SrcString "x")                                             TypeError
  , Test "typun1"    (SrcString "not 2 + 2")                                     TypeError
  , Test "typar1"    (SrcString "input x in x + true")                           TypeError
  , Test "typar2"    (SrcString "true * false")                                  TypeError
  , Test "typar3"    (SrcString "true mod 2")                                    TypeError
  , Test "typpor1"   (SrcString "input x in if x = true then x - 3 else x + 3")  TypeError
  , Test "typpor2"   (SrcString "input x in if x < false then x + 6 else x")     TypeError
  , Test "typpor3"   (SrcString "input x in if false <> x then x else 0")        TypeError
  , Test "typpor4"   (SrcString "input x in if x >= true then x mod 2 else 6")   TypeError
  , Test "typbo1"    (SrcString "input x in if x and true then 1 else 2")        TypeError
  , Test "typbo2"    (SrcString "input x in if false or x then 2 else 1")        TypeError
  , Test "typif1"    (SrcString "input x in if x = 2 then true else 1")          TypeError
  , Test "por1"      (SrcString "input x in if x = 10 then 2 else 0")            (Eval [10] (Value 2))
  , Test "por2"      (SrcString "input x in if x <> 2 then x else 6")            (Eval [9] (Value 9))
  , Test "por3"      (SrcString "input x in if x > 21 then x - 3 else x + 3")    (Eval [10] (Value 13))
  , Test "por4"      (SrcString "input x in if x < 6 then x + 6 else x")         (Eval [5] (Value 11))
  , Test "por5"      (SrcString "input x in if x <= 9 then x else 0")            (Eval [9] (Value 9))
  , Test "por6"      (SrcString "input x in if x >= 1 then x mod 2 else 6")      (Eval [13] (Value 1))
  , Test "bool1"     (SrcString "input x in if false or not true then x else 0") (Eval [66] (Value 0))
  , Test "bool2"     (SrcString "input x in if true and true then x else 0")     (Eval [666] (Value 666))
  , Test "let1"      (SrcString "input y in let x = 1 in y + x")                 (Eval [6] (Value 7))
  , Test "let2"      (SrcString "input y in let x = 9 + 1 in y mod x")           (Eval [11] (Value 1))
  , Test "let3div0"  (SrcString "input y in let x = 0 in y div x")               (Eval [3] RuntimeError)
  , Test "combo1"    (SrcString "input x in 1 + x - 2")            (Eval [9] (Value 8))
  , Test "combo2"    (SrcString "input x in 3 * x * 2")            (Eval [1] (Value 6))
  , Test "combo1prior"    (SrcString "input x in 4 + 3 * x")       (Eval [3] (Value 13))
  , Test "combo2prior"    (SrcString "input x in 2 * x + 9 mod 2") (Eval [10] (Value 21))
  , Test "combo3prior"    (SrcString "input x in 9 * x + x mod 3 + x div 0") (Eval [2] RuntimeError)
  ]