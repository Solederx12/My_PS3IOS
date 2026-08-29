#ifndef SPU_CORE_H
#define SPU_CORE_H

#include <arm_neon.h>

class SPUCore {
public:
    static uint32x4_t add_v32(uint32x4_t a, uint32x4_t b);
    static float32x4_t fma_vf32(float32x4_t a, float32x4_t b, float32x4_t c);
};

#endif
