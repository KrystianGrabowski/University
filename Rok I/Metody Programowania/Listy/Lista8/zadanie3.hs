(f . g) x = f (g x)
(.) :: (b -> c) -> (a -> b) -> (a -> c)

flip f a b = f b a
flip :: (