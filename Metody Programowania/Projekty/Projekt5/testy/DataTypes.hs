-- Modu≥ z typami potrzebnymi w zadaniu
{-# LANGUAGE Safe #-}
module DataTypes where

-- TreúÊ komunikatu o b≥Ídzie
type ErrorMessage = String

-- Wynik spradzania typÛw
data TypeCheckResult p
  = Ok                   -- Program jest poprawny
  | Error p ErrorMessage -- B≥πd na pozycji p o treúci ErrorMessage
  deriving (Eq, Show)

-- Wynik obliczania programu
data EvalResult
  = Value Integer -- Poprawny wynik obliczeÒ
  | RuntimeError  -- B≥πd podczas wykonania programu (dzielenie prze zero)
  deriving (Eq, Show)

-- èrÛd≥o programu dla testu
data ProgramSource
  = SrcString String   -- Bezpoúrednia treúÊ programu
  | SrcFile   FilePath -- úcieøka do pliku z programem
  deriving (Eq, Show)

-- Oczekiwana odpowiedü dla testu
data TestAnswer
  -- Niepoprawny program (b≥πd typu)
  = TypeError
  -- Eval params result -- Program jest poprawny, a dla wartoúci zmiennych
  -- wejúciowych params obliczenie daje wynik result
  | Eval [Integer] EvalResult
  deriving (Eq, Show)

-- Test
data Test = Test
  { testName    :: String        -- Nazwa testu
  , testProgram :: ProgramSource -- èrÛd≥o porogramu
  , testAnswer  :: TestAnswer    -- Oczekiwany rezultat
  }
  deriving (Eq, Show)