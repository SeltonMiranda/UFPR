def separar() -> None:
  with open("sistemas.dat", "r") as f:
    linhas = [linha.strip() for linha in f if linha.strip()]

  idx = 0
  sistema_num = 1

  while idx < len(linhas):
    try:
      dimensao = int(linhas[idx])
    except ValueError:
      print(f"Erro: Valor inválido na linha {idx + 1}: {linhas[idx]}")
      break
    
    sistema = [linhas[idx]] + linhas[idx+1 : idx+1+dimensao]
    idx += dimensao + 1

    arquivo = f"sistema{sistema_num}.txt"
    with open(arquivo, "w") as _output:
      _output.write("\n".join(sistema) + "\n")
    
    print(f"Sistema salvo no arquivo {arquivo}!")
    sistema_num += 1

if __name__ == "__main__":
  separar()