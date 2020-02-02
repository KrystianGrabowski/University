ssm :: [Integer] -> [Integer]
ssm = foldl aux []

aux :: Integer -> [Integer] -> [Integer]
aux a [] = [a]
aux a (x:xs)
       | a<x = a:x:xs
       | otherwise = aux a xs
