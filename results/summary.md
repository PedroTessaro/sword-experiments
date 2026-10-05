# Results

## gh-linux-arm64

```
platform: gh-linux-arm64
date: 2026-10-04T15:04:19Z
uname: Linux 6.17.0-1022-azure aarch64
cpu: 0xd49
cores: 4
cc: gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
openmp: -fopenmp
shield: shield 0.2.0 (Fold)
sword commit: 867d50f
python: Python 3.12.3
threads: 1 2 3 4 6 8 10 16
sum_n: 10000000 mc_n: 10000000 math_n: 1000000 reps: 7
only: all
note: GitHub-hosted runner ubuntu-24.04-arm, shared with other jobs; times are indicative
```

### E1 — summation of 10^7 doubles

**uniform** (correctly rounded sum 5000576.9172228221)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 237 | 6.29 | 6.29 | 1 |
| c-omp | 7 of 8 | 20–237 | 6.53 | 1.60 | 4 |
| c-ompkahan | 1 of 8 | 0 | 23.74 | 5.96 | 4 |
| sword-plain | 1 of 8 | 4 | 6.96 | 1.72 | 4 |
| sword-kahan | 1 of 8 | 0 | 24.85 | 6.25 | 4 |
| sword-exact | 1 of 8 | 0 | 33.87 | 9.42 | 4 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 6.47 | 6.47 | 1 |
| c-omp | 8 of 8 | 37–243 | 6.77 | 1.60 | 4 |
| c-ompkahan | 3 of 8 | 0–1 | 23.78 | 5.92 | 4 |
| sword-plain | 1 of 8 | 30 | 6.65 | 1.57 | 4 |
| sword-kahan | 1 of 8 | 0 | 24.79 | 6.31 | 4 |
| sword-exact | 1 of 8 | 0 | 60.46 | 15.74 | 6 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 2 | 100 | 1 |
| sword-plain | 2 | 100 | 1 |
| c-omp | 4 | 100 | 1 |
| sword-plain | 4 | 100 | 1 |
| c-omp | 8 | 100 | 3 |
| sword-plain | 8 | 100 | 1 |
| c-omp | 16 | 100 | 5 |
| sword-plain | 16 | 100 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440216 … 0.74692123466732607 | 49.5 | 12.4 | 4 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 48.0 | 12.0 | 4 |
| c-philox | 8 of 8 | 0.74688899599929437 … 0.74688899599935521 | 179.9 | 45.1 | 4 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 229.4 | 57.8 | 4 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 93.4 | 23.6 | 8 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 289.3 | 74.0 | 16 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 15.37 | 16.27 |
| sinnear | 6.96 | 3.14 |
| cos | 15.65 | 16.45 |
| exp | 6.11 | 8.72 |
| expunit | 3.22 | 7.16 |
| log | 4.04 | 8.30 |

## gh-linux-x86_64

```
platform: gh-linux-x86_64
date: 2026-10-04T15:04:18Z
uname: Linux 6.17.0-1022-azure x86_64
cpu: AMD EPYC 9V74 80-Core Processor
cores: 4
cc: gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
openmp: -fopenmp
shield: shield 0.2.0 (Fold)
sword commit: 867d50f
python: Python 3.12.3
threads: 1 2 3 4 6 8 10 16
sum_n: 10000000 mc_n: 10000000 math_n: 1000000 reps: 7
only: all
note: GitHub-hosted runner ubuntu-latest, shared with other jobs; times are indicative
```

### E1 — summation of 10^7 doubles

**uniform** (correctly rounded sum 5000576.9172228221)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 237 | 8.20 | 8.20 | 1 |
| c-omp | 7 of 8 | 20–237 | 8.21 | 2.10 | 4 |
| c-ompkahan | 1 of 8 | 0 | 32.80 | 8.27 | 4 |
| sword-plain | 1 of 8 | 4 | 8.22 | 2.12 | 4 |
| sword-kahan | 1 of 8 | 0 | 15.31 | 6.92 | 4 |
| sword-exact | 1 of 8 | 0 | 33.01 | 17.19 | 3 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 8.21 | 8.21 | 1 |
| c-omp | 8 of 8 | 37–243 | 8.21 | 2.08 | 4 |
| c-ompkahan | 3 of 8 | 0–1 | 32.77 | 8.27 | 4 |
| sword-plain | 1 of 8 | 30 | 8.23 | 2.11 | 4 |
| sword-kahan | 1 of 8 | 0 | 15.40 | 7.11 | 4 |
| sword-exact | 1 of 8 | 0 | 66.81 | 23.99 | 6 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 2 | 100 | 1 |
| sword-plain | 2 | 100 | 1 |
| c-omp | 4 | 100 | 1 |
| sword-plain | 4 | 100 | 1 |
| c-omp | 8 | 100 | 3 |
| sword-plain | 8 | 100 | 1 |
| c-omp | 16 | 100 | 6 |
| sword-plain | 16 | 100 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440194 … 0.74692123466732596 | 54.6 | 23.5 | 4 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 52.2 | 23.0 | 4 |
| c-philox | 7 of 8 | 0.74688899599929437 … 0.74688899599935521 | 185.5 | 79.0 | 8 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 377.0 | 102.0 | 4 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 117.8 | 35.0 | 4 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 390.4 | 120.3 | 16 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 17.42 | 19.28 |
| sinnear | 8.21 | 1.91 |
| cos | 17.23 | 24.99 |
| exp | 8.03 | 6.93 |
| expunit | 4.65 | 6.91 |
| log | 4.10 | 6.23 |

## gh-macos-arm64

```
platform: gh-macos-arm64
date: 2026-10-04T15:04:22Z
uname: Darwin 25.6.0 arm64
cpu: Apple M1 (Virtual)
cores: 3
cc: Apple clang version 21.0.0 (clang-2100.1.1.101)
openmp: -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp
shield: shield 0.2.0 (Fold)
sword commit: 867d50f
python: Python 3.14.7
threads: 1 2 3 4 6 8 10 16
sum_n: 10000000 mc_n: 10000000 math_n: 1000000 reps: 7
only: all
note: GitHub-hosted runner macos-latest, shared with other jobs; times are indicative
```

### E1 — summation of 10^7 doubles

**uniform** (correctly rounded sum 5000576.9172228221)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 237 | 11.18 | 11.18 | 1 |
| c-omp | 7 of 8 | 20–237 | 11.79 | 4.88 | 16 |
| c-ompkahan | 1 of 8 | 0 | 49.81 | 17.24 | 6 |
| sword-plain | 1 of 8 | 4 | 11.99 | 3.89 | 4 |
| sword-kahan | 1 of 8 | 0 | 15.05 | 5.43 | 16 |
| sword-exact | 1 of 8 | 0 | 39.86 | 14.14 | 3 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 11.50 | 11.50 | 1 |
| c-omp | 8 of 8 | 37–243 | 10.84 | 4.79 | 10 |
| c-ompkahan | 3 of 8 | 0–1 | 45.41 | 16.26 | 16 |
| sword-plain | 1 of 8 | 30 | 11.04 | 4.25 | 6 |
| sword-kahan | 1 of 8 | 0 | 16.30 | 5.59 | 6 |
| sword-exact | 1 of 8 | 0 | 94.05 | 27.68 | 10 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 2 | 100 | 1 |
| sword-plain | 2 | 100 | 1 |
| c-omp | 4 | 100 | 1 |
| sword-plain | 4 | 100 | 1 |
| c-omp | 8 | 100 | 1 |
| sword-plain | 8 | 100 | 1 |
| c-omp | 16 | 100 | 1 |
| sword-plain | 16 | 100 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440216 … 0.74692123466732596 | 67.3 | 20.7 | 16 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 48.9 | 12.4 | 16 |
| c-philox | 7 of 8 | 0.74688899599929437 … 0.74688899599935521 | 142.1 | 41.9 | 16 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 378.1 | 110.7 | 4 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 151.0 | 51.2 | 16 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 436.5 | 146.4 | 6 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 8.31 | 21.46 |
| sinnear | 2.05 | 2.94 |
| cos | 8.22 | 21.17 |
| exp | 6.26 | 6.32 |
| expunit | 2.66 | 7.39 |
| log | 3.15 | 6.74 |

## linux-arm64-docker

```
platform: linux-arm64-docker
date: 2026-10-04T15:33:48Z
uname: Linux 7.0.12-linuxkit aarch64
cpu: 0x000
cores: 10
cc: gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
openmp: -fopenmp
shield: shield 0.2.0 (Fold)
sword commit: 867d50f
python: Python 3.12.3
threads: 1 2 3 4 6 8 10 16
sum_n: 10000000 mc_n: 10000000 math_n: 1000000 reps: 7
only: all
note: Docker Desktop Linux VM on the same Apple M4
```

### E1 — summation of 10^7 doubles

**uniform** (correctly rounded sum 5000576.9172228221)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 237 | 5.74 | 5.74 | 1 |
| c-omp | 7 of 8 | 21–237 | 5.69 | 1.10 | 8 |
| c-ompkahan | 1 of 8 | 0 | 19.13 | 3.62 | 10 |
| sword-plain | 1 of 8 | 4 | 5.28 | 0.96 | 8 |
| sword-kahan | 1 of 8 | 0 | 11.56 | 2.13 | 10 |
| sword-exact | 1 of 8 | 0 | 17.42 | 3.31 | 10 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 5.74 | 5.74 | 1 |
| c-omp | 8 of 8 | 37–243 | 5.73 | 1.10 | 8 |
| c-ompkahan | 3 of 8 | 0–1 | 19.13 | 3.86 | 10 |
| sword-plain | 1 of 8 | 30 | 5.35 | 1.03 | 10 |
| sword-kahan | 1 of 8 | 0 | 11.71 | 2.24 | 8 |
| sword-exact | 1 of 8 | 0 | 45.77 | 7.78 | 10 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 2 | 100 | 1 |
| sword-plain | 2 | 100 | 1 |
| c-omp | 4 | 100 | 1 |
| sword-plain | 4 | 100 | 1 |
| c-omp | 8 | 100 | 3 |
| sword-plain | 8 | 100 | 1 |
| c-omp | 16 | 100 | 4 |
| sword-plain | 16 | 100 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440216 … 0.74692123466732607 | 33.1 | 6.2 | 10 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 15.5 | 3.9 | 16 |
| c-philox | 7 of 8 | 0.74688899599929437 … 0.74688899599935521 | 86.9 | 19.4 | 10 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 157.5 | 27.7 | 16 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 67.9 | 11.6 | 16 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 315.1 | 34.9 | 16 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 11.18 | 12.34 |
| sinnear | 3.57 | 2.73 |
| cos | 11.85 | 12.20 |
| exp | 4.15 | 2.58 |
| expunit | 2.32 | 4.38 |
| log | 2.33 | 2.88 |

## macos-arm64

```
platform: macos-arm64
date: 2026-10-04T15:10:10Z
uname: Darwin 27.0.0 arm64
cpu: Apple M4
cores: 10
cc: Apple clang version 21.0.0 (clang-2100.3.34.2)
openmp: -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp
shield: shield 0.2.0 (Fold)
sword commit: 867d50f
python: Python 3.14.7
threads: 1 2 3 4 6 8 10 16
sum_n: 10000000 mc_n: 10000000 math_n: 1000000 reps: 7
only: all
note: Apple M4, 4 performance and 6 efficiency cores; one stuck process (issue #41) held ~10% of one core during the run
```

### E1 — summation of 10^7 doubles

**uniform** (correctly rounded sum 5000576.9172228221)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 237 | 7.36 | 7.36 | 1 |
| c-omp | 7 of 8 | 20–237 | 5.08 | 0.93 | 10 |
| c-ompkahan | 1 of 8 | 0 | 19.87 | 3.37 | 10 |
| sword-plain | 1 of 8 | 4 | 7.53 | 0.85 | 10 |
| sword-kahan | 1 of 8 | 0 | 6.59 | 1.08 | 16 |
| sword-exact | 1 of 8 | 0 | 17.29 | 3.15 | 10 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 4.99 | 4.99 | 1 |
| c-omp | 8 of 8 | 37–243 | 4.97 | 0.99 | 8 |
| c-ompkahan | 3 of 8 | 0–1 | 19.72 | 3.68 | 16 |
| sword-plain | 1 of 8 | 30 | 4.97 | 0.80 | 16 |
| sword-kahan | 1 of 8 | 0 | 6.58 | 1.11 | 10 |
| sword-exact | 1 of 8 | 0 | 44.42 | 7.02 | 16 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 2 | 100 | 1 |
| sword-plain | 2 | 100 | 1 |
| c-omp | 4 | 100 | 1 |
| sword-plain | 4 | 100 | 1 |
| c-omp | 8 | 100 | 1 |
| sword-plain | 8 | 100 | 1 |
| c-omp | 16 | 100 | 1 |
| sword-plain | 16 | 100 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440216 … 0.74692123466732596 | 32.2 | 6.1 | 10 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 20.0 | 4.4 | 8 |
| c-philox | 7 of 8 | 0.74688899599929437 … 0.74688899599935521 | 59.5 | 12.0 | 16 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 158.7 | 26.3 | 16 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 70.8 | 11.8 | 16 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 315.1 | 40.4 | 16 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 8.42 | 12.12 |
| sinnear | 1.74 | 1.38 |
| cos | 5.50 | 11.71 |
| exp | 4.11 | 2.73 |
| expunit | 1.66 | 4.20 |
| log | 1.74 | 3.32 |

## macos-arm64-atomic

```
platform: macos-arm64-atomic
date: 2026-10-05T15:26:12Z
uname: Darwin 27.0.0 arm64
cpu: Apple M4
cores: 10
cc: Apple clang version 21.0.0 (clang-2100.3.34.2)
openmp: -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp
shield: shield 0.2.0 (Fold)
sword commit: a12748c
python: Python 3.14.7
threads: 1 2 3 4 6 8 10 16
sum_n: 10000000 mc_n: 10000000 math_n: 1000000 reps: 7
only: all
note: libomp forçada a reduction atômica (KMP_FORCE_REDUCTION=atomic)
```

### E1 — summation of 10^7 doubles

**uniform** (correctly rounded sum 5000576.9172228221)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 237 | 6.76 | 6.76 | 1 |
| c-omp | 7 of 8 | 21–237 | 4.88 | 0.97 | 8 |
| c-ompkahan | 1 of 8 | 0 | 19.31 | 3.71 | 8 |
| sword-plain | 1 of 8 | 4 | 6.66 | 0.87 | 10 |
| sword-kahan | 1 of 8 | 0 | 6.44 | 1.16 | 10 |
| sword-exact | 1 of 8 | 0 | 18.27 | 3.19 | 10 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 4.93 | 4.93 | 1 |
| c-omp | 8 of 8 | 37–243 | 4.88 | 1.09 | 10 |
| c-ompkahan | 3 of 8 | 0–1 | 19.29 | 3.86 | 8 |
| sword-plain | 1 of 8 | 30 | 4.86 | 0.86 | 10 |
| sword-kahan | 1 of 8 | 0 | 6.50 | 1.24 | 8 |
| sword-exact | 1 of 8 | 0 | 45.06 | 7.62 | 16 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 8 | 100 | 3 |
| sword-plain | 8 | 100 | 1 |
| c-omp | 16 | 100 | 3 |
| sword-plain | 16 | 100 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440205 … 0.74692123466732596 | 32.3 | 6.4 | 8 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 19.8 | 3.9 | 16 |
| c-philox | 8 of 8 | 0.74688899599929437 … 0.74688899599935521 | 60.8 | 11.7 | 16 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 159.9 | 26.6 | 16 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 73.8 | 12.2 | 16 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 300.1 | 40.3 | 16 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 9.04 | 12.56 |
| sinnear | 1.69 | 1.41 |
| cos | 5.60 | 11.65 |
| exp | 4.09 | 2.77 |
| expunit | 1.60 | 4.23 |
| log | 1.65 | 3.23 |

## E1, E2 — Sword's answers on different platforms

| experiment | method | platforms | runs | distinct results |
|---|---|---|---|---|
| E1 mixed | c-serial | 6 | 6 | 1 |
| E1 mixed | c-omp | 6 | 48 | 13 |
| E1 mixed | c-ompkahan | 6 | 48 | 3 |
| E1 mixed | sword-plain | 6 | 48 | 1 |
| E1 mixed | sword-kahan | 6 | 48 | 1 |
| E1 mixed | sword-exact | 6 | 48 | 1 |
| E1 uniform | c-serial | 6 | 6 | 1 |
| E1 uniform | c-omp | 6 | 48 | 11 |
| E1 uniform | c-ompkahan | 6 | 48 | 1 |
| E1 uniform | sword-plain | 6 | 48 | 1 |
| E1 uniform | sword-kahan | 6 | 48 | 1 |
| E1 uniform | sword-exact | 6 | 48 | 1 |
| E2 | c-thread | 6 | 48 | 15 |
| E2 | c-index | 6 | 48 | 11 |
| E2 | c-philox | 6 | 48 | 10 |
| E2 | sword-plain | 6 | 48 | 1 |
| E2 | sword-mix | 6 | 48 | 1 |
| E2 | sword-exact | 6 | 48 | 1 |

## E3 — the same arguments on different platforms

| function | platforms | C library: results that differ | std/num: results that differ |
|---|---|---|---|
| sin | gh-linux-arm64 vs gh-linux-x86_64 | 0 of 1000000 | 0 of 1000000 |
| sin | gh-linux-arm64 vs gh-macos-arm64 | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-linux-arm64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| sin | gh-linux-arm64 vs macos-arm64 | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-linux-arm64 vs macos-arm64-atomic | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-linux-x86_64 vs gh-macos-arm64 | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-linux-x86_64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| sin | gh-linux-x86_64 vs macos-arm64 | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-linux-x86_64 vs macos-arm64-atomic | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-macos-arm64 vs linux-arm64-docker | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-macos-arm64 vs macos-arm64 | 0 of 1000000 | 0 of 1000000 |
| sin | gh-macos-arm64 vs macos-arm64-atomic | 0 of 1000000 | 0 of 1000000 |
| sin | linux-arm64-docker vs macos-arm64 | 40563 of 1000000 | 0 of 1000000 |
| sin | linux-arm64-docker vs macos-arm64-atomic | 40563 of 1000000 | 0 of 1000000 |
| sin | macos-arm64 vs macos-arm64-atomic | 0 of 1000000 | 0 of 1000000 |
| cos | gh-linux-arm64 vs gh-linux-x86_64 | 0 of 1000000 | 0 of 1000000 |
| cos | gh-linux-arm64 vs gh-macos-arm64 | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-linux-arm64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| cos | gh-linux-arm64 vs macos-arm64 | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-linux-arm64 vs macos-arm64-atomic | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-linux-x86_64 vs gh-macos-arm64 | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-linux-x86_64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| cos | gh-linux-x86_64 vs macos-arm64 | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-linux-x86_64 vs macos-arm64-atomic | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-macos-arm64 vs linux-arm64-docker | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-macos-arm64 vs macos-arm64 | 0 of 1000000 | 0 of 1000000 |
| cos | gh-macos-arm64 vs macos-arm64-atomic | 0 of 1000000 | 0 of 1000000 |
| cos | linux-arm64-docker vs macos-arm64 | 40715 of 1000000 | 0 of 1000000 |
| cos | linux-arm64-docker vs macos-arm64-atomic | 40715 of 1000000 | 0 of 1000000 |
| cos | macos-arm64 vs macos-arm64-atomic | 0 of 1000000 | 0 of 1000000 |
| exp | gh-linux-arm64 vs gh-linux-x86_64 | 0 of 1000000 | 0 of 1000000 |
| exp | gh-linux-arm64 vs gh-macos-arm64 | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-linux-arm64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| exp | gh-linux-arm64 vs macos-arm64 | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-linux-arm64 vs macos-arm64-atomic | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-linux-x86_64 vs gh-macos-arm64 | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-linux-x86_64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| exp | gh-linux-x86_64 vs macos-arm64 | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-linux-x86_64 vs macos-arm64-atomic | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-macos-arm64 vs linux-arm64-docker | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-macos-arm64 vs macos-arm64 | 0 of 1000000 | 0 of 1000000 |
| exp | gh-macos-arm64 vs macos-arm64-atomic | 0 of 1000000 | 0 of 1000000 |
| exp | linux-arm64-docker vs macos-arm64 | 1765 of 1000000 | 0 of 1000000 |
| exp | linux-arm64-docker vs macos-arm64-atomic | 1765 of 1000000 | 0 of 1000000 |
| exp | macos-arm64 vs macos-arm64-atomic | 0 of 1000000 | 0 of 1000000 |
| log | gh-linux-arm64 vs gh-linux-x86_64 | 0 of 1000000 | 0 of 1000000 |
| log | gh-linux-arm64 vs gh-macos-arm64 | 7 of 1000000 | 0 of 1000000 |
| log | gh-linux-arm64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| log | gh-linux-arm64 vs macos-arm64 | 7 of 1000000 | 0 of 1000000 |
| log | gh-linux-arm64 vs macos-arm64-atomic | 7 of 1000000 | 0 of 1000000 |
| log | gh-linux-x86_64 vs gh-macos-arm64 | 7 of 1000000 | 0 of 1000000 |
| log | gh-linux-x86_64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| log | gh-linux-x86_64 vs macos-arm64 | 7 of 1000000 | 0 of 1000000 |
| log | gh-linux-x86_64 vs macos-arm64-atomic | 7 of 1000000 | 0 of 1000000 |
| log | gh-macos-arm64 vs linux-arm64-docker | 7 of 1000000 | 0 of 1000000 |
| log | gh-macos-arm64 vs macos-arm64 | 0 of 1000000 | 0 of 1000000 |
| log | gh-macos-arm64 vs macos-arm64-atomic | 0 of 1000000 | 0 of 1000000 |
| log | linux-arm64-docker vs macos-arm64 | 7 of 1000000 | 0 of 1000000 |
| log | linux-arm64-docker vs macos-arm64-atomic | 7 of 1000000 | 0 of 1000000 |
| log | macos-arm64 vs macos-arm64-atomic | 0 of 1000000 | 0 of 1000000 |

