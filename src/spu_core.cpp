#include "../include/spu_core.h"

uint32x4_t SPUCore::add_v32(uint32x4_t a, uint32x4_t b) {
    return vaddq_u32(a, b);
}

float32x4_t SPUCore::fma_vf32(float32x4_t a, float32x4_t b, float32x4_t c) {
    return vfmaq_f32(c, a, b);
}
