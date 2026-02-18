module Exercicios where


-- 1) Funções para retornar elementos da tupla (String, String, Char)
getNome :: (String, String, Char) -> String
getNome (n, _, _) = n

getTitulo :: (String, String, Char) -> String
getTitulo (_, t, _) = t

getGenero :: (String, String, Char) -> Char
getGenero (_, _, g) = g

-- 2 e 3) Base de Dados e Funções de Contagem
type Nome = String
type Titulo = String
type Genero = Char
type Pesquisador = (Nome, Titulo, Genero)
type Grupo = [Pesquisador]

base :: Int -> Pesquisador
base x
    | x == 1 = ("joao", "mestre", 'm')
    | x == 2 = ("jonas", "doutor", 'm')
    | x == 3 = ("joice", "mestre", 'f')
    | x == 4 = ("janete", "doutor", 'f')
    | x == 5 = ("jocileide", "doutor", 'f')
    | otherwise = ("ninguem", "", 'x')

-- 2.a) Contar mestres
contMestre :: Int -> Int
contMestre 0 = 0
contMestre n 
    | getTitulo (base n) == "mestre" = 1 + contMestre (n-1)
    | otherwise = contMestre (n-1)

-- 2.b) Contar doutores
contDoc :: Int -> Int
contDoc 0 = 0
contDoc n
    | getTitulo (base n) == "doutor" = 1 + contDoc (n-1)
    | otherwise = contDoc (n-1)

-- 2.c) Contagem por titulação (parâmetro)
contMD :: Int -> String -> Int
contMD 0 _ = 0
contMD n tit
    | getTitulo (base n) == tit = 1 + contMD (n-1) tit
    | otherwise = contMD (n-1) tit

-- 2.d) Contagem por titulação e gênero
cont :: Int -> String -> Char -> Int
cont 0 _ _ = 0
cont n tit gen
    | getTitulo (base n) == tit && getGenero (base n) == gen = 1 + cont (n-1) tit gen
    | otherwise = cont (n-1) tit gen

-- 3.b) Formar lista de pesquisadores recursivamente
gerarListaPesquisadores :: Int -> Grupo
gerarListaPesquisadores 0 = []
gerarListaPesquisadores n = gerarListaPesquisadores (n-1) ++ [base n]

-- 3.c) Lista de nomes de doutores usando gerador (compreensão)
nomesDoutores :: Grupo -> [Nome]
nomesDoutores grupo = [ n | (n, t, g) <- grupo, t == "doutor"]
