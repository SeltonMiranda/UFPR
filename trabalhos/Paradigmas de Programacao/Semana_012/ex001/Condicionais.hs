module Condicionais where


ehApta :: Int -> Bool
ehApta idade = if idade >= 18 
    then True
    else False

ehApta2 :: Int -> Bool
ehApta2 idade
    | idade >= 18 = True
    | otherwise   = False

numero :: Int -> String
numero num = if num > 0
    then "Positivo"
    else if num == 0
        then "Zero"
    else "Negativo"

numero2 :: Int -> String 
numero2 num
    | num > 0 = "Positivo"
    | num == 0 = "Zero"
    | otherwise = "Negativo"

isBissextoIf :: Int -> Bool
isBissextoIf ano = 
    if ano `mod` 400 == 0 
    then True 
    else if ano `mod` 100 == 0 
         then False 
         else if ano `mod` 4 == 0 
              then True 
              else False

isBissextoWhere :: Int -> Bool
isBissextoWhere ano = 
    if div400 then True
    else if div100 then False
    else if div4 then True
    else False
  where
    div4   = ano `mod` 4 == 0
    div100 = ano `mod` 100 == 0
    div400 = ano `mod` 400 == 0

isBissextoGuards :: Int -> Bool
isBissextoGuards ano
    | div400    = True
    | div100    = False
    | div4      = True
    | otherwise = False
  where
    div4   = ano `mod` 4 == 0
    div100 = ano `mod` 100 == 0
    div400 = ano `mod` 400 == 0