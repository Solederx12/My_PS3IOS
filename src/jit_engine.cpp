#include "../include/jit_engine.h"
#include <sys/mman.h>
#include <pthread.h>
#include <stdexcept>

JITEngine::JITEngine(size_t size) : buffer_size(size) {
    // دابینکردنی شوێنی execution له میمۆری بە هەمان یاسای iOS Dynamic Codesigning
    code_buffer = mmap(NULL, buffer_size, PROT_READ | PROT_WRITE | PROT_EXEC,
                       MAP_PRIVATE | MAP_ANONYMOUS | MAP_JIT, -1, 0);
    if (code_buffer == MAP_FAILED) {
        throw std::runtime_error("JIT Allocation Failed");
    }
}

void JITEngine::write_code(const uint32_t* instructions, size_t count) {
    pthread_jit_write_protect_np(0);
    uint32_t* dest = static_cast<uint32_t*>(code_buffer);
    for (size_t i = 0; i < count; ++i) {
        dest[i] = instructions[i];
    }
    pthread_jit_write_protect_np(1);
    sys_icache_invalidate(code_buffer, count * sizeof(uint32_t));
}

JITEngine::~JITEngine() {
    munmap(code_buffer, buffer_size);
}
