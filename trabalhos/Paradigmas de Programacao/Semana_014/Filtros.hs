module Filtros where

isPositivo :: Float -> Bool
isPositivo x = x > 0

isNegativo :: Float -> Bool
isNegativo x = x < 0

isZero :: Float -> Bool
isZero x = x == 0

-- Função de alta ordem (Filtro recursivo)
filtrarValores :: (Float -> Bool) -> [Float] -> [Float]
filtrarValores _ [] = []
filtrarValores f (x:xs)
    | f x       = x : filtrarValores f xs
    | otherwise = filtrarValores f xs