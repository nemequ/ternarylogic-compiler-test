#include "simde/x86/sse2.h"

#ifndef ROSBIF_VERSION
#define ROSBIF_VERSION 5
#endif

#if ROSBIF_VERSION == 1
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

  SIMDE_VECTORIZE
  for (size_t i = 0 ; i < (sizeof(r_.u32) / sizeof(r_.u32[0])) ; i++) {
    r_.u32[i] = 0;
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
#elif ROSBIF_VERSION == 2
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
#elif ROSBIF_VERSION == 3
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
#elif ROSBIF_VERSION == 4
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
#elif ROSBIF_VERSION == 5
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
#endif

simde__m128i
ternarylogic (simde__m128i a, simde__m128i b, simde__m128i c) {
  return simde_mm_ternarylogic_epi32(a, b, c, IMM8);
}
