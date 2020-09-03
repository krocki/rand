#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "rdtsc.h"
#include "rand.h"

double get_time() {
  struct timeval tv; gettimeofday(&tv, NULL);
  return (tv.tv_sec + tv.tv_usec * 1e-6);
}

int main(int argc, char **argv) {

  u64 N = argc > 1 ?
    strtoull(argv[1], NULL, 10) : 1;
  u64 seed = argc > 2 ?
    strtoull(argv[2], NULL, 10) : 0;

  rng_t r;
  rng_init(&r, seed);

  double *arr = calloc(N, sizeof(double));

  double t0 = get_time();
  u64 cs=rdtsc();

  /* generate N numbers */
  for (u64 i=0; i<N; i++) {
    arr[i] = r64f(&r);
  }

  u64 ce=rdtsc();
  double t1 = get_time();

  /* print or save */
  //for (u64 i=0; i<N; i++) {
  //  printf("%.12f\n", arr[i]);
  //}

  double eps=1e-12;

  printf("%llu number(s) in %llu cycles\n"
    "time: %12.9g s, %6.1f cycles/num, %5.2fM num/s\n",
    N, ce-cs, t1-t0,
    (double)(ce-cs)/(double)N,
    (double)N/(1e6 * (t1-t0+eps)));

  if (arr) free(arr);
  return 0;
}
