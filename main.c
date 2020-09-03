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

  rng0_t r0;
  rng1_t r1;

  rng0_init(&r0, seed);
  rng1_init(&r1, seed);

  u64 *arr0 = calloc(N, sizeof(u64));
  u64 *arr1 = calloc(N, sizeof(u64));

  double t0 = get_time();
  u64 cs = rdtsc();

  /* generate N numbers */
  for (u64 i=0; i<N; i++) {
    arr0[i] = r64(&r0);
  }

  u64 ce = rdtsc();
  double t1 = get_time();
  double eps=1e-12;

  printf("RNG0: %llu number(s) in %llu cycles\n"
    "time: %12.9g s, %6.1f cycles/num, %5.2fM num/s\n",
    N, ce-cs, t1-t0,
    (double)(ce-cs)/(double)N,
    (double)N/(1e6 * (t1-t0+eps)));

  t0 = get_time();
  cs = rdtsc();

  /* generate N numbers */
  for (u64 i=0; i<N; i++) {
    arr1[i] = rng1_r64(&r1);
  }

  ce = rdtsc();
  t1 = get_time();

  if (arr0) free(arr0);
  if (arr1) free(arr1);

  printf("RNG1: %llu number(s) in %llu cycles\n"
    "time: %12.9g s, %6.1f cycles/num, %5.2fM num/s\n",
    N, ce-cs, t1-t0,
    (double)(ce-cs)/(double)N,
    (double)N/(1e6 * (t1-t0+eps)));

  /* print or save */
  //for (u64 i=0; i<N; i++) {
  //  printf("%.12f\n", arr[i]);
  //}

  return 0;
}
