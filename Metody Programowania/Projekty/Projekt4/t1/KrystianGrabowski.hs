-- Wymagamy, by moduł zawierał tylko bezpieczne funkcje
{-# LANGUAGE Safe #-}
-- Definiujemy moduł zawierający rozwiązanie.
-- Należy zmienić nazwę modułu na {Imie}{Nazwisko} gdzie za {Imie}
-- i {Nazwisko} należy podstawić odpowiednio swoje imię i nazwisko
-- zaczynające się wielką literą oraz bez znaków diakrytycznych.
module KrystianGrabowski (typecheck, eval) where

-- Importujemy moduły z definicją języka oraz typami potrzebnymi w zadaniu
import AST
import DataTypes
import Data.Map

-- Funkcja sprawdzająca typy
-- Dla wywołania typecheck vars e zakładamy, że zmienne występujące
-- w vars są już zdefiniowane i mają typ int, i oczekujemy by wyrażenia e
-- miało typ int
-- UWAGA: to nie jest jeszcze rozwiązanie; należy zmienić jej definicję.

typecheck :: [Var] -> Expr p -> TypeCheckResult p
typecheck vars e = case e of
          ENum    p integer -> Ok
          EVar    p var -> if var `elem` vars then Ok else Error p "No var"
                           where p = (getData (EVar    p var))
          EBool   p bool ->  Error p "No Int return" 
                             where p = (getData (EBool p bool))
          EUnary p unaryop e1 -> if (show unaryop == "not") then Error p "No Int return" else if (pop vars vars e) && (wtype vars e == True) then Ok else Error p "No Int return"
                              where p = (getData (EUnary p unaryop e1))
          EBinary p binaryop e1 e2 -> if (binbool binaryop == False) then Error p "No Int return" else if (pop vars vars e1) && (pop vars vars e2) && (wtype vars e1) && (wtype vars e2) then Ok else Error p "No Int return"
                                    where p = (getData (EBinary p binaryop e1 e2))
          ELet    p var e1 e2 -> case (wtype vars e1) of
                                     True -> if (pop vars vars e1 == True) then if (wtype (vars ++ [var]) e2 == True) && (pop (vars ++ [var]) (vars ++ [var])  e2 == True) then Ok else Error p "No Int return" else Error p "No Int return" where p = (getData (ELet    p var e1 e2))
                                     False -> if (pop vars vars e1 == True) then if (wtype (vars) e2 == True) && (pop (vars ++ [var]) vars e2 == True) then Ok else Error p "No Int return" else Error p "No Int return" where p = (getData (ELet    p var e1 e2))
          EIf     p e1 e2 e3 -> if (wtype vars e1 == False) && (wtype vars e2 == True) && (wtype vars e3 == True) then if (pop vars vars e1 == True) && (pop vars vars e2 == True) && (pop vars vars e3 == True) then Ok else Error p "No Int return"  else Error p "No Int return"
                                    where p = (getData (EIf     p e1 e2 e3))
pop all vars e = case e of
          ENum    p integer -> True
          EVar    p var -> if var `elem` all then True else False
          EBool   p bool -> True
          EUnary p unaryop e -> case (show unaryop) of 
                                    "not" -> if (wtype vars e == False) && (pop all vars e == True) then True else False
                                    "-" -> if (wtype vars e == True) && (pop all vars e == True) then True else False
                                    otherwise -> False
          EBinary p binaryop e1 e2 -> case (binbool2 binaryop) of
                                          "ii" -> if (wtype vars e1 == True) && (wtype vars e2 == True) &&
                                                  (pop all vars e1 == True) && (pop all vars e2 == True) then True else False
                                          "ib" -> if (wtype vars e1 == True) && (wtype vars e2 == True) &&
                                                  (pop all vars e1 == True) && (pop all vars e2 == True) then True else False
                                          otherwise -> if (wtype vars e1 == False) && (wtype vars e2 == False) &&
                                                  (pop all vars e1 == True) && (pop all vars e2 == True) then True else False
          ELet    p var e1 e2 -> if (wtype vars e1 == True) then if (pop (all ++ [var]) (vars ++ [var]) e2 == True) then True else False else if (pop (all ++ [var]) vars e2 == True) then True else False
          EIf     p e1 e2 e3 -> if (wtype vars e1 == True) then False else if (pop all vars e1 == True) && (pop all vars e2 == True) && (pop all vars e3 == True) && (wtype vars e2 == wtype vars e3) then True else False 

wtype vars e = case e of
          ENum    p integer -> True
          EVar    p var -> if var `elem` vars then True else False
          EBool   p bool -> False
          EUnary p unaryop e -> if (show unaryop == "not") then False else True
          EBinary p binaryop e1 e2 -> if (binbool binaryop == True) then True else False
          EIf     p e1 e2 e3 -> if (wtype vars e2 == True) then True else False
          otherwise -> True
binbool opbin = case (show opbin) of
                     "+" -> True
                     "-" -> True
                     "*" -> True
                     "div" -> True
                     "mod" -> True
                     otherwise -> False
binbool2 opbin = case (show opbin) of
                     "+" -> "ii"
                     "-" -> "ii"
                     "*" -> "ii"
                     "div" -> "ii"
                     "mod" -> "ii"
                     "and" -> "bb"
                     "or" -> "bb"
                     otherwise -> "ib"
-- Funkcja obliczająca wyrażenia
-- Dla wywołania eval input e przyjmujemy, że dla każdej pary (x, v)
-- znajdującej się w input, wartość zmiennej x wynosi v.
-- Możemy założyć, że wyrażenie e jest dobrze typowane, tzn.
-- typecheck (map fst input) e = Ok
-- UWAGA: to nie jest jeszcze rozwiązanie; należy zmienić jej definicję.

eval :: [(Var,Integer)] -> Expr p -> EvalResult
eval input e = case e of
          ENum    p integer -> Value integer
          EVar    p var  -> Value (tupl input var)
          EUnary p unaryop e1 -> if (zerochck input e) then Value (num_c input input e) else RuntimeError
          EBinary p binaryop e1 e2 -> case binaryop of
                               BAdd -> if (zerochck input e) then Value (num_c input input e) else RuntimeError
                               BSub -> if (zerochck input e) then Value (num_c input input e) else RuntimeError
                               BMul -> if (zerochck input e) then Value (num_c input input e) else RuntimeError
                               BDiv -> if (zerochck input e) then Value (num_c input input e) else RuntimeError
                               BMod -> if (zerochck input e) then Value (num_c input input e) else RuntimeError
          ELet    p var e1 e2 -> if (zerochck input e) then Value (num_c input input e) else RuntimeError
          EIf     p e1 e2 e3 -> if (zerochck input e) then Value (num_c input input e) else RuntimeError 
          otherwise -> Value 10

zerochck input e = case e of
          ENum    p integer -> True
          EVar    p var  -> True
          EBool   p bool -> True
          EUnary p unaryop e1 -> (zerochck input e1)
          EBinary p binaryop e1 e2 -> case binaryop of
                               BDiv -> if (num_c input input e2 == 0) then False else ((zerochck input e1) && (zerochck input e2))
                               BMod -> if (num_c input input e2 == 0) then False else ((zerochck input e1) && (zerochck input e2))
                               otherwise -> ((zerochck input e1) && (zerochck input e2))
          ELet   p var e1 e2 -> (zerochck input e1) && (zerochck input e2)
          EIf    p e1 e2 e3 -> if (zerochck input e1) && (bool_c input input e1 == True) then (zerochck input e2) else (zerochck input e3)

bool_c all input e = case e of
          EBool   p bool -> bool
          EVar    p var  -> if tuplb all var then True else False
          EUnary p unaryop e1 -> not(bool_c all input e1)
          EBinary p binaryop e1 e2 -> case binaryop of
                                          BEq -> (num_c all input e1) == (num_c all input e2)
                                          BNeq -> (num_c all input e1) /= (num_c all input e2)
                                          BLt -> (num_c all input e1) < (num_c all input e2)
                                          BGt -> (num_c all input e1) > (num_c all input e2)
                                          BLe -> (num_c all input e1) <= (num_c all input e2)
                                          BGe -> (num_c all input e1) >= (num_c all input e2)
                                          BAnd -> (bool_c all input e1) && (bool_c all input e2)
                                          BOr -> (bool_c all input e1) || (bool_c all input e2)
          ELet    p var e1 e2 -> if (evtype all input e1 == True) then bool_c (addfin all (var,num_c all input e1)) (addfin input (var,num_c all input e1)) e2 else
                                     if (bool_c all input e1 == True) then bool_c (addfin all (var,111)) input e2 else bool_c all input e2
          EIf   p e1 e2 e3 -> if (bool_c all input e1) then (bool_c all input e2) else (bool_c all input e3)
          otherwise -> True


num_c all input e = case e of
          ENum    p integer -> integer
          EVar    p var  -> tupl input var
          EUnary p unaryop e1 -> -(num_c all input e1)
          EBinary p binaryop e1 e2 -> case binaryop of
                                          BAdd -> (num_c all input e1) + (num_c all input e2)
                                          BSub -> (num_c all input e1) - (num_c all input e2)
                                          BMul -> (num_c all input e1) * (num_c all input e2)
                                          BDiv -> (num_c all input e1) `div` (num_c all input e2)
                                          BMod -> (num_c all input e1) `mod` (num_c all input e2)
          ELet    p var e1 e2 -> if (evtype all input e1 == True) then num_c (addfin all (var,num_c all input e1)) (addfin input (var,num_c all input e1)) e2 else
                                     if (bool_c all input e1 == True) then num_c (addfin all (var,111)) input e2 else num_c all input e2
          EIf   p e1 e2 e3 -> if (bool_c all input e1) then (num_c all input e2) else (num_c all input e3)
          otherwise -> 1

tupl ((a,b):xs) s = if (a == s) then b else tupl xs s
tupl [] s = 1010101

tuplb ((a,b):xs) s = if (a == s) then True else tuplb xs s
tuplb [] s = False

duplikex ((a,b):xs) (ad,bd) = if (a == ad) then True else duplikex xs (ad,bd)
duplikex [] (ad,bd) = False

addfin input el = case (duplikex input el) of
            False -> input ++ [el]
            True -> chng input el

chng ((a,b):xs) (ad,bd) = if (a == ad) then [(ad,bd)] ++ xs else [(a,b)] ++ chng xs (ad,bd)
chng [(a,b)] (ad,bd) = [(ad,bd)]

evtype all input e = case e of
          ENum    p integer -> True
          EVar    p var -> if (tuplb all var) && (tuplb input var) then True else False
          EBool   p bool -> False
          EUnary p unaryop e -> if (show unaryop == "not") then False else True
          EBinary p binaryop e1 e2 -> if (binbool binaryop == True) then True else False
          ELet    p var e1 e2 -> if (evtype all input e2 == True) then True else False
          EIf     p e1 e2 e3 -> if (evtype all input e2 == True) then True else False
          otherwise -> True









  