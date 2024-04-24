CONFIG_TOOLCHAIN_PREFIX:=$(patsubst "%",%,$(CONFIG_TOOLCHAIN_PREFIX))

CC:=$(CONFIG_TOOLCHAIN_PREFIX)-gcc
AS:=$(CONFIG_TOOLCHAIN_PREFIX)-as
AR:=$(CONFIG_TOOLCHAIN_PREFIX)-ar
LD:=$(CONFIG_TOOLCHAIN_PREFIX)-ld
NM:=$(CONFIG_TOOLCHAIN_PREFIX)-nm
OBJDUMP:=$(CONFIG_TOOLCHAIN_PREFIX)-objdump
OBJCOPY:=$(CONFIG_TOOLCHAIN_PREFIX)-objcopy

DEPFLAGS=-MM -MP

#always default to little endian
#ifeq ($(CONFIG_ENDIAN),y)
#CFLAGS+=-mlittle-endian
#endif

#optimization
# we have three none -O0, normal -O2, aggressive -O3
# gcc have other optimization levels like optimizing for speed -Os and 
# optimizing for size -Os but we limit ourselves to safe values
ifeq ($(CONFIG_OPTIMIZATION_NONE),y)
OPTIMIZATION_FLAGS=-O0 -ggdb
else ifeq ($(CONFIG_OPTIMIZATION_NORMAL),y)
OPTIMIZATION_FLAGS=-O2 -ggdb
else ifeq ($(CONFIG_OPTIMIZATION_AGRRESSIVE),y)
OPTIMIZATION_FLAGS=-O3 -ggdb
endif
CFLAGS+=$(OPTIMIZATION_FLAGS)

#LDFLAGS+=-T$(LINKERSCRIPT)

#print memory usage 
LDFLAGS+=-Wl,--print-memory-usage

ifeq ($(CONFIG_GENERATE_LINK_MAP),y)
LDFLAGS+=-Wl,-Map $(TOPDIR)/$(MAPFILE)
endif

