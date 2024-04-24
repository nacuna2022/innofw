#ifndef __INCLUDE__TYPES_H__
#define __INCLUDE__TYPES_H__
#include <config.h>
#include <stdint.h>

/* exact width types */
typedef uint8_t         u8;
typedef uint16_t        u16;
typedef uint32_t        u32;
typedef uint64_t        u64;

/* register definitions */
typedef uint64_t        reg64_t;
typedef uint32_t        reg32_t;
typedef uint16_t        reg16_t;
typedef uint8_t         reg8_t;

typedef uint32_t        irqflag_t;

/* for addresses use this */
typedef uintptr_t       addr_t;

#endif /* __INCLUDE_TYPES_H__ */
