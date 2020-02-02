-- Wymagamy, by modu� zawiera� tylko bezpieczne funkcje
{-# LANGUAGE Safe #-}
-- Definiujemy modu� zawieraj�cy rozwi�zanie.
-- Nale�y zmieni� nazw� modu�u na {Imie}{Nazwisko} gdzie za {Imie}
-- i {Nazwisko} nale�y podstawi� odpowiednio swoje imi� i nazwisko
-- zaczynaj�ce si� wielk� liter� oraz bez znak�w diakrytycznych.
module KrystianGrabowski (typecheck, eval) where

-- Importujemy modu�y z definicj� j�zyka oraz typami potrzebnymi w zadaniu
import AST
import DataTypes

-- Funkcja sprawdzaj�ca typy
-- Dla wywo�ania typecheck fs vars e zak�adamy, �e zmienne wyst�puj�ce
-- w vars s� ju� zdefiniowane i maj� typ int, i oczekujemy by wyra�enia e
-- mia�o typ int
-- UWAGA: to nie jest jeszcze rozwi�zanie; nale�y zmieni� jej definicj�.
typecheck :: [FunctionDef p] -> [Var] -> Expr p -> TypeCheckResult p
typecheck _ _ _ = Ok

-- Funkcja obliczaj�ca wyra�enia
-- Dla wywo�ania eval fs input e przyjmujemy, �e dla ka�dej pary (x, v)
-- znajduj�cej si� w input, warto�� zmiennej x wynosi v.
-- Mo�emy za�o�y�, �e definicje funckcji fs oraz wyra�enie e s� dobrze
-- typowane, tzn. typecheck fs (map fst input) e = Ok
-- UWAGA: to nie jest jeszcze rozwi�zanie; nale�y zmieni� jej definicj�.
eval :: [FunctionDef p] -> [(Var,Integer)] -> Expr p -> EvalResult
eval _ _ _ = RuntimeError