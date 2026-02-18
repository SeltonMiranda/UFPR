module Exercicios where

-- 1) Soma todos os elementos de uma lista de inteiros
somaLista :: [Int] -> Int
somaLista [] = 0
somaLista (x:xs) = x + somaLista xs

-- 2) Remove todos os números pares de uma lista
removerPares :: [Int] -> [Int]
removerPares [] = []
removerPares (x:xs)
    | even x    = removerPares xs
    | otherwise = x : removerPares xs

-- 3) Inverte os elementos de uma lista de números reais
inverter :: [Float] -> [Float]
inverter [] = []
inverter (x:xs) = inverter xs ++ [x]

-- 4) Retorna nomes que começam com a letra 'A'
filtrarNomesA :: [String] -> [String]
filtrarNomesA [] = []
filtrarNomesA (x:xs)
    | not (null x) && head x == 'A' = x : filtrarNomesA xs
    | otherwise                     = filtrarNomesA xs


-- a) [0, 3, 6, 9, 12, 15]
geraListaA :: [Int]
geraListaA = [x | x <- [0, 3..15]]

-- b) [[1], [2], [3], [4], [5]]
geraListaB :: [[Int]]
geraListaB = [[x] | x <- [1..5]]


-- 1) Retorna tupla com dobro, triplo, quádruplo e quíntuplo
multiplos :: Int -> (Int, Int, Int, Int)
multiplos n = (n*2, n*3, n*4, n*5)

-- 2) Retorna divisão inteira por 2 e se é par ou ímpar
infoNumero :: Int -> (Int, String)
infoNumero n1 = (n1 `div` 2, if even n1 then "Par" else "Impar")

-- 3) Soma dos positivos e produto dos negativos
processarLista :: [Int] -> (Int, Int)
processarLista [] = (0, 1)
processarLista (x:xs)
    | x > 0     = (x + somaResto)