#include "simde/x86/avx512/ternarylogic.h"

simde__m128i
ternarylogic (simde__m128i a, simde__m128i b, simde__m128i c) {
  return simde_mm_ternarylogic_epi32(a, b, c, IMM8);
}
