import csv
import subprocess
import re

PROG = "./v2/cgSolver"
CORE = "3"

sizes = [32, 64, 128, 256, 512, 1000, 2000, 4000, 8000, 9000, 10000, 20000]

OUTPUT = "resultados_v2_op2.csv"


# ---------------------------------------------------------
# Funções de execução
# ---------------------------------------------------------

def run_program_no_likwid(size):
    """Roda o programa diretamente, sem LIKWID, para medir tempo."""
    
    input_data = f"{size}\n7\n0.0\n25\n1e-8\n"

    result = subprocess.run(
        [PROG],
        input=input_data,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )

    return result.stdout.splitlines()


def run_likwid(size, group):
    """Roda o programa usando LIKWID para coletar os contadores."""
    
    input_data = f"{size}\n7\n0.0\n25\n1e-8\n"

    cmd = [
        "likwid-perfctr",
        "-C", CORE,
        "-g", group,
        "-m",
        PROG
    ]

    result = subprocess.run(
        cmd,
        input=input_data,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT
    )

    return result.stdout.splitlines()


# ---------------------------------------------------------
# Funções de parsing
# ---------------------------------------------------------

def parse_time(lines):
    """Procura uma linha contendo apenas o número do tempo."""
    pat = re.compile(r"^\s*([\d.]+)\s*$")
    for line in lines:
        m = pat.search(line)
        if m:
            return float(m.group(1))
    return None


def parse_L3(lines):
    pat = re.compile(r"L3 bandwidth \[MBytes/s\]\s*\|\s*([\d.]+)")
    for line in lines:
        m = pat.search(line)
        if m:
            return float(m.group(1))
    return None


def parse_L2(lines):
    pat = re.compile(r"L2 miss ratio\s*\|\s*([\d.]+)")
    for line in lines:
        m = pat.search(line)
        if m:
            return float(m.group(1))
    return None


def parse_flops_dp(lines):
    pat = re.compile(r"(?<!AVX )DP MFLOP/s\s*\|\s*([\d.]+)")
    for line in lines:
        m = pat.search(line)
        if m:
            return float(m.group(1))
    return None


def parse_flops_avx(lines):
    pat = re.compile(r"AVX DP MFLOP/s\s*\|\s*([\d.]+)")
    for line in lines:
        m = pat.search(line)
        if m:
            return float(m.group(1))
    return None


def parse_packed_dp_mflops(lines):
    pat = re.compile(r"Packed DP MFLOP/s\s*\|\s*([\d.]+)")
    for line in lines:
        m = pat.search(line)
        if m:
            return float(m.group(1))
    return None


# ---------------------------------------------------------
# Execução principal
# ---------------------------------------------------------

with open(OUTPUT, "w", newline="") as f:
    writer = csv.writer(f)
    writer.writerow(["tamanho", "tempo", "L3_bandwidth", "L2_miss", "flops_dp", "flops_avx"])

    for n in sizes:
        print(f"Rodando para N={n}...")

        # 1) Tempo sem LIKWID
        out_time = run_program_no_likwid(n)
        tempo = parse_time(out_time)

        # 2) Métricas com LIKWID
        out_flops_dp = run_likwid(n, "FLOPS_DP")
        flops_dp_total = parse_flops_dp(out_flops_dp)

        out_l3 = run_likwid(n, "L3")
        L3_bw = parse_L3(out_l3)

        out_l2 = run_likwid(n, "L2CACHE")
        L2_miss = parse_L2(out_l2)

        out_flops_avx = run_likwid(n, "FLOPS_AVX")
        packed_dp_mflops_avx = parse_packed_dp_mflops(out_flops_avx)

        row = [
            n,
            tempo,
            L3_bw,
            L2_miss,
            flops_dp_total,
            packed_dp_mflops_avx
        ]

        print(f"→ {row}")
        writer.writerow(row)

print(f"\nResultados salvos em {OUTPUT}")
