#include "/home/nemequ/local/src/simde/simde/x86/sse2.h"

SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_ternarylogic_epi32(simde__m128i a, simde__m128i b, simde__m128i c, int imm8)
  SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 255) {
  simde__m128i_private
    r_,
    a_ = simde__m128i_to_private(a),
    b_ = simde__m128i_to_private(b),
    c_ = simde__m128i_to_private(c);

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

  simde_memset(&r_, 0, sizeof(r_));

  SIMDE_VECTORIZE
  for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
    if (imm8 & 0x80) r_.u32[i] |=  a_.u32[i] &  b_.u32[i] &  c_.u32[i];
    if (imm8 & 0x40) r_.u32[i] |=  a_.u32[i] &  b_.u32[i] & ~c_.u32[i];
    if (imm8 & 0x20) r_.u32[i] |=  a_.u32[i] & ~b_.u32[i] &  c_.u32[i];
    if (imm8 & 0x10) r_.u32[i] |=  a_.u32[i] & ~b_.u32[i] & ~c_.u32[i];
    if (imm8 & 0x08) r_.u32[i] |= ~a_.u32[i] &  b_.u32[i] &  c_.u32[i];
    if (imm8 & 0x04) r_.u32[i] |= ~a_.u32[i] &  b_.u32[i] & ~c_.u32[i];
    if (imm8 & 0x02) r_.u32[i] |= ~a_.u32[i] & ~b_.u32[i] &  c_.u32[i];
    if (imm8 & 0x01) r_.u32[i] |= ~a_.u32[i] & ~b_.u32[i] & ~c_.u32[i];
    if (negate)      r_.u32[i]  = ~r_.u32[i];
  }

  return simde__m128i_from_private(r_);
}

simde__m128i
ternarylogic (simde__m128i a, simde__m128i b, simde__m128i c) {
  return simde_mm_ternarylogic_epi32(a, b, c, IMM8);
}
