/* { dg-do compile } */
/* { dg-options "-march=rv32gcv -mabi=ilp32 -O3 -ftree-vectorize --param riscv-autovec-lmul=dynamic -fselective-scheduling -fdump-tree-vect-details" } */

#include <stdint-gcc.h>

void
foo (uint8_t *restrict a, uint8_t *restrict b, int n)
{
  for (int i = 0; i < n; ++i)
    {
      a[i * 8] = b[i * 8 + 7] + 1;
      a[i * 8 + 1] = b[i * 8 + 6] + 2;
      a[i * 8 + 2] = b[i * 8 + 5] + 3;
      a[i * 8 + 3] = b[i * 8 + 4] + 4;
      a[i * 8 + 4] = b[i * 8 + 3] + 5;
      a[i * 8 + 5] = b[i * 8 + 2] + 6;
      a[i * 8 + 6] = b[i * 8 + 1] + 7;
      a[i * 8 + 7] = b[i * 8 + 0] + 8;
    }
}

/* { dg-final { scan-assembler {e8,m4} } } */
/* { dg-final { scan-assembler-times {csrr} 1 } } */
/* { dg-final { scan-tree-dump-not "Maximum lmul = 8" "vect" } } */
/* { dg-final { scan-tree-dump "Maximum lmul = 4" "vect" } } */
/* { dg-final { scan-tree-dump-not "Maximum lmul = 2" "vect" } } */
/* { dg-final { scan-tree-dump-not "Maximum lmul = 1" "vect" } } */
