#ifndef JIT_ENGINE_H
#define JIT_ENGINE_H

#include <cstddef>
#include <cstdint>

class JITEngine {
private:
    void* code_buffer;
    size_t buffer_size;

public:
    JITEngine(size_t size);
    void write_code(const uint32_t* instructions, size_t count);
    ~JITEngine();
};

#endif
