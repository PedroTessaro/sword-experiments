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

**E1b — repetibilidade.** A mesma configuração (dados `mixed`, 4 e 8 threads)
executada 20 vezes: com o número de threads fixo, o resultado se repete?

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
```

`ONLY=math` roda só o E3, que não precisa de OpenMP. `NOTE="..."` grava uma
observação sobre a máquina no `env.txt` (por exemplo, que ela é emulada).
`THREADS`, `SUM_N`, `MC_N`, `MATH_N`, `REPS` e `REPEAT` mudam os tamanhos.

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
- `{.17}` na Sword não imprime os últimos dígitos exatos (issue #34), então os
  valores decimais nos CSVs da Sword são aproximados: o que vale são os bits.
- `num.Sin` e `num.Cos` são lentos para |x| > π/4 por causa da redução de
  argumento (issue #35); o núcleo, sem redução, é tão rápido quanto a libm.
