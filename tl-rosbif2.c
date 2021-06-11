#include "/home/nemequ/local/src/simde/simde/x86/sse2.h"

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_ternarylogic_epi32(simde__m128i a, simde__m128i b, simde__m128i c, int imm8)
  SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 255) {
  simde__m128i r, t;
  const simde__m128i zero = simde_mm_setzero_si128();
  const simde__m128i ff = simde_mm_cmpeq_epi8(zero, zero);
  const int bits_set =
    ((imm8 >> 7) & 1) +
    ((imm8 >> 6) & 1) +
    ((imm8 >> 5) & 1) +
    ((imm8 >> 4) & 1) +
    ((imm8 >> 3) & 1) +
    ((imm8 >> 2) & 1) +
    ((imm8 >> 1) & 1) +
    ((imm8 >> 0) & 1);
  const int negate = bits_set > 4;

  if (negate) imm8 = ~imm8;

  r = zero;

  if (imm8 & 0xc0) t = simde_mm_and_si128(a, b);
  if (imm8 & 0x80) r = simde_mm_or_si128(r,    simde_mm_and_si128(c, t));
  if (imm8 & 0x40) r = simde_mm_or_si128(r, simde_mm_andnot_si128(c, t));

  if (imm8 & 0x30) t = simde_mm_andnot_si128(b, a);
  if (imm8 & 0x20) r = simde_mm_or_si128(r,    simde_mm_and_si128(c, t));
  if (imm8 & 0x10) r = simde_mm_or_si128(r, simde_mm_andnot_si128(c, t));

  if (imm8 & 0x0c) t = simde_mm_andnot_si128(a, b);
  if (imm8 & 0x08) r = simde_mm_or_si128(r,    simde_mm_and_si128(c, t));
  if (imm8 & 0x04) r = simde_mm_or_si128(r, simde_mm_andnot_si128(c, t));

  if (imm8 & 0x03) t = simde_mm_xor_si128(simde_mm_or_si128(a, b), ff);
  if (imm8 & 0x02) r = simde_mm_or_si128(r,    simde_mm_and_si128(c, t));
  if (imm8 & 0x01) r = simde_mm_or_si128(r, simde_mm_andnot_si128(c, t));

  if (negate)      r = simde_mm_xor_si128(r, ff);

  return r;
}

simde__m128i
ternarylogic (simde__m128i a, simde__m128i b, simde__m128i c) {
  return simde_mm_ternarylogic_epi32(a, b, c, IMM8);
}
