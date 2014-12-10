myList = [1,2,3,4,5,6,7,8]

emptyList = []

maximum' :: (Ord a) => [a] -> a  
maximum' [] = error "maximum of empty list"  
maximum' [x] = x  
maximum' (x:xs) = max x (maximum' xs)  

--data Maybe a = Nothing | Just a  

--data Car x y z = Car { company :: x   
--                     , model :: y  
--                     , year :: z   
--                     } deriving (Show)  

--tellCar :: (Show a) => Car String String a -> String  
--tellCar (Car {company = c, model = m, year = y}) = "This " ++ c ++ " " ++ m ++ " was made in " ++ show y  

divBy :: Integral a => a -> [a] -> Either String [a]
divBy _ [] = Right []
divBy _ (0:_) = Left "divBy: division by 0"
divBy numerator (denom:xs) =
    case divBy numerator xs of
      Left x -> Left x
      Right results -> Right ((numerator `div` denom) : results)

--doubleMe :: [Integer] -> [Integer]
--doubleMe [] = []
--doubleMe [x] = [2 * x]
--doubleMe (x:xs) = (2*x):(doubleMe xs)
































