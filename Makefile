MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)
C_FLAGS  = -c -O0 -mcpu=cortex-m0plus -mthumb -g3
OPENOCD_FLAGS = -f interface/stlink.cfg -f target/stm32g0x.cfg
BUILD_DIR = build

SRCS = \
	main.c \
	peripheral.c \

OBJECTS := $(patsubst %,$(BUILD_DIR)/%.o,$(basename $(SRCS)))
$(shell mkdir -p $(dir $(OBJECTS)) >/dev/null)

LINKER_SCRIPT = LinkerScript.ld

#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S# cpu

CPU = -mcpu=cortex-m0plus

.PHONY: all
all: $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex $(BUILD_DIR)/main.bin

.PHONY: flash
flash: $(BUILD_DIR)/main.elf all
	openocd $(OPENOCD_FLAGS) -c "program $< reset" -c "shutdown"

.PHONY: clean
clean:
	rm -rf build

$(BUILD_DIR)/%.o: %.c
	$(CC) $(C_FLAGS) -o $@ $<

$(BUILD_DIR)/main.elf: $(OBJECTS) MakeFile $(LINKER_SCRIPT)
	$(CC) -o $@ $(OBJECTS) -mcpu=cortex-m0plus -T"$(LINKER_SCRIPT)" --specs=nosys.specs -Wl,-Map="minimal.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf |
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf |
	$(BIN) $< $@
