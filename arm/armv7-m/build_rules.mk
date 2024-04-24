
# architecture-level build rules pull in the tool chain definitions 
# and define architecture level compiler flags and defines
include $(TOPDIR)/arm/$(CONFIG_ARM_ARCH)/toolchain_defs.mk

# armv-m GCC options go here 
ifeq ($(CONFIG_CORTEXM7),y)
CFLAGS+=-mtune=cortex-m7
CFLAGS+=-march=armv7e-m
else ifeq ($(CONFIG_CORTEXM4),y)
CFLAGS+=-mtune=cortex-m7
CFLAGS+=-march=armv7e-m
endif

ifeq ($(CONFIG_HAVE_FPU),y)

ifeq ($(CONFIG_SOFT_FLOATS),y)
CFLAGS+=-mfloat-abi=soft
else
CFLAGS+=-mfloat-abi=hard
CFLAGS+=-mfpu=fpv5-d16
endif # CONFIG_SOFT_FLOATS

else 
CFLAGS+=-mfloat-abi=soft
endif # CONFIG_HAVE_FPU

ifeq ($(CONFIG_THUMB_MODE),y)
CFLAGS+=-mthumb
endif

CFLAGS+=-I$(TOPDIR)/arm/$(CONFIG_ARM_ARCH)/include
