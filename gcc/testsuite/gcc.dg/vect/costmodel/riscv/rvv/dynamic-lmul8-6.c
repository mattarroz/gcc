/* { dg-do compile } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -ftree-vectorize --param riscv-autovec-lmul=dynamic -fdump-tree-vect-details" } */

#include <stdint-gcc.h>

void
foo (int8_t *__restrict a, int8_t *__restrict b, int8_t *__restrict a2,
     int8_t *__restrict b2, int8_t *__restrict a3, int8_t *__restrict b3,
     int8_t *__restrict a4, int8_t *__restrict b4, int8_t *__restrict a5,
     int8_t *__restrict b5, int n)
{
  for (int i = 0; i < n; i++)
    {
      a[i] = b[i] * a2[i] * b2[i] * a3[i] * b3[i] * a4[i] * b4[i] * a5[i] * b5[i];
    }
}

/* { dg-final { scan-assembler {e8,m8} } } */
/* { dg-final { scan-assembler-not {csrr} } } */
/* { dg-final { scan-tree-dump "Maximum lmul = 8" "vect" } } */
/* { dg-final { scan-tree-dump-not "Maximum lmul = 4" "vect" } } */
/* { dg-final { scan-tree-dump-not "Maximum lmul = 2" "vect" } } */
/* { dg-final { scan-tree-dump-not "Maximum lmul = 1" "vect" } } */
