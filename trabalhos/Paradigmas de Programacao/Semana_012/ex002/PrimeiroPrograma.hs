module PrimeiroPrograma where

num :: Int -> Float
num 1 = 5.0
num 2 = 10.0
num 3 = 15.0
num 4 = 20.0
num 5 = 25.0


somaAnterior :: Int -> Float
somaAnterior 1 = num 1                
somaAnterior n = num n + somaAnterior (n - 1)


media :: Float
media = somaTotal / fromIntegral quantidade
  where
    somaTotal = somaAnterior 5        
    quantidade = 5                    