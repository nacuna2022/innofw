#ifndef __INCLUDE_MMIO_H__
#define __INCLUDE_MMIO_H__
#include <types.h>
#include <compiler.h>

/* use these to access device (read: strongly ordered) memory */

static inline __always_inline
reg64_t read64(const addr_t addr)
{
        return *((volatile reg64_t *)addr);
}

static inline __always_inline
reg32_t read32(const addr_t addr)
{
        return *((volatile reg32_t *)addr);
}

static inline __always_inline
reg16_t read16(const addr_t addr)
{
        return *((volatile reg16_t *)addr);
}

static inline __always_inline
reg8_t read8(const addr_t addr)
{
        return *((volatile reg8_t *)addr);
}

static inline __always_inline
void write64(const addr_t addr, const reg64_t v64)
{
        *((volatile reg64_t *)addr) = v64;
        return;
}

static inline __always_inline
void write32(const addr_t addr, const reg64_t v32)
{
        *((volatile reg32_t *)addr) = v32;
        return;
}

static inline __always_inline
void write16(const addr_t addr, const reg64_t v16)
{
        *((volatile reg16_t *)addr) = v16;
        return;
}

static inline __always_inline
void write8(const addr_t addr, const reg64_t v8)
{
        *((volatile reg8_t *)addr) = v8;
        return;
}

#endif /* __INCLUDE_MMIO_H__ */

