
CONFIG_BOARD_NAME:=$(patsubst "%",%,$(CONFIG_BOARD_NAME))
CONFIG_MCU:=$(patsubst "%",%,$(CONFIG_MCU))
CONFIG_ARM_ARCH:=$(patsubst "%",%,$(CONFIG_ARM_ARCH))
CONFIG_IMAGE_NAME:=$(patsubst "%",%,$(CONFIG_IMAGE_NAME))

CFLAGS+=-I$(TOPDIR)/include

define makedepend_c
	@$(CC) $(CFLAGS) $(DEPFLAGS) -MT $(patsubst %.c,%.o,$2) $2 > $1
endef

define make_depend_s
	@$(CC) $(CFLAGS) $(DEPFLAGS) -MT $(patsubst %.S,%.o,$2) $2 > $1
endef

define compile
	@echo "CC $(notdir $1)"
	@$(CC) -c $(CFLAGS) $2 -o $1
endef

define assemble
	@echo "AS $(notdir $1)"
	@$(CC) -c $(CFLAGS) $2 -o $1
endef 

define mkconfig
	@python scripts/mkconfig.py --config $1 --header $2 --project $3
endef

%.ddc: %.c
	$(call makedepend_c, $@, $<)

%.ddS: %.S
	$(call make_depend_s, $@, $<)

%.o: %.c
	$(call compile, $@, $<)

%.o: %.S
	$(call assemble, $@, $<)
