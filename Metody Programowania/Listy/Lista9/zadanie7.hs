newtype FSet a = FSet (a -> Bool)

empty :: FSet a
empty = FSet(\_ -> False)

empty1 :: FSet a
empty1 = FSet (const False)

singleton :: Ord a => a -> FSet a
singleton x = FSet ((==) x)