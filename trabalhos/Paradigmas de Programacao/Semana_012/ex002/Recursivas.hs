module Recursivas where

fibonacci :: Int -> Int
fibonacci 0 = 0
fibonacci 1 = 1
fibonacci n = fibonacci (n - 1) + fibonacci (n - 2)

contarDigitos :: Int -> Int
contarDigitos n
    | n < 10    = 1
    | otherwise = 1 + contarDigitos (n `div` 10)

somaDigitos :: Int -> Int
somaDigitos n
    | n < 10    = n
    | otherwise = (n `mod` 10) + somaDigitos (n `div` 10)

