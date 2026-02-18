import subprocess
import sys
import pathlib

def main() -> None:
  if len(sys.argv) != 2:
    print("Uso: python3 run_tests.py <diretório_com_sistemas>")
    sys.exit(1)
  
  folder = pathlib.Path(sys.argv[1])
  if not folder.is_dir():
    print(f"Erro: {folder} não é um diretório")
    sys.exit(1)
  
  with open("resultados.txt", "w") as _output:
    _output.write("Resultados:\n\n")
  
  for file in sorted(folder.glob("sistema*.txt")):
    print(f"Executando {file}...")

    with open(file, "r") as _input, open("resultados.txt", "a") as _output:
      _output.write(f"-------{file}-------")
      subprocess.run(["./perfSL"], stdin=_input, stdout=_output)
      _output.write("\n\n")
  
if __name__ == "__main__":
  main()