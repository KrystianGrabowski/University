-- Modu� z typami potrzebnymi w zadaniu
{-# LANGUAGE Safe #-}
module DataTypes where

-- Tre�� komunikatu o b��dzie
type ErrorMessage = String

-- Wynik spradzania typ�w
data TypeCheckResult p
  = Ok                   -- Program jest poprawny
  | Error p ErrorMessage -- B��d na pozycji p o tre�ci ErrorMessage
  deriving (Eq, Show)

-- Wynik obliczania programu
data EvalResult
  = Value Integer -- Poprawny wynik oblicze�
  | RuntimeError  -- B��d podczas wykonania programu (dzielenie prze zero)
  deriving (Eq, Show)

-- �r�d�o programu dla testu
data ProgramSource
  = SrcString String   -- Bezpo�rednia tre�� programu
  | SrcFile   FilePath -- �cie�ka do pliku z programem
  deriving (Eq, Show)

-- Oczekiwana odpowied� dla testu
data TestAnswer
  -- Niepoprawny program (b��d typu)
  = TypeError
  -- Eval params result -- Program jest poprawny, a dla warto�ci zmiennych
  -- wej�ciowych params obliczenie daje wynik result
  | Eval [Integer] EvalResult
  deriving (Eq, Show)

-- Test
data Test = Test
  { testName    :: String        -- Nazwa testu
  , testProgram :: ProgramSource -- �r�d�o porogramu
  , testAnswer  :: TestAnswer    -- Oczekiwany rezultat
  }
  deriving (Eq, Show)