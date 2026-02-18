module funcoesDiversas where

reajuste :: Float -> Float
reajuste s = s * 1.25

mediaPonderada :: Float -> Float -> Float -> Int -> Int -> Int -> Float
mediaPonderada n1 n2 n3 p1 p2 p3 = (n1 * p1 + n2 * p2 + n3 * p3) / (p1 + p2 + p3)

toFarenheit :: Float -> Float
toFarenheit c = c * (9.0/5.0) + 32.0

idade :: Int -> Int
idade nasc = 2032 - nasc

minutos :: Int -> Int -> Int
minutos hora minutos = hora * 60 + minutos

somaQuadrados :: Int -> Int -> Int -> Int
somaQuadrados a b c = a*a + b*b + c*c

somaQuadrados2 :: Int -> Int -> Int -> Int
somaQuadrados2 a b c = a^2 + b^2 + c^2

ehimpar :: Int -> Bool
ehimpar a = if mod a 2 == 0
    then False
    else True

divisivel :: Int -> Int -> Bool
divisivel a b = if mod a b == 0
    then True
    else False

salario :: Float -> Float
salario s = s * 1.05 * 0.93