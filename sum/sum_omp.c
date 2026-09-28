// The sum of a file of doubles, the way it is usually written in C.
//
//   serial    one loop, one thread
//   omp       #pragma omp parallel for reduction(+) schedule(static)
//   ompkahan  each thread a compensated (Kahan) sum, partials combined in
//             thread order
//
// Prints: method,threads,bits,value,median_ns
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

static double serial(const double *xs, long n) {
  double s = 0.0;
  for (long i = 0; i < n; i++) s += xs[i];
  return s;
}

static double omp(const double *xs, long n) {
  double s = 0.0;
#pragma omp parallel for reduction(+ : s) schedule(static)
  for (long i = 0; i < n; i++) s += xs[i];
  return s;
}

static double ompkahan(const double *xs, long n) {
  int t = omp_get_max_threads();
  double *sums = calloc(t, sizeof *sums), *lost = calloc(t, sizeof *lost);
#pragma omp parallel
  {
    int me = omp_get_thread_num();
    double s = 0.0, c = 0.0;
#pragma omp for schedule(static)
    for (long i = 0; i < n; i++) {
      double y = xs[i] - c;
      double u = s + y;
      c = (u - s) - y;
      s = u;
    }
    sums[me] = s;
    lost[me] = c;
  }
  double s = 0.0, c = 0.0;
  for (int k = 0; k < t; k++) {
    double y = (sums[k] - lost[k]) - c;
    double u = s + y;
    c = (u - s) - y;
    s = u;
  }
  free(sums);
  free(lost);
  return s;
}

int main(int argc, char **argv) {
  if (argc < 4) {
    fprintf(stderr, "usage: sum_omp file serial|omp|ompkahan threads [reps]\n");
    return 2;
  }
  const char *method = argv[2];
  int threads = atoi(argv[3]);
  int reps = argc > 4 ? atoi(argv[4]) : 7;
  omp_set_num_threads(threads);

  FILE *f = fopen(argv[1], "rb");
  if (!f) return 1;
  fseek(f, 0, SEEK_END);
  long n = ftell(f) / 8;
  fseek(f, 0, SEEK_SET);
  double *xs = malloc(n * sizeof *xs);
  if (fread(xs, 8, n, f) != (size_t)n) return 1;
  fclose(f);

  double (*fn)(const double *, long) =
      !strcmp(method, "serial") ? serial : !strcmp(method, "omp") ? omp : ompkahan;
  double result = 0.0, *times = malloc(reps * sizeof *times);
  for (int r = 0; r < reps; r++) {
    double t0 = now_ns();
    result = fn(xs, n);
    times[r] = now_ns() - t0;
  }
  qsort(times, reps, sizeof *times, cmp);
  uint64_t bits;
  memcpy(&bits, &result, 8);
  printf("c-%s,%d,%016llx,%.17g,%.0f\n", method, threads, (unsigned long long)bits,
         result, times[reps / 2]);
  return 0;
}
