// Writes the inputs every summation experiment reads, as raw little-endian
// doubles, so that C and Sword add exactly the same numbers.
//
//   uniform.bin  n values in [0, 1): well conditioned, every term positive.
//   mixed.bin    n values (2u - 1) * 2^e, e uniform in [-30, 30]: signs mixed
//                and magnitudes over 18 decades, so rounding shows.
//
// splitmix64 from a fixed seed: the same files on every machine.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static uint64_t state;

static uint64_t next(void) {
  uint64_t z = (state += 0x9E3779B97F4A7C15ull);
  z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
  z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
  return z ^ (z >> 31);
}

static double unit(void) { return (double)(next() >> 11) * 0x1.0p-53; }

int main(int argc, char **argv) {
  long n = argc > 1 ? atol(argv[1]) : 10000000;
  state = 20261013;
  FILE *u = fopen("uniform.bin", "wb");
  FILE *m = fopen("mixed.bin", "wb");
  if (!u || !m) return 1;
  for (long i = 0; i < n; i++) {
    double a = unit();
    fwrite(&a, sizeof a, 1, u);
    // One draw per statement: C leaves the order of a product's operands to
    // the compiler, and the file must not depend on it.
    double bm = 2.0 * unit() - 1.0;
    int be = (int)(next() % 61) - 30;
    double b = bm * ldexp(1.0, be);
    fwrite(&b, sizeof b, 1, m);
  }
  fclose(u);
  fclose(m);
  return 0;
}
