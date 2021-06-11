#include "ternary_sse.cpp"

__m128i
mula_ternarylogic (__m128i a, __m128i b, __m128i c) {
  return ternarylogic::sse::ternary<IMM8>(a, b, c);
}
