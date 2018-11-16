fib :: Integer -> Integer
fib 0 = 1
fib 1 = 1
fib n = fib (n-1)+ fib(n-2)

fibn n = f !! (n) where f = 0:1:zipWith (+) f (tail f)
w = putStrLn $ show( map fibn [0,1,2,3,4,5,6,7,8,9,10])