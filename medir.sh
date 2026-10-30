#!/bin/bash
# mede o tempo do baralho em cada rajada do gerador (secao 7 do enunciado)
# uso: ./medir.sh [repeticoes]   (padrao 3; grava a mediana em tempos.csv)
# nao faz parte da entrega, so serve para gerar os numeros do relatorio

REP=${1:-3}
TIMEFORMAT=%R
make -s || exit 1

echo "rajada,n,segundos" > tempos.csv
for r in SOBE CARTA POSICAO CORTA DESFAZ; do
    for n in 12500 25000 50000 100000; do
        ./gerador $r $n > entrada.txt
        tempos=""
        for i in $(seq $REP); do
            t=$( { time ./baralho < entrada.txt > /dev/null; } 2>&1 )
            tempos="$tempos $t"
        done
        # mediana das repeticoes
        med=$(echo $tempos | tr ' ' '\n' | sort -g | sed -n "$(( (REP + 1) / 2 ))p")
        echo "$r,$n,$med" | tee -a tempos.csv
    done
done
rm -f entrada.txt

# inclinacao da reta log-log (minimos quadrados de log t contra log n)
echo
echo "rajada,inclinacao"
awk -F, 'NR > 1 { x = log($2); y = log($3); k = $1
                  sx[k] += x; sy[k] += y; sxx[k] += x*x; sxy[k] += x*y; c[k]++ }
         END { for (k in c) printf "%s,%.2f\n", k,
                 (c[k]*sxy[k] - sx[k]*sy[k]) / (c[k]*sxx[k] - sx[k]*sx[k]) }' tempos.csv
