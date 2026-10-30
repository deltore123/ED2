# gera o grafico de escalabilidade (log-log) a partir do tempos.csv do medir.sh
# uso: python graficos.py   (precisa de matplotlib e numpy)
# nao faz parte da entrega, so serve para o relatorio

import csv
import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

RAJADAS = ["SOBE", "CARTA", "POSICAO", "CORTA", "DESFAZ"]
CORES = ["#2a78d6", "#eb6834", "#1baf7a", "#eda100", "#e87ba4"]
MARCADORES = ["o", "s", "^", "D", "v"]
PREVISTA = {r: 2 for r in RAJADAS}   # tabela de custos: O(n) por comando

# le o csv: rajada -> lista de (n, segundos)
dados = {r: [] for r in RAJADAS}
with open("tempos.csv") as f:
    for linha in csv.DictReader(f):
        dados[linha["rajada"]].append((int(linha["n"]), float(linha["segundos"])))

# inclinacao = coeficiente angular de log(t) contra log(n)
inclinacao = {}
for r in RAJADAS:
    n, t = np.array(sorted(dados[r])).T
    inclinacao[r] = np.polyfit(np.log(n), np.log(t), 1)[0]

plt.rcParams.update({"font.size": 10, "axes.edgecolor": "#b5b4ae",
                     "axes.labelcolor": "#3b3a36", "xtick.color": "#5f5e59",
                     "ytick.color": "#5f5e59"})
fig, ax = plt.subplots(figsize=(7.5, 5), dpi=200)
ax.set_xscale("log")
ax.set_yscale("log")

# retas de referencia (inclinacao 1 e 2), abaixo dos dados para nao se misturar
n_ref = np.array([12500, 100000])
t_base = min(t for r in RAJADAS for _, t in dados[r]) / 4
for k, estilo in [(1, ":"), (2, "--")]:
    ax.plot(n_ref, t_base * (n_ref / n_ref[0]) ** k, estilo, color="#a3a29b",
            linewidth=1, zorder=1)
    ax.text(n_ref[1] * 1.03, t_base * 8 ** k, f"inclinação {k}",
            color="#7c7b75", fontsize=8, va="center")

fim = {}
for r, cor, m in zip(RAJADAS, CORES, MARCADORES):
    n, t = np.array(sorted(dados[r])).T
    ax.plot(n, t, color=cor, linewidth=2, marker=m, markersize=7,
            markeredgecolor="white", markeredgewidth=1.5, zorder=3,
            label=r)
    fim[r] = t[-1]

# rotulos diretos no fim de cada linha, afastados quando ficam colados
ordem = sorted(RAJADAS, key=lambda r: np.log10(fim[r]))
y_rotulo = {}
anterior = -np.inf
for r in ordem:
    y = max(np.log10(fim[r]), anterior + 0.11)
    y_rotulo[r] = y
    anterior = y
for r in RAJADAS:
    texto = f"{r}  {inclinacao[r]:.2f}".replace(".", ",")
    ax.annotate(texto, xy=(100000, fim[r]),
                xytext=(100000 * 1.08, 10 ** y_rotulo[r]),
                color="#3b3a36", fontsize=9, va="center")

ax.set_xlim(10000, 190000)
ax.set_xticks([12500, 25000, 50000, 100000])
ax.set_xticklabels(["12 500", "25 000", "50 000", "100 000"])
ax.minorticks_off()
ax.set_xlabel("cartas no baralho (n)  —  cada rajada tem m = 2n comandos")
ax.set_ylabel("tempo (s)")
ax.set_title("Escalabilidade por rajada (log-log); rótulo = inclinação", loc="left",
             color="#1f1e1b", fontsize=12)
ax.grid(True, which="major", color="#e6e5e0", linewidth=0.8)
ax.set_axisbelow(True)
for lado in ["top", "right"]:
    ax.spines[lado].set_visible(False)
ax.legend(loc="upper left", frameon=False, fontsize=8.5)
fig.tight_layout()
fig.savefig("escalabilidade.png")

print("rajada,inclinacao_medida,inclinacao_prevista")
for r in RAJADAS:
    print(f"{r},{inclinacao[r]:.2f},{PREVISTA[r]}")
