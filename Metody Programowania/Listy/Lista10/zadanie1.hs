import Data.List
import Data.Char
nat2::[(Integer,Integer)]
nat2 = [(y,x-y)| x <- [0..], y <- [0..x]]