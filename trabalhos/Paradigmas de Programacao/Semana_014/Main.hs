import Tratamento

main :: IO ()
main = do
    let homens = ["Joao", "Carlos"]
    let casadas = ["Maria", "Ana"]
    let jovens = ["Joice", "Janete"]
    
    print (aplicarTratamento sr homens)
    print (aplicarTratamento sra casadas)
    print (aplicarTratamento srta jovens)