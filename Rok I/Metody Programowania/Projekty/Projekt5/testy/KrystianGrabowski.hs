-- Wymagamy, by modu³ zawiera³ tylko bezpieczne funkcje
{-# LANGUAGE Safe #-}
-- Definiujemy modu³ zawieraj¹cy rozwi¹zanie.
-- Nale¿y zmieniæ nazwê modu³u na {Imie}{Nazwisko} gdzie za {Imie}
-- i {Nazwisko} nale¿y podstawiæ odpowiednio swoje imiê i nazwisko
-- zaczynaj¹ce siê wielk¹ liter¹ oraz bez znaków diakrytycznych.
module KrystianGrabowski (typecheck, eval) where

-- Importujemy modu³y z definicj¹ jêzyka oraz typami potrzebnymi w zadaniu
import AST
import DataTypes

-- Funkcja sprawdzaj¹ca typy
-- Dla wywo³ania typecheck fs vars e zak³adamy, ¿e zmienne wystêpuj¹ce
-- w vars s¹ ju¿ zdefiniowane i maj¹ typ int, i oczekujemy by wyra¿enia e
-- mia³o typ int
-- UWAGA: to nie jest jeszcze rozwi¹zanie; nale¿y zmieniæ jej definicjê.
typecheck :: [FunctionDef p] -> [Var] -> Expr p -> TypeCheckResult p
typecheck _ _ _ = Ok

-- Funkcja obliczaj¹ca wyra¿enia
-- Dla wywo³ania eval fs input e przyjmujemy, ¿e dla ka¿dej pary (x, v)
-- znajduj¹cej siê w input, wartoœæ zmiennej x wynosi v.
-- Mo¿emy za³o¿yæ, ¿e definicje funckcji fs oraz wyra¿enie e s¹ dobrze
-- typowane, tzn. typecheck fs (map fst input) e = Ok
-- UWAGA: to nie jest jeszcze rozwi¹zanie; nale¿y zmieniæ jej definicjê.
eval :: [FunctionDef p] -> [(Var,Integer)] -> Expr p -> EvalResult
eval _ _ _ = RuntimeError