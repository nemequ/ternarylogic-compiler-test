#include "simde/x86/sse2.h"

#if 0
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
#elif defined(SIMDE_VECTOR_SUBSCRIPT_OPS)
SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_ternarylogic_epi32(simde__m128i a, simde__m128i b, simde__m128i c, int imm8)
  SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 255) {
  simde__m128i_private
    r_, t_,
    a_ = simde__m128i_to_private(a),
    b_ = simde__m128i_to_private(b),
    c_ = simde__m128i_to_private(c);
  int to_do, mask;

  to_do = imm8;

  r_.u64 = a_.u64 ^ a_.u64;

  mask = 0xFF;
  if ((to_do & mask) == mask) {
    r_.u64 = ~r_.u64;
    to_do &= ~mask;
  }

  mask = 0xF0;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 = a_.u64;
    to_do &= ~mask;
  }

  mask = 0xCC;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= b_.u64;
    to_do &= ~mask;
  }

  mask = 0xAA;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= c_.u64;
    to_do &= ~mask;
  }

  mask = 0x0F;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= ~a_.u64;
    to_do &= ~mask;
  }

  mask = 0x33;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= ~b_.u64;
    to_do &= ~mask;
  }

  mask = 0x55;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= ~c_.u64;
    to_do &= ~mask;
  }

  mask = 0x3C;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= a_.u64 ^ b_.u64;
    to_do &= ~mask;
  }

  mask = 0x5A;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= a_.u64 ^ c_.u64;
    to_do &= ~mask;
  }

  mask = 0x66;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= b_.u64 ^ c_.u64;
    to_do &= ~mask;
  }

  mask = 0xA0;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= a_.u64 & c_.u64;
    to_do &= ~mask;
  }

  mask = 0x50;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= ~c_.u64 & a_.u64;
    to_do &= ~mask;
  }

  mask = 0x0A;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= ~a_.u64 & c_.u64;
    to_do &= ~mask;
  }

  mask = 0x88;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= b_.u64 & c_.u64;
    to_do &= ~mask;
  }

  mask = 0x44;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= ~c_.u64 & b_.u64;
    to_do &= ~mask;
  }

  mask = 0x22;
  if ((to_do & mask) && ((imm8 & mask) == mask)) {
    r_.u64 |= ~b_.u64 & c_.u64;
    to_do &= ~mask;
  }

  if (to_do & 0xc0) {
    t_.u64 = a_.u64 & b_.u64;
    if ((to_do & 0xc0) == 0xc0) r_.u64 |= t_.u64;
    else if (to_do & 0x80)      r_.u64 |=  c_.u64 & t_.u64;
    else                        r_.u64 |= ~c_.u64 & t_.u64;
  }

  if (to_do & 0x30) {
    t_.u64 = ~b_.u64 & a_.u64;
    if ((to_do & 0x30) == 0x30) r_.u64 |= t_.u64;
    else if (to_do & 0x20)      r_.u64 |=  c_.u64 & t_.u64;
    else                        r_.u64 |= ~c_.u64 & t_.u64;
  }

  if (to_do & 0x0c) {
    t_.u64 = ~a_.u64 & b_.u64;
    if ((to_do & 0x0c) == 0x0c) r_.u64 |= t_.u64;
    else if (to_do & 0x08)      r_.u64 |=  c_.u64 & t_.u64;
    else                        r_.u64 |= ~c_.u64 & t_.u64;
  }

  if (to_do & 0x03) {
    t_.u64 = ~(a_.u64 | b_.u64);
    if ((to_do & 0x03) == 0x03) r_.u64 |= t_.u64;
    else if (to_do & 0x02)      r_.u64 |=  c_.u64 & t_.u64;
    else                        r_.u64 |= ~c_.u64 & t_.u64;
  }

  return simde__m128i_from_private(r_);
}
#else
/* clang generates crazy inefficient code for imm8 = 24, 26, 28, 30, 36, 38, 44, 52, 54, 56, 78, 88, 100, 114 */
/* (I only tested up to 127 as I was doing this by hand) */
/* For these bad cases the RThroughput is about three times lower with u64 instead of u32 */
/* The clang code also seems to be better for many other values. */
SIMDE_FUNCTION_ATTRIBUTES
simde__m128i
simde_mm_ternarylogic_epi32(simde__m128i a, simde__m128i b, simde__m128i c, int imm8)
  SIMDE_REQUIRE_CONSTANT_RANGE(imm8, 0, 255) {
  simde__m128i_private
    r_,
    a_ = simde__m128i_to_private(a),
    b_ = simde__m128i_to_private(b),
    c_ = simde__m128i_to_private(c);
  uint64_t t;
  int to_do, mask;

  SIMDE_VECTORIZE
  for (size_t i = 0 ; i < (sizeof(r_.u64) / sizeof(r_.u64[0])) ; i++) {
    to_do = imm8;

    mask = 0xFF;
    if ((to_do & mask) == mask) {
      r_.u64[i] = UINT64_MAX;
      to_do &= ~mask;
    }
    else r_.u64[i] = 0;

    mask = 0xF0;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] = a_.u64[i];
      to_do &= ~mask;
    }

    mask = 0xCC;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= b_.u64[i];
      to_do &= ~mask;
    }

    mask = 0xAA;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= c_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x0F;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= ~a_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x33;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= ~b_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x55;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= ~c_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x3C;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= a_.u64[i] ^ b_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x5A;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= a_.u64[i] ^ c_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x66;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= b_.u64[i] ^ c_.u64[i];
      to_do &= ~mask;
    }

    mask = 0xA0;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= a_.u64[i] & c_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x50;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= ~c_.u64[i] & a_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x0A;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= ~a_.u64[i] & c_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x88;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= b_.u64[i] & c_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x44;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= ~c_.u64[i] & b_.u64[i];
      to_do &= ~mask;
    }

    mask = 0x22;
    if ((to_do & mask) && ((imm8 & mask) == mask)) {
      r_.u64[i] |= ~b_.u64[i] & c_.u64[i];
      to_do &= ~mask;
    }

    if (to_do & 0xc0) {
      t = a_.u64[i] & b_.u64[i];
      if ((to_do & 0xc0) == 0xc0) r_.u64[i] |= t;
      else if (to_do & 0x80)      r_.u64[i] |=  c_.u64[i] & t;
      else                        r_.u64[i] |= ~c_.u64[i] & t;
    }

    if (to_do & 0x30) {
      t = ~b_.u64[i] & a_.u64[i];
      if ((to_do & 0x30) == 0x30) r_.u64[i] |= t;
      else if (to_do & 0x20)      r_.u64[i] |=  c_.u64[i] & t;
      else                        r_.u64[i] |= ~c_.u64[i] & t;
    }

    if (to_do & 0x0c) {
      t = ~a_.u64[i] & b_.u64[i];
      if ((to_do & 0x0c) == 0x0c) r_.u64[i] |= t;
      else if (to_do & 0x08)      r_.u64[i] |=  c_.u64[i] & t;
      else                        r_.u64[i] |= ~c_.u64[i] & t;
    }

    if (to_do & 0x03) {
      t = ~(a_.u64[i] | b_.u64[i]);
      if ((to_do & 0x03) == 0x03) r_.u64[i] |= t;
      else if (to_do & 0x02)      r_.u64[i] |=  c_.u64[i] & t;
      else                        r_.u64[i] |= ~c_.u64[i] & t;
    }
  }

  return simde__m128i_from_private(r_);
}
#endif

simde__m128i
ternarylogic (simde__m128i a, simde__m128i b, simde__m128i c) {
  return simde_mm_ternarylogic_epi32(a, b, c, IMM8);
}
