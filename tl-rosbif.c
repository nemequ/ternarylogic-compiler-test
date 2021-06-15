#include "simde/x86/sse2.h"

#if 0
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
#else
SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_ternarylogic_epi32(simde__m128i a, simde__m128i b, simde__m128i c, int imm8)
  SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 255) {
  simde__m128i r, t;
  const simde__m128i zero = simde_mm_setzero_si128();
  const simde__m128i ff = simde_mm_cmpeq_epi8(zero, zero);
  int to_do, mask;

  to_do = imm8;

  mask = 0xFF;
  if ((to_do & mask) == mask) {
    r = ff;
    to_do &= ~mask;
  }
  else r = zero;

  mask = 0xF0;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = a;
    to_do &= ~mask;
  }

  mask = 0xCC;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, b);
    to_do &= ~mask;
  }

  mask = 0xAA;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, c);
    to_do &= ~mask;
  }

  mask = 0x0F;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_xor_si128(a, ff));
    to_do &= ~mask;
  }

  mask = 0x33;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_xor_si128(b, ff));
    to_do &= ~mask;
  }

  mask = 0x55;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_xor_si128(c, ff));
    to_do &= ~mask;
  }

  mask = 0x3C;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_xor_si128(a, b));
    to_do &= ~mask;
  }

  mask = 0x5A;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_xor_si128(a, c));
    to_do &= ~mask;
  }

  mask = 0x66;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_xor_si128(b, c));
    to_do &= ~mask;
  }

  mask = 0xA0;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_and_si128(a, c));
    to_do &= ~mask;
  }

  mask = 0x50;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_andnot_si128(c, a));
    to_do &= ~mask;
  }

  mask = 0x0A;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_andnot_si128(a, c));
    to_do &= ~mask;
  }

  mask = 0x88;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_and_si128(b, c));
    to_do &= ~mask;
  }

  mask = 0x44;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_andnot_si128(c, b));
    to_do &= ~mask;
  }

  mask = 0x22;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r = simde_mm_or_si128(r, simde_mm_andnot_si128(b, c));
    to_do &= ~mask;
  }

  if (to_do & 0xc0) {
    t = simde_mm_and_si128(a, b);
    if ((to_do & 0xc0) == 0xc0) r = simde_mm_or_si128(r, t);
    else if (to_do & 0x80)      r = simde_mm_or_si128(r,    simde_mm_and_si128(c, t));
    else                        r = simde_mm_or_si128(r, simde_mm_andnot_si128(c, t));
  }

  if (to_do & 0x30) {
    t = simde_mm_andnot_si128(b, a);
    if ((to_do & 0x30) == 0x30) r = simde_mm_or_si128(r, t);
    else if (to_do & 0x20)      r = simde_mm_or_si128(r,    simde_mm_and_si128(c, t));
    else                        r = simde_mm_or_si128(r, simde_mm_andnot_si128(c, t));
  }

  if (to_do & 0x0c) {
    t = simde_mm_andnot_si128(a, b);
    if ((to_do & 0x0c) == 0x0c) r = simde_mm_or_si128(r, t);
    else if (to_do & 0x08)      r = simde_mm_or_si128(r,    simde_mm_and_si128(c, t));
    else                        r = simde_mm_or_si128(r, simde_mm_andnot_si128(c, t));
  }

  if (to_do & 0x03) {
    t = simde_mm_xor_si128(simde_mm_or_si128(a, b), ff);
    if ((to_do & 0x03) == 0x03) r = simde_mm_or_si128(r, t);
    else if (to_do & 0x02)      r = simde_mm_or_si128(r,    simde_mm_and_si128(c, t));
    else                        r = simde_mm_or_si128(r, simde_mm_andnot_si128(c, t));
  }
  return r;
}
#endif

simde__m128i
ternarylogic (simde__m128i a, simde__m128i b, simde__m128i c) {
  return simde_mm_ternarylogic_epi32(a, b, c, IMM8);
}
