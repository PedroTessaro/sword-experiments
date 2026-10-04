# Experimentos: reprodutibilidade bit a bit em computação paralela

Os experimentos do artigo para o 18º COBRIC. Cada um compara C com OpenMP, como
normalmente se escreve, com Sword.

## O que cada experimento mede

**E1 — soma de 10⁷ doubles** (`sum/`). Dois conjuntos de dados, gerados por
`data/gen.c` a partir de uma semente fixa, iguais em toda máquina:

- `uniform`: valores em [0, 1), bem condicionado;
- `mixed`: `(2u − 1)·2^e` com `e` em [−30, 30], sinais misturados e 18 ordens de
  grandeza, onde o arredondamento aparece.

A referência é `math.fsum` do Python (`data/reference.py`), corretamente
arredondada e independente de qualquer programa testado. Os métodos são:

| método | o que é |
|---|---|
| `c-serial` | um laço, uma thread |
| `c-omp` | `#pragma omp parallel for reduction(+) schedule(static)` |
| `c-ompkahan` | soma compensada (Kahan) por thread, parciais combinadas na ordem das threads |
| `sword-plain` | `parallel for ... reduce(+)` |
| `sword-kahan` | `parallel for ... reduce(num.Merge)` |
| `sword-exact` | `parallel for ... reduce(num.MergeExact)`, acumulador exato de Kulisch |

Para cada método e cada número de threads (1, 2, 3, 4, 6, 8, 10, 16), guarda os
bits do resultado e a mediana do tempo em 7 repetições.

**E1b — repetibilidade.** A mesma configuração (dados `mixed`, com 2, 4, 8 e 16
threads) executada 100 vezes cada: com o número de threads fixo, o resultado se
repete?

**E2 — Monte Carlo** (`mc/`). Estimativa de ∫₀¹ e^(−x²) dx com 10⁷ amostras: um
gerador de números aleatórios, uma função elementar e uma soma, os três pontos
onde um resultado costuma deixar de se reproduzir.

| método | gerador | exp | soma |
|---|---|---|---|
| `c-thread` | um por thread, semeado pelo número da thread (o modo usual) | libm | `reduction(+)` |
| `c-index` | amostra i = splitmix64(semente + i) | libm | `reduction(+)` |
| `c-philox` | amostra i = Philox4x32-10, idêntico ao da Sword | libm | `reduction(+)` |
| `sword-mix` | amostra i = splitmix64(semente + i), idêntico ao `c-index` | `num.Exp` | `reduce(+)` |
| `sword-plain` | `rand.At(semente, i)` (Philox4x32-10) | `num.Exp` | `reduce(+)` |
| `sword-exact` | `rand.At(semente, i)` | `num.Exp` | `reduce(num.MergeExact)` |

Os pares `c-index`/`sword-mix` e `c-philox`/`sword-plain` usam as mesmas
amostras, para que a diferença de custo seja da linguagem e não do gerador. Que o
Philox em C dá os mesmos números que `rand.At` foi conferido diretamente.

**E3 — funções elementares** (`math/`). 10⁶ argumentos por função, gerados por
`math/args.c`: `sin`/`cos` em [−1000, 1000], `sin` em [−π/4, π/4] (sem redução
de argumento), `exp` em [−700, 700] e em [−1, 0], `log` em 600 ordens de
grandeza. A libm do sistema contra `std/num`. Os bits de cada resultado ficam em
`results/<plataforma>/bits/`, para comparar plataformas.

## Como rodar

Precisa de um compilador C com OpenMP, Python 3 e o compilador da Sword
compilado (`make` no repositório da linguagem).

```sh
SHIELD=../sword/shield ./run.sh <nome-da-plataforma>
python3 analyze.py > results/summary.md
python3 -m venv .venv && .venv/bin/pip install -r requirements.txt
.venv/bin/python figures.py          # results/figures/*.png e *.svg
```

As figuras (rótulos em português, para o artigo) saem dos mesmos CSVs: F1
resultados distintos por método em todas as plataformas e contagens de threads;
F2 erro por número de threads; F3 tempo por número de threads; F4
repetibilidade com threads fixas; F5 diferenças da libm entre plataformas; F6
custo das funções elementares.

`ONLY=math` roda só o E3, que não precisa de OpenMP. `NOTE="..."` grava uma
observação sobre a máquina no `env.txt` (por exemplo, que ela é emulada).
`THREADS`, `SUM_N`, `MC_N`, `MATH_N`, `REPS`, `REPEAT` e `REPEAT_THREADS` mudam
os tamanhos.

No Linux, dentro do contêiner usado para os testes da linguagem:

```sh
docker run --rm -v "$PWD/sword.tar:/sword.tar:ro" -v "$PWD:/exp" sword-ci:arm64 sh -c \
  'mkdir /sword && tar -xf /sword.tar -C /sword && cd /sword && make -s &&
   cd /exp && CC=gcc SHIELD=/sword/shield ./run.sh linux-arm64'
```

`sword.tar` é `git archive` da versão da linguagem usada, que o `env.txt`
registra.

## Cuidados ao ler os resultados

- Tempos de uma máquina emulada não valem; os bits valem.
- O Apple M4 tem 4 núcleos de desempenho e 6 de eficiência, então o ganho com
  threads não é linear e não deve ser lido como se fosse.
- Os resultados em `results/` são da **Sword 0.2.0 "Fold"** (tag `v0.2.0`,
  commit `867d50f`), compilada a partir da tag em cada máquina. `baseline/` é a
  mesma matriz numa versão anterior às correções de impressão de números e de
  redução de argumento de seno e cosseno (commit `f4a4195`), nas máquinas do
  GitHub: é onde se vê o seno a ~300 ns por chamada.
- `gh-*` são máquinas do GitHub Actions (x86-64 AMD EPYC 9V74 nos resultados
  e AMD EPYC 7763 na linha de base, arm64 Neoverse, Apple M1 virtual), com 3 ou 4 núcleos e compartilhadas: os tempos são indicativos, e
  8 e 16 threads nelas são mais threads que núcleos.
- A não repetibilidade com o número de threads fixo (E1b) aparece com o OpenMP
  do GCC (libgomp, Linux) a partir de 8 threads; com 2 e 4 ele repetiu, e o do
  LLVM (libomp, macOS) repetiu em todas as 100 execuções de cada configuração. O
  que varia com o número de threads varia nos dois.
- Durante a rodada no M4, um processo travado (issue #41 da Sword) ocupava ~10%
  de um dos dez núcleos; está anotado no `env.txt`.
