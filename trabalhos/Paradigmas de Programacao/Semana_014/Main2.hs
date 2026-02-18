import Filtros

main :: IO ()
main = do
    let lista = [-5.0, 0.0, 10.5, -2.0, 0.0, 7.0]
    
    putStr "Positivos: "
    print (filtrarValores isPositivo lista)
    
    putStr "Negativos: "
    print (filtrarValores isNegativo lista)
    
    putStr "Nulos: "
    print (filtrarValores isZero lista)