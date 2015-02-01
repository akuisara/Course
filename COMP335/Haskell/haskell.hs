myList = [1,2,3,4,5,6,7,8]

doubleMe :: [Integer] -> [Integer]
doubleMe [] = []
doubleMe [x] = [2 * x]
doubleMe (x:xs) = (2*x):(doubleMe xs)

-------------------------------------

map' :: (a -> b) -> [a] -> [b]
map' f xs = [f x | x <- xs]

doubleMap :: Integer -> Integer
doubleMap x = 2 * x



--emptyList = []

--maximum' :: (Ord a) => [a] -> a  
--maximum' [] = error "maximum of empty list"  
--maximum' [x] = x  
--maximum' (x:xs) = max x (maximum' xs)  

--data Maybe a = Nothing | Just a  

--data Car x y z = Car { company :: x   
--                     , model :: y  
--                     , year :: z   
--                     } deriving (Show)  

--tellCar :: (Show a) => Car String String a -> String  
--tellCar (Car {company = c, model = m, year = y}) = "This " ++ c ++ " " ++ m ++ " was made in " ++ show y  

--divBy :: Integral a => a -> [a] -> Either String [a]
--divBy _ [] = Right []
--divBy _ (0:_) = Left "divBy: division by 0"
--divBy numerator (denom:xs) =
--    case divBy numerator xs of
--      Left x -> Left x
--      Right results -> Right ((numerator `div` denom) : results)



data Person = Person { firstName :: String  
                     , lastName :: String  
                     , age :: Int  
                     } deriving (Eq, Show, Read)

data Day = Monday | Tuesday | Wednesday | Thursday | Friday | Saturday | Sunday   
           deriving (Eq, Ord, Show, Read, Bounded, Enum) 

data Shape = Circle Float Float Float | Rectangle Float Float Float Float

surface :: Shape -> Float  
surface (Circle _ _ r) = pi * r ^ 2 