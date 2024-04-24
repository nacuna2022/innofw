#ifndef __ARM_INCLUDE_ARM_REGS_H__
#define __ARM_INCLUDE_ARM_REGS_H__
#include <types.h>
#include <compiler.h>

#define SCS_ADDR        (0xE000E000UL)

#define SCB_ADDR        (SCS_ADDR + 0x0D00UL)
#define DBG_ADDR        (SCS_ADDR + 0x0DF0UL)
#define SWI_ADDR        (SCS_ADDR + 0x0F00UL)
#define CACHE_ADDR      (SCS_ADDR + 0x0F50UL)
#define UCID_ADDR       (SCS_ADDR + 0x0FD0UL) /* uController-specific ID space */

#define SYSTICK_ADDR    (SCS_ADDR + 0x0010UL)
#define NVIC_ADDR       (SCS_ADDR + 0x0100UL)
#define MPU_ADDR        (SCS_ADDR + 0x0D90UL)
#define FPU_ADDR        (SCS_ADDR + 0x0F00UL)

/* SC BLock */
#define CPUID           (SCB_ADDR + 0x00UL)
#define ICSR            (SCB_ADDR + 0x04UL)
#define VTOR            (SCB_ADDR + 0x08UL)
#define AIRCR           (SCB_ADDR + 0x0CUL)
#define SCR             (SCB_ADDR + 0x10UL)
#define CCR             (SCB_ADDR + 0x14UL)
#define SHPR1           (SCB_ADDR + 0x18UL)
#define SHPR2           (SCB_ADDR + 0x1CUL)
#define SHPR3           (SCB_ADDR + 0x20UL)
#define SHCSR           (SCB_ADDR + 0x24UL)
#define CFSR            (SCB_ADDR + 0x28UL)
#define HFSR            (SCB_ADDR + 0x2CUL)
#define DFSR            (SCB_ADDR + 0x30UL)
#define MMFAR           (SCB_ADDR + 0x34UL)
#define BFAR            (SCB_ADDR + 0x38UL)
#define AFSR            (SCB_ADDR + 0x3CUL)

/* Processor feature block */
#define ID_PFR0         (SCB_ADDR + 0x40UL)
#define ID_PFR1         (SCB_ADDR + 0x44UL)
#define ID_DFR0         (SCB_ADDR + 0x48UL)
#define ID_AFR0         (SCB_ADDR + 0x4CUL)
#define ID_MMFR0        (SCB_ADDR + 0x50UL)
#define ID_MMFR1        (SCB_ADDR + 0x54UL)
#define ID_MMFR2        (SCB_ADDR + 0x58UL)
#define ID_MMFR3        (SCB_ADDR + 0x5CUL)
#define ID_ISAR0        (SCB_ADDR + 0x60UL)
#define ID_ISAR1        (SCB_ADDR + 0x64UL)
#define ID_ISAR2        (SCB_ADDR + 0x68UL)
#define ID_ISAR3        (SCB_ADDR + 0x6CUL)
#define ID_ISAR4        (SCB_ADDR + 0x70UL)
#define ID_ISAR5        (SCB_ADDR + 0x74UL)
#define CLIDR           (SCB_ADDR + 0x78UL)
#define CTR             (SCB_ADDR + 0x7CUL)
#define CCSIDR          (SCB_ADDR + 0x80UL)
#define CSSELR          (SCB_ADDR + 0x84UL)

#define CPACR           (SCB_ADDR + 0x88UL)

/* SYSTICK block */
#define SYST_CSR        (SYSTICK_ADDR + 0x0UL)
#define SYST_RVR        (SYSTICK_ADDR + 0x4UL)
#define SYST_CVR        (SYSTICK_ADDR + 0x8UL)
#define SYST_CALIB      (SYSTICK_ADDR + 0xCUL)


/* NVIC block */
#define NVIC_ISER0      (NVIC_ADDR + 0x00UL)
#define NVIC_ICER0      (NVIC_ADDR + 0x80UL)
#define NVIC_ISPR0      (NVIC_ADDR + 0x100UL)
#define NVIC_ICPR0      (NVIC_ADDR + 0x180UL)
#define NVIC_IABR0      (NVIC_ADDR + 0x200UL)
#define NVIC_IPR0       (NVIC_ADDR + 0x300UL)



/* FP Extension block */
#define FPCCR           (FPU_ADDR + 0x34UL)
#define FPCAR           (FPU_ADDR + 0x38UL)
#define FPDSCR          (FPU_ADDR + 0x3CUL)
#define MVFR0           (FPU_ADDR + 0x40UL)       
#define MVFR1           (FPU_ADDR + 0x44UL)
#define MVFR2           (FPU_ADDR + 0x48UL)

#endif /* __ARM_INCLUDE_ARM_REGS_H__ */

