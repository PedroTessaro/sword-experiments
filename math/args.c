// Arguments for the elementary functions, the same on every machine:
//   trig.bin  x uniform in [-1000, 1000]   for sin and cos
//   near.bin  x uniform in [-pi/4, pi/4]   sin with no argument reduction
//   unit.bin  x uniform in [-1, 0]         exp where the Monte Carlo calls it
//   exp.bin   x uniform in [-700, 700]
//   log.bin   2^e * (1 + u), e uniform in [-1000, 1000]: 600 decades
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t state;

static uint64_t next(void) {
  uint64_t z = (state += 0x9E3779B97F4A7C15ull);
  z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
  z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
  return z ^ (z >> 31);
}

static double unit(void) { return (double)(next() >> 11) * 0x1.0p-53; }

int main(int argc, char **argv) {
  long n = argc > 1 ? atol(argv[1]) : 1000000;
  state = 1974;
  FILE *t = fopen("trig.bin", "wb"), *e = fopen("exp.bin", "wb"), *l = fopen("log.bin", "wb");
  FILE *s = fopen("near.bin", "wb"), *u = fopen("unit.bin", "wb");
  if (!t || !e || !l || !s || !u) return 1;
  for (long i = 0; i < n; i++) {
    // One draw per statement: C leaves the order of a call's arguments, and of
    // a product's operands, to the compiler, and the files must not depend on it.
    double a = (2.0 * unit() - 1.0) * 1000.0;
    double b = (2.0 * unit() - 1.0) * 700.0;
    double cm = 1.0 + unit();
    int ce = (int)(next() % 2001) - 1000;
    double c = ldexp(cm, ce);
    fwrite(&a, 8, 1, t);
    fwrite(&b, 8, 1, e);
    fwrite(&c, 8, 1, l);
    double d = (2.0 * unit() - 1.0) * 0.78539816339744828;
    fwrite(&d, 8, 1, s);
    double g = -unit();
    fwrite(&g, 8, 1, u);
  }
  fclose(t);
  fclose(e);
  fclose(l);
  fclose(s);
  fclose(u);
  return 0;
}
