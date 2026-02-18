module Tratamento where

sr :: String -> String
sr nome = "Sr. " ++ nome

sra :: String -> String
sra nome = "Sra. " ++ nome

srta :: String -> String
srta nome = "Srta. " ++ nome

-- Função de alta ordem (Mapeamento recursivo)
aplicarTratamento :: (String -> String) -> [String] -> [String]
aplicarTratamento _ [] = []
aplicarTratamento f (x:xs) = f x : aplicarTratamento f xs