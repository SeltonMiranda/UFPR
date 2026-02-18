"""
Nome: Selton Miranda Rolim
GRR: 20235688
"""

import subprocess
import sys
import re

EXECUTAVEL = "resolveEDO"

LIKWID_CMD = [
  "likwid-perfctr",
  "-C", "0", "-g", "FLOPS_DP", "-m", f"./{EXECUTAVEL}"
]

def main() -> None:
  if len(sys.argv) < 2:
    print(f"Uso: python3 {sys.argv[0]} <input_file>")
    sys.exit(1)
  
  input = sys.argv[1]

  with open(input, "r") as f:
    data = f.read()

  res = subprocess.run(LIKWID_CMD, input=data, capture_output=True, text=True)  
  
  if res.returncode != 0:
    print("ERRO ao executar LIKWID")
    sys.exit(1)

  output = res.stdout
 
  retirar = ("--", "CPU ")
  for linha in output.splitlines():
    if linha.strip().startswith(retirar):
        continue
    elif linha.strip().startswith("Region "):
        break
    print(linha)

  pattern = re.compile(r"FP_ARITH_INST_RETIRED_SCALAR_DOUBLE\s*\|\s*\w+\s*\|\s*(\d+)")
  for linha in output.splitlines():
    p = pattern.search(linha)
    if p:
      valor = p.group(1)
      print(f"FP_ARITH_INST_RETIRED_SCALAR_DOUBLE: {valor}")
  print()

if __name__ == '__main__':
  main()
