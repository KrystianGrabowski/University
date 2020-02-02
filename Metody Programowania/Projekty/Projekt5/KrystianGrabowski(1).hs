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

-- Funkcja sprawdzająca typy
-- Dla wywołania typecheck fs vars e zakładamy, że zmienne występujące
-- w vars są już zdefiniowane i mają typ int, i oczekujemy by wyrażenia e
-- miało typ int
-- UWAGA: to nie jest jeszcze rozwiązanie; należy zmienić jej definicję.
typecheck :: [FunctionDef p] -> [Var] -> Expr p -> TypeCheckResult p
typecheck fs vars e = case e of
          ENum    p integer -> Ok
          EVar    p var -> if var `elem` vars then Ok else Error p "No var"
                           where p = (getData (EVar    p var))
          EBool   p bool ->  Error p "No Int return" 
                             where p = (getData (EBool p bool))
          EUnary p unaryop e1 -> if (show unaryop == "not") then Error p "No Int return" else if (pop fs vars vars e) && (wtype fs vars e == TInt) then Ok else Error p "No Int return"
                              where p = (getData (EUnary p unaryop e1))
          EBinary p binaryop e1 e2 -> if (binbool binaryop == False) then Error p "No Int return" else if (pop fs vars vars e1) && (pop fs vars vars e2) && (wtype fs vars e1 == TInt) && (wtype fs vars e2 == TInt) then Ok else Error p "No Int return"
                                    where p = (getData (EBinary p binaryop e1 e2))
          ELet    p var e1 e2 -> case (wtype fs vars e1) of
                                     TInt -> if (pop fs vars vars e1 == True) then if (wtype fs (vars ++ [var]) e2 == TInt) && (pop fs (vars ++ [var]) (vars ++ [var])  e2 == True) 
                                                     then Ok else Error p "No Int return" else Error p "No Int return" where p = (getData (ELet    p var e1 e2))
                                     TBool -> if (pop fs vars vars e1 == True) then if (wtype fs vars e2 == TInt) && (pop fs (vars ++ [var]) vars e2 == True) then Ok 
                                                      else Error p "No Int return" else Error p "No Int return" where p = (getData (ELet    p var e1 e2))
                                     TPair x y -> if (pop fs vars vars e1 == True) then case (x,y) of
                                                      (TInt,TInt) -> if (wtype fs (vars ++ [var]) e2 == TInt) && (pop fs (vars ++ [var]) (vars ++ [var])  e2 == True) then Ok else Error p "No Int return" where p = (getData (ELet    p var e1 e2))
                                                      (TBool,TBool) -> if (wtype fs vars e2 == TInt) && (pop fs (vars ++ [var]) vars  e2 == True) then Ok else Error p "No Int return" where p = (getData (ELet    p var e1 e2))
                                                      otherwise -> if (wtype fs vars e2 == TInt) && (pop fs (vars ++ [var]) vars  e2 == True) then Ok else Error p "No Int return" where p = (getData (ELet    p var e1 e2))
                                                  else Error p "No Int return" where p = (getData (ELet    p var e1 e2))
                                     TUnit -> if (wtype fs vars e2 == TInt) && (pop fs vars vars  e2 == True) then Ok else Error p "No Int return" where p = (getData (ELet    p var e1 e2))
                                     TList x -> if (wtype fs (vars ++ [var]) e2 == TInt) || (pop fs (vars ++ [var]) (vars ++ [var])  e2 == True) then Ok else Error p "No Int return" where p = (getData (ELet    p var e1 e2))
          EIf     p e1 e2 e3 -> if (wtype fs vars e1 == TBool) && (wtype fs vars e2 == TInt) && (wtype fs vars e3 == TInt) then
                                    if (pop fs vars vars e1 == True) && (pop fs vars vars e2 == True) && (pop fs vars vars e3 == True)
                                         then Ok else Error p "No Int return"  else Error p "No Int return"
                                    where p = (getData (EIf     p e1 e2 e3))
          EApp   p fsym e -> if (intret fs fsym == True ) && (finputtype fs vars e fsym == True)  then Ok else Error p "No Int return"
                                    where p = (getData (EApp  p fsym e))
          EUnit   p -> Error p "No Int return"
                                    where p = (getData (EUnit  p))
          EPair  p e1 e2 -> Error p "No Int return"
                                    where p = (getData (EPair  p e1 e2))
          EFst  p e -> if (projtype fs vars e 'f' == TInt) then Ok else Error p "No Int return"
                                    where p = (getData (EFst  p e))
          ESnd  p e -> if (projtype fs vars e 's' == TInt) then Ok else Error p "No Int return"
                                    where p = (getData (ESnd  p e))
          ENil p t -> Error p "No Int return"
                                    where p = (getData (ENil  p t))
          ECons   p e1 e2 -> Error p "No Int return"
                                    where p = (getData (ECons  p e1 e2)) 
          EMatchL p ee nc (v1,v2,e) -> if (wtype fs vars nc == TInt) && (wtype fs vars e == TInt)
                                          && (pop fs vars vars nc == True) && (pop fs (vars ++ [v1] ++ [v2]) vars e == True)
                                             then Ok else Error p "No Int return"
                                    where p = (getData (EMatchL p ee nc (v1,v2,e)))


intret ((FunctionDef a b c d e f ):xs) nm = if ((b == nm) && (e == TInt)) then True else intret xs nm 
intret [] nm = False

finputtype ((FunctionDef a b c d e f ):xs) vars expr nm = if (b == nm) && (wtype ((FunctionDef a b c d e f ):xs) vars expr == d) then True 
                                                               else finputtype xs vars expr nm 
finputtype [] vars expr nm = False

pop fs all vars e = case e of
          ENum    p integer -> True
          EVar    p var -> if (var `elem` all) || (elemfs fs var) then True else False
          EBool   p bool -> True
          EUnary p unaryop e -> case (show unaryop) of 
                                    "not" -> if (wtype fs vars e == TBool) && (pop fs all vars e == True) then True else False
                                    "-" -> if (wtype fs vars e == TInt) && (pop fs all vars e == True) then True else False
                                    otherwise -> False
          EBinary p binaryop e1 e2 -> case (binbool2 binaryop) of
                                          "ii" -> if (wtype fs vars e1 == TInt) && (wtype fs vars e2 == TInt) &&
                                                  (pop fs all vars e1 == True) && (pop fs all vars e2 == True) then True else False
                                          "ib" -> if (wtype fs vars e1 == TInt) && (wtype fs vars e2 == TInt) &&
                                                  (pop fs all vars e1 == True) && (pop fs all vars e2 == True) then True else False
                                          otherwise -> if (wtype fs vars e1 == TBool) && (wtype fs vars e2 == TBool) &&
                                                  (pop fs all vars e1 == True) && (pop fs all vars e2 == True) then True else False
          ELet    p var e1 e2 -> if (wtype fs vars e1 == TInt) then if (pop fs (all ++ [var]) (vars ++ [var]) e2 == True) then True 
                                                    else False else if (pop fs (all ++ [var]) vars e2 == True) then True else False
          EIf     p e1 e2 e3 -> if (wtype fs vars e1 == TInt) then False else 
                                   if (pop fs all vars e1 == True) && (pop fs all vars e2 == True) 
                                     && (pop fs all vars e3 == True) && (wtype fs vars e2 == wtype fs vars e3) 
                                     then True else  False 
          EApp    p fsym e ->if (wtype fs vars e /= TUnit) && (funktype fs all vars fsym) && (finputtype fs vars e fsym  == True)  then True 
                                 else if (wtype fs vars e == TUnit) then True else False
          EUnit   p -> True
          EPair   p e1 e2 -> if (pop fs all vars e1) && (pop fs all vars e2) then True else False
          EFst    p e -> if (pop fs all vars e) then True else False
          ESnd    p e -> if (pop fs all vars e) then True else False
          ENil    p t -> True
          ECons   p e1 e2 -> if (pop fs all vars e1) && (pop fs all vars e2) then True else False
          EMatchL p ee nc (v1,v2,e) -> if (pop fs all vars ee) && (pop fs all vars nc) && (pop fs all vars e)  && (wtype fs vars nc == wtype fs vars e)
                                          then True else False

elemfs ((FunctionDef a b c d e f ):xs) var = if (var == c) then True else elemfs xs var
elemfs [] var = False
funktype ((FunctionDef a b c d e f ):xs) all vars nm = if (b == nm) && pop ((FunctionDef a b c d e f ):xs) all vars f then True else funktype xs all vars nm 
funktype [] all vars nm = True

wtype :: [FunctionDef p] -> [Var] -> Expr p -> Type
wtype fs vars e = case e of
          ENum    p integer -> TInt
          EVar    p var -> if var `elem` vars then TInt else TBool
          EBool   p bool -> TBool
          EUnary p unaryop e -> if (show unaryop == "not") then TBool else TInt
          EBinary p binaryop e1 e2 -> if (binbool binaryop == True) then TInt else TBool
          EIf     p e1 e2 e3 -> if (wtype fs vars e2 == TInt) then TInt else TBool
          EApp    p fsym e -> typretf fs vars e fsym
          EUnit   p -> TUnit
          EPair   p e1 e2 -> TPair (wtype fs vars e1) (wtype fs vars e2)
          EFst    p e -> projtype fs vars e 'f'
          ESnd    p e -> projtype fs vars e 's'
          ENil    p t -> TList t
          ECons   p e1 e2 -> TList (wtype fs vars e1)
          EMatchL p ee nc (v1,v2,e) -> (wtype fs vars nc)
          otherwise -> TInt



pairtype ((FunctionDef a b c d e f ):xs) vars var t = if (b == var) then case d of
          TPair x y -> if (t == 'f') then x else y
          otherwise -> TInt
                      else pairtype xs vars var t
pairtype [] vars var t = if var `elem` vars then TInt else TBool

projtype fs vars ea t = if (t == 'f') then case ea of
          EPair  p e1 e2 -> wtype fs vars e1
          EVar p var -> pairtype fs vars var t
          otherwise -> TUnit
          else case ea of
          EPair p e1 e2 -> wtype fs vars e2
          EVar p var -> pairtype fs vars var t
          otherwise -> TUnit


typretf :: [FunctionDef p] -> [Var] -> Expr p -> FSym -> Type
typretf  ((FunctionDef a b c d e f ):xs) vars e1 nm = if (nm == b) then case e of
                     TInt -> TInt
                     TBool -> TBool
                     TUnit -> TUnit
                     TPair x y -> TPair x y
                     TList x -> TList x
                                    else typretf xs vars e1 nm
typretf [] vars e1 nm = TInt

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
-- Dla wywołania eval fs input e przyjmujemy, że dla każdej pary (x, v)
-- znajdującej się w input, wartość zmiennej x wynosi v.
-- Możemy założyć, że definicje funckcji fs oraz wyrażenie e są dobrze
-- typowane, tzn. typecheck fs (map fst input) e = Ok
-- UWAGA: to nie jest jeszcze rozwiązanie; należy zmienić jej definicję.

-- Funkcja obliczająca wyrażenia
-- Dla wywołania eval input e przyjmujemy, że dla każdej pary (x, v)
-- znajdującej się w input, wartość zmiennej x wynosi v.
-- Możemy założyć, że wyrażenie e jest dobrze typowane, tzn.
-- typecheck (map fst input) e = Ok
-- UWAGA: to nie jest jeszcze rozwiązanie; należy zmienić jej definicję.

eval :: [FunctionDef p] -> [(Var,Integer)] -> Expr p -> EvalResult
eval fs input e = case e of
          ENum    p integer -> Value integer
          EVar    p var  -> Value (tupl input var)
          EUnary p unaryop e1 -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
          EBinary p binaryop e1 e2 -> case binaryop of
                               BAdd -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
                               BSub -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
                               BMul -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
                               BDiv -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
                               BMod -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
          ELet    p var e1 e2 -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
          EIf     p e1 e2 e3 -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
          EApp    p fsym e1 -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
          EFst    p e1 -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
          ESnd    p e1 -> if (zerochck fs input e) then Value (num_c fs input input e) else RuntimeError
          otherwise -> Value 10

zerochck fs input e = case e of
          ENum    p integer -> True
          EVar    p var  -> True
          EBool   p bool -> True
          EUnary p unaryop e1 -> (zerochck fs input e1)
          EBinary p binaryop e1 e2 -> case binaryop of
                               BDiv -> if (num_c fs input input e2 == 0) then False else ((zerochck fs input e1) && (zerochck fs input e2))
                               BMod -> if (num_c fs input input e2 == 0) then False else ((zerochck fs input e1) && (zerochck fs input e2))
                               otherwise -> ((zerochck fs input e1) && (zerochck fs input e2))
          ELet   p var e1 e2 -> (zerochck fs input e1) && (zerochck fs input e2)
          EIf    p e1 e2 e3 -> if (zerochck fs input e1) && (bool_c fs input input e1 == True) then (zerochck fs input e2) 
                                   else (zerochck fs input e3)
          EApp    p fsym e1 -> (zerochck fs input e1) && (funk_zerochck fs fs input input e1 fsym)
          EPair    p e1 e2 -> (zerochck fs input e1) && (zerochck fs input e1)
          EFst    p e1 -> (zerochck fs input e1)
          ESnd    p e1 -> (zerochck fs input e1) 
          otherwise -> True

funk_zerochck ((FunctionDef a b c d e f ):xs) fs all input e1 nm = if (b == nm) 
                                                                      then zerochck ((FunctionDef a b c d e f ):xs) (addfin input (c,num_c fs all input e1)) f 
                                                                          else funk_zerochck xs fs all input e1 nm
funk_zerochck [] fs all input e1 nm = False



el_pair_gti fs all input e t = if (t == 'f') then case e of
          EPair p e1 e2 ->  num_c fs all input e1 
          EVar p var -> tupl input var
          otherwise -> 1
               else case e of
          EPair p e1 e2 -> num_c fs all input e2
          EVar p var -> tupl input var
          otherwise -> 1

el_pair_gtb fs all input e t = if (t == 'f') then case e of
          EPair p e1 e2 ->  bool_c fs all input e1 
          otherwise -> True
               else case e of
          EPair p e1 e2 -> bool_c fs all input e2
          otherwise -> True


bool_c fs all input e = case e of
          EBool   p bool -> bool
          EVar    p var  -> if tuplb all var then True else False
          EUnary p unaryop e1 -> not(bool_c fs all input e1)
          EBinary p binaryop e1 e2 -> case binaryop of
                                          BEq -> (num_c fs all input e1) == (num_c fs all input e2)
                                          BNeq -> (num_c fs all input e1) /= (num_c fs all input e2)
                                          BLt -> (num_c fs all input e1) < (num_c fs all input e2)
                                          BGt -> (num_c fs all input e1) > (num_c fs all input e2)
                                          BLe -> (num_c fs all input e1) <= (num_c fs all input e2)
                                          BGe -> (num_c fs all input e1) >= (num_c fs all input e2)
                                          BAnd -> (bool_c fs all input e1) && (bool_c fs all input e2)
                                          BOr -> (bool_c fs all input e1) || (bool_c fs all input e2)
          ELet    p var e1 e2 -> case (ttypes all input e1) of
                                  "h" -> if (evtype all input e1 == True) then bool_c fs (addfin all (var,num_c fs all input e1)) (addfin input (var,num_c fs all input e1)) e2 
                                            else if (bool_c fs all input e1 == True) then bool_c fs (addfin all (var,111)) input e2 else bool_c fs all input e2
                                  otherwise -> flet_cb fs all input e1 e2
          EIf   p e1 e2 e3 -> if (bool_c fs all input e1) then (bool_c fs all input e2) else (bool_c fs all input e3)
          EApp    p fsym e1 -> (zerochck fs input e1) && (funk_zerochck fs fs all input e1 fsym)
          EFst    p e1 -> (el_pair_gtb fs all input e1 'f')
          ESnd    p e1 -> (el_pair_gtb fs all input e1 's')
          otherwise -> True


num_c fs all input e = case e of
          ENum    p integer -> integer
          EVar    p var  -> tupl input var
          EUnary p unaryop e1 -> -(num_c fs all input e1)
          EBinary p binaryop e1 e2 -> case binaryop of
                                          BAdd -> (num_c fs all input e1) + (num_c fs all input e2)
                                          BSub -> (num_c fs all input e1) - (num_c fs all input e2)
                                          BMul -> (num_c fs all input e1) * (num_c fs all input e2)
                                          BDiv -> (num_c fs all input e1) `div` (num_c fs all input e2)
                                          BMod -> (num_c fs all input e1) `mod` (num_c fs all input e2)
          ELet    p var e1 e2 -> case (ttypes all input e1) of
                                     "h" -> if (evtype all input e1 == True) then num_c fs (addfin all (var,num_c fs all input e1)) (addfin input (var,num_c fs all input e1)) e2 
                                               else if (bool_c fs all input e1 == True) then num_c fs (addfin all (var,111)) input e2 
                                                   else num_c fs all input e2
                                     otherwise -> flet_c fs all input e1 e2
          EIf   p e1 e2 e3 -> if (bool_c fs all input e1) then (num_c fs all input e2) else (num_c fs all input e3)
          EApp    p fsym e1 -> let q = (num_c fs all input e1) in (funk_counti fs fs all input q fsym)
          EFst    p e1 -> (el_pair_gti fs all input e1 'f')
          ESnd    p e1 -> (el_pair_gti fs all input e1 's')
          otherwise -> 1

gtv fs all input ee t = case ee of
               EPair p e1 e2 -> if (t == 'f') then num_c fs all input e1 else num_c fs all input e2
               otherwise -> 1

gtvb fs all input ee t = case ee of
               EPair p e1 e2 -> if (t == 'f') then bool_c fs all input e1 else bool_c fs all input e2
               otherwise -> True

flet_cb fs all input e1 e2 = case e2 of
          EBool   p bool -> bool
          EVar    p var  -> if tuplb all var then True else False
          EUnary p unaryop e1a -> not(flet_cb fs all input e1 e1a)
          EBinary p binaryop e1a e2a -> case binaryop of
                                          BEq -> (num_c fs all input e1a) == (num_c fs all input e2a)
                                          BNeq -> (num_c fs all input e1a) /= (num_c fs all input e2a)
                                          BLt -> (num_c fs all input e1a) < (num_c fs all input e2a)
                                          BGt -> (num_c fs all input e1a) > (num_c fs all input e2a)
                                          BLe -> (num_c fs all input e1a) <= (num_c fs all input e2a)
                                          BGe -> (num_c fs all input e1a) >= (num_c fs all input e2a)
                                          BAnd -> (flet_cb fs all input e1 e1a) && (flet_cb fs all input e1 e2a)
                                          BOr -> (flet_cb fs all input e1 e1a) || (flet_cb fs all input e1 e2a)
          ELet    p var e1a e2a -> if (evtype all input e1 == True) then flet_cb fs (addfin all (var,num_c fs all input e1)) (addfin input (var,num_c fs all input e1)) e1 e2a 
                                    else if (flet_cb fs all input e1 e1a == True) then flet_cb fs (addfin all (var,111)) input e1 e2a else flet_cb fs all input e1 e2a
          EIf   p e1a e2a e3a -> if (flet_cb fs all input e1 e1a) then (flet_cb fs all input e1 e2a) else (flet_cb fs all input e1 e3a)
          EApp    p fsym e1a -> (zerochck fs input e1) && (funk_zerochck fs fs all input e1 fsym)
          EFst    p e1a -> gtvb fs all input e1 'f'
          ESnd    p e1a -> gtvb fs all input e1 's'
          otherwise -> True

flet_c fs all input e1 e2 = case e2 of
          ENum    p integer -> integer
          EVar    p var  -> tupl input var
          EUnary p unaryop e1a -> -(flet_c fs all input e1 e1a )
          EBinary p binaryop e1a e2a -> case binaryop of
                                          BAdd -> (flet_c fs all input e1 e1a) + (flet_c fs all input e1 e2a)
                                          BSub -> (flet_c fs all input e1 e1a) - (flet_c fs all input e1 e2a)
                                          BMul -> (flet_c fs all input e1 e1a) * (flet_c fs all input e1 e2a)
                                          BDiv -> (flet_c fs all input e1 e1a) `div` (flet_c fs all input e1 e2a)
                                          BMod -> (flet_c fs all input e1 e1a) `mod` (flet_c fs all input e1 e2a)
          ELet    p var e1a e2a -> if (evtype all input e1 == True) then flet_c fs (addfin all (var,flet_c fs all input e1 e1a)) (addfin input (var,num_c fs all input e1a)) e1 e2a else
                                     if (bool_c fs all input e1 == True) then flet_c fs (addfin all (var,111)) input e1 e2a else 
                                          flet_c fs all input e1 e2a
          EIf   p e1a e2a e3a -> if (bool_c fs all input e1) then (flet_c fs all input e1 e2a) else (flet_c fs all input e1 e3a)
          EApp    p fsym e1a -> let q = (flet_c fs all input e1 e1a) in (funk_counti fs fs all input q fsym)
          EFst    p e1a -> gtv fs all input e1 'f'
          ESnd    p e1a -> gtv fs all input e1 's'
          otherwise -> 1

funk_counti ((FunctionDef a b c d e f ):xs) fs all input w nm = if (nm == b) then num_c fs (addfin all (c,w)) (addfin input (c,w)) f 
                                                                    else funk_counti xs fs all input w nm
funk_counti [] fs all input arg nm = 1

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

ttypes all input e = case e of
          EPair p e1 e2 -> case (evtype all input e1) of
                                     True -> if (evtype all input e2) then "ii" else "ib"
                                     False ->  if (evtype all input e2) then "bi" else "bb"
          otherwise -> "h"
evtype all input e = case e of
          ENum    p integer -> True
          EVar    p var -> if (tuplb all var) && (tuplb input var) then True else False
          EBool   p bool -> False
          EUnary p unaryop e -> if (show unaryop == "not") then False else True
          EBinary p binaryop e1 e2 -> if (binbool binaryop == True) then True else False
          ELet    p var e1 e2 -> if (evtype all input e2 == True) then True else False
          EIf     p e1 e2 e3 -> if (evtype all input e2 == True) then True else False
          otherwise -> True









  
