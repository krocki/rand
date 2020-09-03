#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "rdtsc.h"
#include "rand.h"

typedef unsigned long long llu;

double get_time() {
  struct timeval tv; gettimeofday(&tv, NULL);
  return (tv.tv_sec + tv.tv_usec * 1e-6);
}

int main(int argc, char **argv) {

  u64 N = argc > 1 ?
    (1 << strtoull(argv[1], NULL, 10)) : 1;
  u64 seed = argc > 2 ?
    strtoull(argv[2], NULL, 10) : 0;

  rng_t rng_state;
  rng_init(&rng_state, seed);

  u64 *arr = calloc(N, sizeof(u64));

  double eps=1e-12;
  double t0, t1;
  u64 cs, ce;

  /* start time */
  t0 = get_time(); cs = rdtsc();

  /* generate N numbers */
  for (u64 i=0; i<N; i++) { arr[i] = r64(&rng_state); }

  /* end time */
  ce = rdtsc(); t1 = get_time();

  printf("RNG: %llu number(s) in %llu cycles\n"
    "time: %12.9g s, %6.1f cycles/num, %5.2fM num/s\n",
    (llu)N, (llu)(ce-cs), t1-t0,
    (double)(ce-cs)/(double)N,
    (double)N/(1e6 * (t1-t0+eps)));

  /* free */
  if (arr) free(arr);

  return 0;
}
