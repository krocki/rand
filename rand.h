// K.Rocki
// 9/3/2020

#ifndef __RAND_H__
#define __RAND_H__

#include <stdint.h>

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;

/* DEFAULT */
/* numerical recipes 7.1.2    */
/* ran: combination of 4 rngs */
/* period 3.1 * 10^58         */
/* ~ 5.7 cycles / 64-bit num  */

/* RNG2 */
/* numerical recipes ranq2    */
/* period 8.5 * 10^37         */
/* ~ 4.6 cycles / 64-bit num  */

typedef struct {
  u64 u,v,w;
} rng_t;

#if RNG2
static inline u64
r64(rng_t *r) {
  r->v ^= r->v >> 17;
  r->v ^= r->v << 31;
  r->v ^= r->v >> 8;
  r->w = 4294957665U *
    (r->w & 0xffffffff) +
    (r->w >> 32);
  return (r->w) ^ (r->v);
}
void
rng_init(rng_t *r, u64 j) {
  r->v = j ^ 4101842887655102017LL;
  r->w = r64(r);
  r->u = r64(r);
};

#else
static inline u64
r64(rng_t *r) {
  r->u = r->u *
    2862933555777941757LL +
    7046029254386353087LL;
  r->v ^= r->v >> 17;
  r->v ^= r->v << 31;
  r->v ^= r->v >> 8;
  r->w = 4294957665U *
    (r->w & 0xffffffff) +
    (r->w >> 32);
  u64 x = r->u ^ (r->u << 21);
  x ^= x >> 35; x ^= x << 4;
  return (x + r->v) ^ (r->w);
}
void
rng_init(rng_t *r, u64 j) {
  r->v = 4101842887655102017LL;
  r->w = 1;
  r->u = j ^ r->v; r64(r);
  r->v = r->u; r64(r);
  r->w = r->v; r64(r);
};

#endif

static inline double
f64(rng_t *r) {
  return 5.42101086242752217E-20 * r64(r);
};

#endif
