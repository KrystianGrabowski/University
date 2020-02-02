import Data.List
import Data.Char

integerToString :: Integer -> String
integerToString 0 = "0"
integerToString n = (reverse . unfoldr (\n -> if n == 0 then Nothing 
                    else Just((intToDigit . fromEnum) (n `mod` 10), n `div` 10)))n
w = putStrLn $ show(integerToString 01234567)