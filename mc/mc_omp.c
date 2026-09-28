// Monte Carlo estimate of the integral of exp(-x^2) over [0, 1], in C.
//
//   thread  each thread its own generator, seeded from the seed and its number:
//           how it is usually written, and what the samples are depends on
//           how many threads there are
//   index   sample i drawn from splitmix64(seed + i): the same samples at any
//           thread count, so only the summation order and the C library's exp
//           are left to differ
//   philox  sample i drawn from Philox4x32-10 exactly as std/rand's At(seed, i)
//           does, so the samples are the ones the Sword program draws
//
// Both sum with reduction(+) and call exp() from the C library.
// Prints: method,threads,bits,value,median_ns
#include <math.h>
#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static double now_ns(void) {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return t.tv_sec * 1e9 + t.tv_nsec;
}

static int cmp(const void *a, const void *b) {
  double x = *(const double *)a, y = *(const double *)b;
  return (x > y) - (x < y);
}

static uint64_t mix(uint64_t z) {
  z += 0x9E3779B97F4A7C15ull;
  z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
  z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
  return z ^ (z >> 31);
}

static double unit(uint64_t v) { return (double)(v >> 11) * 0x1.0p-53; }

// Philox4x32-10 (Salmon et al. 2011), block 0 of stream i, as std/rand has it.
static uint64_t philox_at(uint64_t seed, uint64_t i) {
  uint32_t x[4] = {0, 0, (uint32_t)i, (uint32_t)(i >> 32)};
  uint32_t k0 = (uint32_t)seed, k1 = (uint32_t)(seed >> 32);
  for (int r = 0; r < 10; r++) {
    if (r > 0) {
      k0 += 0x9E3779B9u;
      k1 += 0xBB67AE85u;
    }
    uint64_t a = (uint64_t)0xD2511F53u * x[0];
    uint64_t b = (uint64_t)0xCD9E8D57u * x[2];
    uint32_t y0 = (uint32_t)(b >> 32) ^ x[1] ^ k0, y1 = (uint32_t)b;
    uint32_t y2 = (uint32_t)(a >> 32) ^ x[3] ^ k1, y3 = (uint32_t)a;
    x[0] = y0, x[1] = y1, x[2] = y2, x[3] = y3;
  }
  return (uint64_t)x[0] | (uint64_t)x[1] << 32;
}

static double by_thread(uint64_t seed, long n) {
  double s = 0.0;
#pragma omp parallel reduction(+ : s)
  {
    uint64_t state = seed ^ ((uint64_t)omp_get_thread_num() + 1) * 0x9E3779B97F4A7C15ull;
#pragma omp for schedule(static)
    for (long i = 0; i < n; i++) {
      state = mix(state);
      double x = unit(state);
      s += exp(-x * x);
    }
  }
  return s / (double)n;
}

static double by_index(uint64_t seed, long n) {
  double s = 0.0;
#pragma omp parallel for reduction(+ : s) schedule(static)
  for (long i = 0; i < n; i++) {
    double x = unit(mix(seed + (uint64_t)i));
    s += exp(-x * x);
  }
  return s / (double)n;
}

static double by_philox(uint64_t seed, long n) {
  double s = 0.0;
#pragma omp parallel for reduction(+ : s) schedule(static)
  for (long i = 0; i < n; i++) {
    double x = unit(philox_at(seed, (uint64_t)i));
    s += exp(-x * x);
  }
  return s / (double)n;
}

int main(int argc, char **argv) {
  if (argc < 4) {
    fprintf(stderr, "usage: mc_omp thread|index|philox samples threads [reps]\n");
    return 2;
  }
  const char *method = argv[1];
  long n = atol(argv[2]);
  int threads = atoi(argv[3]);
  int reps = argc > 4 ? atoi(argv[4]) : 5;
  omp_set_num_threads(threads);
  double result = 0.0, *times = malloc(reps * sizeof *times);
  for (int r = 0; r < reps; r++) {
    double t0 = now_ns();
    result = !strcmp(method, "thread")  ? by_thread(20261013, n)
             : !strcmp(method, "index") ? by_index(20261013, n)
                                        : by_philox(20261013, n);
    times[r] = now_ns() - t0;
  }
  qsort(times, reps, sizeof *times, cmp);
  uint64_t bits;
  memcpy(&bits, &result, 8);
  printf("c-%s,%d,%016llx,%.17g,%.0f\n", method, threads, (unsigned long long)bits,
         result, times[reps / 2]);
  return 0;
}
