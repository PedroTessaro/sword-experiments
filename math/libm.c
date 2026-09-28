// sin, cos, exp and log from the C library over the argument files, each result
// written as raw bits to out/<platform>-libm-<fn>.bin.
// Prints: fn,count,median_ns_per_call
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double now_ns(void) {
  struct timespec t;
  clock_gettime(CLOCK_MONOTONIC, &t);
  return t.tv_sec * 1e9 + t.tv_nsec;
}

static double *load(const char *path, long *n) {
  FILE *f = fopen(path, "rb");
  if (!f) exit(1);
  fseek(f, 0, SEEK_END);
  *n = ftell(f) / 8;
  fseek(f, 0, SEEK_SET);
  double *xs = malloc(*n * 8);
  if (fread(xs, 8, *n, f) != (size_t)*n) exit(1);
  fclose(f);
  return xs;
}

static void run(const char *platform, const char *name, double (*fn)(double),
                const char *args) {
  long n;
  double *xs = load(args, &n), *ys = malloc(n * 8);
  // Volatile through a pointer, so the calls are made and timed.
  double (*volatile call)(double) = fn;
  double best = 1e300;
  for (int r = 0; r < 5; r++) {
    double t0 = now_ns();
    for (long i = 0; i < n; i++) ys[i] = call(xs[i]);
    double t = now_ns() - t0;
    if (t < best) best = t;
  }
  char path[256];
  snprintf(path, sizeof path, "out/%s-libm-%s.bin", platform, name);
  FILE *f = fopen(path, "wb");
  fwrite(ys, 8, n, f);
  fclose(f);
  printf("libm-%s,%ld,%.2f\n", name, n, best / n);
  free(xs);
  free(ys);
}

int main(int argc, char **argv) {
  const char *platform = argc > 1 ? argv[1] : "here";
  run(platform, "sin", sin, "trig.bin");
  run(platform, "sinnear", sin, "near.bin");
  run(platform, "cos", cos, "trig.bin");
  run(platform, "exp", exp, "exp.bin");
  run(platform, "expunit", exp, "unit.bin");
  run(platform, "log", log, "log.bin");
  return 0;
}
