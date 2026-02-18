import pandas as pd
import matplotlib.pyplot as plt
import os

res_v1 = "resultados/resultados_v1_op2.csv"
res_v2 = "resultados/resultados_v2_op2.csv"
op = "op2"

def plot_comparison(attribute):
    df_v1 = pd.read_csv(res_v1)
    df_v2 = pd.read_csv(res_v2)

    plt.figure(figsize=(10, 6))
    
    plt.plot(df_v1["tamanho"], df_v1[attribute], 
             label="Versão 1", color="blue", marker="o", linestyle="-")
    
    plt.plot(df_v2["tamanho"], df_v2[attribute], 
             label="Versão 2 (otimizada)", color="red", marker="x", linestyle="-")

    plt.title(f"Comparação de Desempenho: {attribute}")
    plt.xlabel("Tamanho da Matriz (N)")
    if attribute == "tempo":
        plt.ylabel("Tempo (ms)")
        plt.yscale("log")
    else:
        plt.ylabel(attribute.replace('_', ' ').title())

    plt.xscale("log")
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"graficos/grafico_{attribute}_{op}.png")
    plt.close()

if not os.path.exists(res_v1) or not os.path.exists(res_v2):
    print(f"ERRO: Certifique-se de que os arquivos {res_v1} e {res_v2} existam.")
else:
    attributes = ["tempo", "L3_bandwidth", "L2_miss", "flops_dp", "flops_avx"]

    for attr in attributes:
        plot_comparison(attr)
    
    print("Gráficos gerados com sucesso")