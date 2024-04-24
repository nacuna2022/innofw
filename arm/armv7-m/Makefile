include $(TOPDIR)/.config

ARMV7M_SRCS=
ARMV7M_SRCS+=src/arm_head.c \
	     src/arm_irq.c \
	     src/arm_task.c \
	     src/arm_systick.c\
	     src/arm_idle.c\
	     src/arm_shutdown.c

ARMV7M_ASM=
ARMV7M_ASM+=src/arm_reset.S\
	    src/arm_exception_entry.S

include $(TOPDIR)/scripts/util.mk
include build_rules.mk

LDFLAGS+=-T$(TOPDIR)/$(LINKER_SCRIPT)
ALLMODULES:=$(patsubst %,$(TOPDIR)/%,$(MODULES))

all: $(TARGET)

$(TARGET): $(ARMV7M_SRCS:.c=.o) $(ARMV7M_ASM:.S=.o)
	@echo "LD $@"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(ALLMODULES) $^ \
		-specs=nano.specs -specs=nosys.specs \
                -nostartfiles \
		-o $(TOPDIR)/$@

-include $(ARMV7M_SRCS:.c=.ddc) $(ARMV7M_ASM:.S=.ddS)

