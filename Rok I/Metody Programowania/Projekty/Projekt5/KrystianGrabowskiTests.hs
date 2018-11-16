-- Wymagamy, by modu³ zawiera³ tylko bezpieczne funkcje
{-# LANGUAGE Safe #-}
-- Definiujemy modu³ zawieraj¹cy testy.
-- Nale¿y zmieniæ nazwê modu³u na {Imie}{Nazwisko}Tests gdzie za {Imie}
-- i {Nazwisko} nale¿y podstawiæ odpowiednio swoje imiê i nazwisko
-- zaczynaj¹ce siê wielk¹ liter¹ oraz bez znaków diakrytycznych.
module KrystianGrabowskiTests(tests) where

-- Importujemy modu³ zawieraj¹cy typy danych potrzebne w zadaniu
import DataTypes

-- Lista testów do zadania
-- Nale¿y uzupe³niæ jej definicjê swoimi testami
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

  , Test "lista"    (SrcString "snd(2,3)") (Eval [] (Value 3))
  , Test "prosty"   (SrcFile "prosty.pp5") (Eval [2] (Value 2))
  , Test "fibon"    (SrcFile "aplikfib.pp5")       (Eval [5] (Value 5))
  , Test "addon"    (SrcFile "aplikadd1.pp5")      (Eval [5] (Value 6))
  , Test "sqrt"     (SrcFile "apliksq.pp5")        (Eval [4] (Value 16))
  , Test "mod2"     (SrcFile "aplikmod2.pp5")      (Eval [9] (Value 1))
  , Test "digsum"   (SrcFile "aplikdigsum.pp5")    (Eval [123] (Value 6))
  , Test "pow"      (SrcFile "aplikpow.pp5")       (Eval [6] (Value 720))
  , Test "fus"      (SrcFile "aplikimv1.pp5")      (Eval [111] (Value 97))
  , Test "unitck"   (SrcFile "aplikun.pp5")        (Eval [6] (Value 30))
  , Test "TEEEEEEEEE"   (SrcString "fst(false,true)") TypeError
  , Test "pairv1"   (SrcString "let x = (6,9) in fst(x)") (Eval [] (Value 6))
  , Test "pairv2"   (SrcString "let x = (6,9) in snd(x)") (Eval [] (Value 9))
  , Test "pairv3"   (SrcString "let x = (6,9) in fst(x) + snd(x)") (Eval [] (Value 15))
  , Test "pairv4"   (SrcString "input x in if x > 66 then fst(8,5) else snd(8,5)") (Eval [60] (Value 5))
  , Test "pairv5"   (SrcString "input x y in if snd(6,y) > x then fst(x,8) else 1") (Eval [4,5] (Value 4))
  , Test "pairv6"   (SrcString "input z y in let x = (z,y) in fst(x) * snd(x)") (Eval [6,11] (Value 66))            
  , Test "pairv7"   (SrcString "input z y in let x = (z,y) in fst(x) div snd(x)") (Eval [4,2] (Value 2))
  , Test "pairv8"   (SrcString "input z y in let x = (y,z) in fst(x) mod snd(x)") (Eval [2,9] (Value 1))
  , Test "pairv9"   (SrcString "input a b c d in if fst(a,b) = fst(c,d) then snd(a,b) else snd(c,d)") (Eval [6,4,6,7] (Value 4)) 
  , Test "pair1" (SrcFile "pairfsa.pp5")        (Eval [10] (Value 10))
  , Test "pair2" (SrcFile "pairfsb.pp5")        (Eval [10] (Value 1))
  , Test "pair3" (SrcFile "pairfsc.pp5")        (Eval [2,2] (Value 2))
  , Test "pair4" (SrcFile "pairfsd.pp5")        (Eval [1,2,3,1] (Value 6))
  , Test "pairbb" (SrcFile "pairbul.pp5")       (Eval [7] (Value 123))
  , Test "pairbi" (SrcFile "pairbi.pp5")       (Eval [8] (Value 8))
  , Test "list1" (SrcFile "listempty.pp5")      (Eval [2] (Value 2))
  , Test "list2" (SrcFile "hwmany.pp5")         (Eval [1,2,3,4] (Value 2))
  , Test "zerov1" (SrcString "input z in let x = (z,0) in fst(x) div snd(x)") (Eval [3] RuntimeError)
  , Test "zerov2" (SrcString "input z y in let x = (z,y) in fst(x) div snd(x)") (Eval [77,0] RuntimeError)
  , Test "type1"  (SrcFile "types1.pp5")            TypeError
  , Test "type2"  (SrcFile "types2.pp5")            TypeError
  , Test "type3"  (SrcFile "types3.pp5")            TypeError
  , Test "type4"  (SrcFile "types4.pp5")            TypeError
  , Test "type5"  (SrcFile "types5.pp5")            TypeError
  ]