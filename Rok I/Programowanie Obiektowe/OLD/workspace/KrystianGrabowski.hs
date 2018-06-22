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

finputtype ((FunctionDef a b c d e f ):xs) vars expr nm = if (b == nm) && (wtype ((FunctionDef a b c d e f ):xs) vars expr == d) then True else finputtype xs vars expr nm 
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
          ELet    p var e1 e2 -> if (wtype fs vars e1 == TInt) then if (pop fs (all ++ [var]) (vars ++ [var]) e2 == True) then True else False else if (pop fs (all ++ [var]) vars e2 == True) then True else False
          EIf     p e1 e2 e3 -> if (wtype fs vars e1 == TInt) then False else 
                                   if (pop fs all vars e1 == True) && (pop fs all vars e2 == True) 
                                     && (pop fs all vars e3 == True) && (wtype fs vars e2 == wtype fs vars e3) 
                                     then True else  False 
          EApp    p fsym e -> (funktype fs all vars fsym) && (finputtype fs vars e fsym  == True)
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
dblii = [("p",2,2)]
dblbb = [("p",True,True)]
dblib = [("p",8,True)]
dblbi = [("p",True,8)]

eval :: [FunctionDef p] -> [(Var,Integer)] -> Expr p -> EvalResult
eval fs input e = case e of
          ENum    p integer -> Value integer
          EVar    p var  -> Value (tupl input var)
          EUnary p unaryop e1 -> if (zerochck fs input e) then Value (num_c input input e) else RuntimeError
          EBinary p binaryop e1 e2 -> case binaryop of
                               BAdd -> if (zerochck fs input e) then Value (num_c input input e) else RuntimeError
                               BSub -> if (zerochck fs input e) then Value (num_c input input e) else RuntimeError
                               BMul -> if (zerochck fs input e) then Value (num_c input input e) else RuntimeError
                               BDiv -> if (zerochck fs input e) then Value (num_c input input e) else RuntimeError
                               BMod -> if (zerochck fs input e) then Value (num_c input input e) else RuntimeError
          ELet    p var e1 e2 -> if (zerochck fs input e) then Value (num_c input input e) else RuntimeError
          EIf     p e1 e2 e3 -> if (zerochck fs input e) then Value (num_c input input e) else RuntimeError
          EApp    p fsym e1   -> if (zerochck fs input e) then Value (num_c input input e) else RuntimeError
          otherwise -> Value 10




zerochck fs input e = case e of
          ENum    p integer -> True
          EVar    p var  -> True
          EBool   p bool -> True
          EUnary p unaryop e1 -> (zerochck fs input e1)
          EBinary p binaryop e1 e2 -> case binaryop of
                               BDiv -> if (num_c input input e2 == 0) then False else ((zerochck fs input e1) && (zerochck fs input e2))
                               BMod -> if (num_c input input e2 == 0) then False else ((zerochck fs input e1) && (zerochck fs input e2))
                               otherwise -> ((zerochck fs input e1) && (zerochck fs input e2))
          ELet   p var e1 e2 -> (zerochck fs input e1) && (zerochck fs input e2)
          EIf    p e1 e2 e3 -> if (zerochck fs input e1) && (bool_c input input e1 == True) then (zerochck fs input e2) else (zerochck fs input e3)
          EApp   p fsym e1 -> (ins_zero fs input fsym) && (zerochck fs input e1)
          otherwise -> True

ins_zero ((FunctionDef a b c d e f ):xs) input fsym = if (fsym == b) then zerochck ((FunctionDef a b c d e f ):xs) input f else ins_zero xs input fsym
ins_zero [] input fsym = False

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
          ELet    p var e1 e2 -> case pairT e1 of 
                          otherwise -> if (evtype all input e1 == True) then num_c (addfin all (var,num_c all input e1)) (addfin input (var,num_c all input e1)) e2 else
                                     if (bool_c all input e1 == True) then num_c (addfin all (var,111)) input e2 else num_c all input e2
                           True -> case of (
          EIf   p e1 e2 e3 -> if (bool_c all input e1) then (num_c all input e2) else (num_c all input e3)
         
          otherwise -> 1

pairT e = case e of
       EPair p e1 e2 ->True
       otherwise -> False


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

TypesT fs all input e = case e of
          ENum    p integer -> TInt
          EVar    p var -> if (tuplb all var) && (tuplb input var) then TInt else TBool
          EBool   p bool -> TBool
          EUnary p unaryop e -> if (show unaryop == "not") then TBool else TInt
          EBinary p binaryop e1 e2 -> if (binbool binaryop == True) then TInt else TBool
          ELet    p var e1 e2 -> if (evtype all input e2 == True) then TInt else TBool
          EIf     p e1 e2 e3 -> if (evtype all input e2 == True) then TInt else TBool
          EApp   p fsym e1 -> (ftype_c fs fsym)
          EPair  p e
		  EFst  p e
		  ESnd  p e
          otherwise -> TInt 

ftype_c ((FunctionDef a b c d e f ):xs) nz = if (nz == b) then e else ftype_c xs nz


evtype all input e = case e of
          ENum    p integer -> True
          EVar    p var -> if (tuplb all var) && (tuplb input var) then True else False
          EBool   p bool -> False
          EUnary p unaryop e -> if (show unaryop == "not") then False else True
          EBinary p binaryop e1 e2 -> if (binbool binaryop == True) then True else False
          ELet    p var e1 e2 -> if (evtype all input e2 == True) then True else False
          EIf     p e1 e2 e3 -> if (evtype all input e2 == True) then True else False
          otherwise -> True









  
