#include "../include/jit_engine.h"
#include <sys/mman.h>
#include <stdexcept>
#include <libkern/OSCacheControl.h>

JITEngine::JITEngine(size_t size) : buffer_size(size) {
    // Allocation بە یاسای JIT Memory لە iOS
    code_buffer = mmap(NULL, buffer_size, PROT_READ | PROT_WRITE | PROT_EXEC,
                       MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (code_buffer == MAP_FAILED) {
        throw std::runtime_error("JIT Allocation Failed");
    }
}

void JITEngine::write_code(const uint32_t* instructions, size_t count) {
    // گۆڕینی R/W ڕاستەوخۆ بە mprotect بۆ iOS
    mprotect(code_buffer, buffer_size, PROT_READ | PROT_WRITE);
    
    uint32_t* dest = static_cast<uint32_t*>(code_buffer);
    for (size_t i = 0; i < count; ++i) {
        dest[i] = instructions[i];
    }
    
    mprotect(code_buffer, buffer_size, PROT_READ | PROT_EXEC);
    sys_icache_invalidate(code_buffer, count * sizeof(uint32_t));
}

JITEngine::~JITEngine() {
    munmap(code_buffer, buffer_size);
}
