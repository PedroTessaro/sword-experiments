# Results

## gh-linux-arm64

```
platform: gh-linux-arm64
date: 2026-09-28T01:41:16Z
uname: Linux 6.17.0-1022-azure aarch64
cpu: 0xd49
cores: 4
cc: gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
openmp: -fopenmp
shield: shield 0.1.0 (Tamahagane)
sword commit: 23acc20
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
| c-serial | 1 of 1 | 237 | 6.41 | 6.41 | 1 |
| c-omp | 7 of 8 | 20–237 | 6.60 | 1.73 | 4 |
| c-ompkahan | 1 of 8 | 0 | 23.81 | 5.96 | 4 |
| sword-plain | 1 of 8 | 4 | 6.79 | 1.80 | 4 |
| sword-kahan | 1 of 8 | 0 | 24.90 | 6.25 | 4 |
| sword-exact | 1 of 8 | 0 | 33.93 | 9.40 | 4 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 6.61 | 6.61 | 1 |
| c-omp | 8 of 8 | 37–243 | 7.07 | 1.63 | 4 |
| c-ompkahan | 3 of 8 | 0–1 | 23.74 | 5.98 | 4 |
| sword-plain | 1 of 8 | 30 | 6.65 | 1.70 | 4 |
| sword-kahan | 1 of 8 | 0 | 24.94 | 6.26 | 4 |
| sword-exact | 1 of 8 | 0 | 60.63 | 16.05 | 6 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 4 | 20 | 1 |
| sword-plain | 4 | 20 | 1 |
| c-omp | 8 | 20 | 3 |
| sword-plain | 8 | 20 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440205 … 0.74692123466732596 | 49.4 | 12.4 | 4 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 48.0 | 12.1 | 4 |
| c-philox | 7 of 8 | 0.74688899599929437 … 0.74688899599935521 | 180.0 | 45.1 | 4 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 228.7 | 57.8 | 4 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 93.4 | 23.5 | 10 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 288.6 | 74.9 | 6 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 15.42 | 16.31 |
| sinnear | 6.94 | 3.15 |
| cos | 15.65 | 16.38 |
| exp | 6.12 | 8.73 |
| expunit | 3.22 | 7.19 |
| log | 4.04 | 8.31 |

## gh-linux-x86_64

```
platform: gh-linux-x86_64
date: 2026-09-28T01:41:25Z
uname: Linux 6.17.0-1022-azure x86_64
cpu: INTEL(R) XEON(R) PLATINUM 8573C
cores: 4
cc: gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
openmp: -fopenmp
shield: shield 0.1.0 (Tamahagane)
sword commit: 23acc20
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
| c-serial | 1 of 1 | 237 | 5.71 | 5.71 | 1 |
| c-omp | 7 of 8 | 20–237 | 5.65 | 1.43 | 4 |
| c-ompkahan | 1 of 8 | 0 | 22.51 | 5.66 | 4 |
| sword-plain | 1 of 8 | 4 | 5.77 | 1.49 | 4 |
| sword-kahan | 1 of 8 | 0 | 14.62 | 6.68 | 4 |
| sword-exact | 1 of 8 | 0 | 32.87 | 17.02 | 6 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 5.65 | 5.65 | 1 |
| c-omp | 8 of 8 | 37–243 | 5.64 | 1.45 | 4 |
| c-ompkahan | 3 of 8 | 0–1 | 22.51 | 5.66 | 4 |
| sword-plain | 1 of 8 | 30 | 5.68 | 1.53 | 4 |
| sword-kahan | 1 of 8 | 0 | 14.67 | 6.68 | 4 |
| sword-exact | 1 of 8 | 0 | 73.53 | 28.27 | 6 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 4 | 20 | 1 |
| sword-plain | 4 | 20 | 1 |
| c-omp | 8 | 20 | 3 |
| sword-plain | 8 | 20 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440205 … 0.74692123466732596 | 62.1 | 28.1 | 4 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 60.0 | 27.6 | 8 |
| c-philox | 8 of 8 | 0.74688899599929437 … 0.74688899599935532 | 170.9 | 73.6 | 4 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 398.6 | 112.0 | 4 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 111.3 | 38.7 | 4 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 423.5 | 124.3 | 16 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 17.00 | 19.27 |
| sinnear | 5.58 | 1.88 |
| cos | 16.54 | 19.00 |
| exp | 7.98 | 5.64 |
| expunit | 4.42 | 6.35 |
| log | 3.78 | 5.77 |

## gh-macos-arm64

```
platform: gh-macos-arm64
date: 2026-09-28T01:41:24Z
uname: Darwin 25.6.0 arm64
cpu: Apple M1 (Virtual)
cores: 3
cc: Apple clang version 21.0.0 (clang-2100.1.1.101)
openmp: -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp
shield: shield 0.1.0 (Tamahagane)
sword commit: 23acc20
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
| c-serial | 1 of 1 | 237 | 11.13 | 11.13 | 1 |
| c-omp | 7 of 8 | 20–237 | 10.61 | 4.02 | 8 |
| c-ompkahan | 1 of 8 | 0 | 46.87 | 14.57 | 4 |
| sword-plain | 1 of 8 | 4 | 9.93 | 3.71 | 8 |
| sword-kahan | 1 of 8 | 0 | 15.11 | 4.19 | 10 |
| sword-exact | 1 of 8 | 0 | 38.16 | 9.79 | 8 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 10.42 | 10.42 | 1 |
| c-omp | 8 of 8 | 37–243 | 12.51 | 3.62 | 3 |
| c-ompkahan | 3 of 8 | 0–1 | 53.66 | 14.56 | 3 |
| sword-plain | 1 of 8 | 30 | 11.22 | 3.60 | 6 |
| sword-kahan | 1 of 8 | 0 | 17.22 | 4.24 | 6 |
| sword-exact | 1 of 8 | 0 | 82.63 | 25.38 | 8 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 4 | 20 | 1 |
| sword-plain | 4 | 20 | 1 |
| c-omp | 8 | 20 | 1 |
| sword-plain | 8 | 20 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440216 … 0.74692123466732596 | 89.3 | 18.2 | 6 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 50.1 | 10.1 | 3 |
| c-philox | 7 of 8 | 0.74688899599929437 … 0.74688899599935521 | 148.9 | 35.6 | 16 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 357.6 | 89.9 | 16 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 154.2 | 41.1 | 16 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 436.2 | 139.6 | 8 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 8.40 | 19.91 |
| sinnear | 2.08 | 2.64 |
| cos | 8.25 | 20.07 |
| exp | 6.25 | 5.79 |
| expunit | 2.48 | 6.90 |
| log | 2.93 | 7.50 |

## linux-arm64-docker

```
platform: linux-arm64-docker
date: 2026-09-28T01:41:39Z
uname: Linux 7.0.12-linuxkit aarch64
cpu: 0x000
cores: 10
cc: gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
openmp: -fopenmp
shield: shield 0.1.0 (Tamahagane)
sword commit: 23acc20
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
| c-serial | 1 of 1 | 237 | 5.71 | 5.71 | 1 |
| c-omp | 7 of 8 | 21–237 | 5.72 | 1.11 | 8 |
| c-ompkahan | 1 of 8 | 0 | 19.14 | 3.71 | 10 |
| sword-plain | 1 of 8 | 4 | 5.32 | 0.95 | 10 |
| sword-kahan | 1 of 8 | 0 | 11.89 | 2.06 | 16 |
| sword-exact | 1 of 8 | 0 | 17.46 | 3.39 | 16 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 5.76 | 5.76 | 1 |
| c-omp | 8 of 8 | 37–243 | 5.71 | 1.10 | 8 |
| c-ompkahan | 3 of 8 | 0–1 | 19.14 | 3.90 | 10 |
| sword-plain | 1 of 8 | 30 | 5.37 | 0.93 | 10 |
| sword-kahan | 1 of 8 | 0 | 11.92 | 2.01 | 10 |
| sword-exact | 1 of 8 | 0 | 47.23 | 7.77 | 16 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 4 | 20 | 1 |
| sword-plain | 4 | 20 | 1 |
| c-omp | 8 | 20 | 3 |
| sword-plain | 8 | 20 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440216 … 0.74692123466732607 | 33.1 | 5.7 | 10 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 15.5 | 3.5 | 8 |
| c-philox | 7 of 8 | 0.74688899599929437 … 0.74688899599935521 | 86.4 | 17.5 | 16 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 156.1 | 26.0 | 16 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 68.5 | 11.5 | 16 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 316.7 | 44.5 | 16 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 10.92 | 12.07 |
| sinnear | 3.53 | 2.14 |
| cos | 11.52 | 11.98 |
| exp | 4.10 | 2.46 |
| expunit | 2.21 | 4.17 |
| log | 2.26 | 2.79 |

## macos-arm64

```
platform: macos-arm64
date: 2026-09-28T01:41:00Z
uname: Darwin 27.0.0 arm64
cpu: Apple M4
cores: 10
cc: Apple clang version 21.0.0 (clang-2100.3.34.2)
openmp: -Xpreprocessor -fopenmp -I/opt/homebrew/opt/libomp/include -L/opt/homebrew/opt/libomp/lib -lomp
shield: shield 0.1.0 (Tamahagane)
sword commit: 23acc20
python: Python 3.14.7
threads: 1 2 3 4 6 8 10 16
sum_n: 10000000 mc_n: 10000000 math_n: 1000000 reps: 7
only: all
note: Apple M4, 4 performance and 6 efficiency cores
```

### E1 — summation of 10^7 doubles

**uniform** (correctly rounded sum 5000576.9172228221)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 237 | 6.79 | 6.79 | 1 |
| c-omp | 7 of 8 | 20–237 | 5.06 | 0.94 | 10 |
| c-ompkahan | 1 of 8 | 0 | 19.84 | 3.28 | 10 |
| sword-plain | 1 of 8 | 4 | 5.83 | 0.83 | 10 |
| sword-kahan | 1 of 8 | 0 | 6.63 | 1.10 | 16 |
| sword-exact | 1 of 8 | 0 | 17.05 | 3.05 | 16 |

**mixed** (correctly rounded sum 159165645829.89481)

| method | distinct results | error (ULPs) | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-serial | 1 of 1 | 243 | 5.01 | 5.01 | 1 |
| c-omp | 8 of 8 | 37–243 | 5.01 | 0.94 | 10 |
| c-ompkahan | 3 of 8 | 0–1 | 19.91 | 3.24 | 10 |
| sword-plain | 1 of 8 | 30 | 5.04 | 0.85 | 10 |
| sword-kahan | 1 of 8 | 0 | 6.64 | 1.07 | 16 |
| sword-exact | 1 of 8 | 0 | 45.27 | 6.88 | 16 |

### E1b — the same run repeated, thread count fixed (mixed data)

| method | threads | runs | distinct results |
|---|---|---|---|
| c-omp | 4 | 20 | 1 |
| sword-plain | 4 | 20 | 1 |
| c-omp | 8 | 20 | 1 |
| sword-plain | 8 | 20 | 1 |

### E2 — Monte Carlo, integral of exp(-x²) on [0, 1]

| method | distinct results | values seen | 1 thread (ms) | fastest (ms) | at threads |
|---|---|---|---|---|---|
| c-thread | 8 of 8 | 0.74684708827440216 … 0.74692123466732596 | 32.2 | 5.9 | 16 |
| c-index | 8 of 8 | 0.74675913289815332 … 0.74675913289820595 | 19.9 | 3.9 | 16 |
| c-philox | 7 of 8 | 0.74688899599929437 … 0.74688899599935521 | 59.8 | 11.6 | 16 |
| sword-plain | 1 of 8 | 0.74688899599934544 | 157.4 | 26.1 | 16 |
| sword-mix | 1 of 8 | 0.74675913289817852 | 70.4 | 11.5 | 16 |
| sword-exact | 1 of 8 | 0.74688899599934688 | 310.6 | 38.4 | 16 |

### E3 — elementary functions, cost

| function | C library (ns/call) | std/num (ns/call) |
|---|---|---|
| sin | 6.57 | 11.83 |
| sinnear | 1.27 | 1.41 |
| cos | 5.49 | 12.12 |
| exp | 4.20 | 2.78 |
| expunit | 1.76 | 4.28 |
| log | 1.67 | 3.37 |

## E1, E2 — Sword's answers on different platforms

| experiment | method | platforms | runs | distinct results |
|---|---|---|---|---|
| E1 mixed | c-serial | 5 | 5 | 1 |
| E1 mixed | c-omp | 5 | 40 | 11 |
| E1 mixed | c-ompkahan | 5 | 40 | 3 |
| E1 mixed | sword-plain | 5 | 40 | 1 |
| E1 mixed | sword-kahan | 5 | 40 | 1 |
| E1 mixed | sword-exact | 5 | 40 | 1 |
| E1 uniform | c-serial | 5 | 5 | 1 |
| E1 uniform | c-omp | 5 | 40 | 11 |
| E1 uniform | c-ompkahan | 5 | 40 | 1 |
| E1 uniform | sword-plain | 5 | 40 | 1 |
| E1 uniform | sword-kahan | 5 | 40 | 1 |
| E1 uniform | sword-exact | 5 | 40 | 1 |
| E2 | c-thread | 5 | 40 | 14 |
| E2 | c-index | 5 | 40 | 11 |
| E2 | c-philox | 5 | 40 | 10 |
| E2 | sword-plain | 5 | 40 | 1 |
| E2 | sword-mix | 5 | 40 | 1 |
| E2 | sword-exact | 5 | 40 | 1 |

## E3 — the same arguments on different platforms

| function | platforms | C library: results that differ | std/num: results that differ |
|---|---|---|---|
| sin | gh-linux-arm64 vs gh-linux-x86_64 | 0 of 1000000 | 0 of 1000000 |
| sin | gh-linux-arm64 vs gh-macos-arm64 | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-linux-arm64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| sin | gh-linux-arm64 vs macos-arm64 | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-linux-x86_64 vs gh-macos-arm64 | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-linux-x86_64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| sin | gh-linux-x86_64 vs macos-arm64 | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-macos-arm64 vs linux-arm64-docker | 40563 of 1000000 | 0 of 1000000 |
| sin | gh-macos-arm64 vs macos-arm64 | 0 of 1000000 | 0 of 1000000 |
| sin | linux-arm64-docker vs macos-arm64 | 40563 of 1000000 | 0 of 1000000 |
| cos | gh-linux-arm64 vs gh-linux-x86_64 | 0 of 1000000 | 0 of 1000000 |
| cos | gh-linux-arm64 vs gh-macos-arm64 | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-linux-arm64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| cos | gh-linux-arm64 vs macos-arm64 | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-linux-x86_64 vs gh-macos-arm64 | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-linux-x86_64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| cos | gh-linux-x86_64 vs macos-arm64 | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-macos-arm64 vs linux-arm64-docker | 40715 of 1000000 | 0 of 1000000 |
| cos | gh-macos-arm64 vs macos-arm64 | 0 of 1000000 | 0 of 1000000 |
| cos | linux-arm64-docker vs macos-arm64 | 40715 of 1000000 | 0 of 1000000 |
| exp | gh-linux-arm64 vs gh-linux-x86_64 | 0 of 1000000 | 0 of 1000000 |
| exp | gh-linux-arm64 vs gh-macos-arm64 | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-linux-arm64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| exp | gh-linux-arm64 vs macos-arm64 | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-linux-x86_64 vs gh-macos-arm64 | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-linux-x86_64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| exp | gh-linux-x86_64 vs macos-arm64 | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-macos-arm64 vs linux-arm64-docker | 1765 of 1000000 | 0 of 1000000 |
| exp | gh-macos-arm64 vs macos-arm64 | 0 of 1000000 | 0 of 1000000 |
| exp | linux-arm64-docker vs macos-arm64 | 1765 of 1000000 | 0 of 1000000 |
| log | gh-linux-arm64 vs gh-linux-x86_64 | 0 of 1000000 | 0 of 1000000 |
| log | gh-linux-arm64 vs gh-macos-arm64 | 7 of 1000000 | 0 of 1000000 |
| log | gh-linux-arm64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| log | gh-linux-arm64 vs macos-arm64 | 7 of 1000000 | 0 of 1000000 |
| log | gh-linux-x86_64 vs gh-macos-arm64 | 7 of 1000000 | 0 of 1000000 |
| log | gh-linux-x86_64 vs linux-arm64-docker | 0 of 1000000 | 0 of 1000000 |
| log | gh-linux-x86_64 vs macos-arm64 | 7 of 1000000 | 0 of 1000000 |
| log | gh-macos-arm64 vs linux-arm64-docker | 7 of 1000000 | 0 of 1000000 |
| log | gh-macos-arm64 vs macos-arm64 | 0 of 1000000 | 0 of 1000000 |
| log | linux-arm64-docker vs macos-arm64 | 7 of 1000000 | 0 of 1000000 |

