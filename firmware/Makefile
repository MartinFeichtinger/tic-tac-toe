#####################################################################################################################################
# Project Configuration
#####################################################################################################################################
MCU = attiny461a
FORMAT = ihex
OPT = s
DEBUG = dwarf-2
CSTANDARD = -std=gnu99

TARGET_NAME = tic-tac-toe
BIN_DIR = bin
BUILD_DIR = build
SRC_DIR = src

# Programmer Settings (DIAMEX ISP-PROG-NG)
AVRDUDE       = avrdude
AD_MCU        = t461
AD_PROGRAMMER = stk500v2
AD_PORT       = /dev/ttyACM0

#####################################################################################################################################
# Toolchain & Flags
#####################################################################################################################################
CC      = avr-gcc
OBJCOPY = avr-objcopy
SIZE    = avr-size
REMOVE  = rm -f

# Find all source files for the main project (excluding tests)
# We find everything in src/ but we will filter out tests in the OBJ list
SRC = $(shell find $(SRC_DIR) -name '*.c' | grep -v "/tests/")

# Include Paths (Adds -I to each directory)
EXTRAINCDIRS = $(SRC_DIR)/app $(SRC_DIR)/driver $(SRC_DIR)/hal $(SRC_DIR)
CINCS = $(patsubst %,-I%,$(EXTRAINCDIRS))

# Compiler Flags
CFLAGS = -g$(DEBUG) -O$(OPT)
CFLAGS += -fsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -Wall -Wstrict-prototypes $(CSTANDARD)
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS) $(CINCS)
LDFLAGS = -lm

#####################################################################################################################################
# Derived Paths
#####################################################################################################################################
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TARGET_ELF = $(BIN_DIR)/$(TARGET_NAME).elf
TARGET_HEX = $(BIN_DIR)/$(TARGET_NAME).hex

#####################################################################################################################################
# Main Build Rules
#####################################################################################################################################
.PHONY: all clean flash test flash_test

all: $(BIN_DIR) $(BUILD_DIR) $(TARGET_HEX)
	@echo "Build finished: $(TARGET_HEX)"
	@$(SIZE) --mcu=$(MCU) -C $(TARGET_ELF)

$(TARGET_HEX): $(TARGET_ELF)
	@echo "Creating Hex: $@"
	@$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

$(TARGET_ELF): $(OBJ)
	@echo "Linking: $@"
	@$(CC) $(ALL_CFLAGS) $^ --output $@ $(LDFLAGS)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	@$(CC) -c $(ALL_CFLAGS) $< -o $@

#####################################################################################################################################
# Test Section
# Call with: make flash_test TEST_FILE=src/tests/hw_integration/basic_speaker_test.c
#####################################################################################################################################
TEST_NAME = $(basename $(notdir $(TEST_FILE)))
TEST_HEX = $(BIN_DIR)/test_$(TEST_NAME).hex
TEST_ELF = $(BIN_DIR)/test_$(TEST_NAME).elf

test: $(BIN_DIR) $(BUILD_DIR) $(TEST_HEX)
	@echo "Test-Build finished: $(TEST_HEX)"

$(TEST_HEX): $(TEST_ELF)
	@$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

$(TEST_ELF): $(TEST_FILE) $(filter-out %main.o, $(OBJ))
	@echo "Linking Test: $@"
	@$(CC) $(ALL_CFLAGS) $^ --output $@ $(LDFLAGS)

#####################################################################################################################################
# Flashing Section
#####################################################################################################################################
flash: all
	$(AVRDUDE) -p $(AD_MCU) -c $(AD_PROGRAMMER) -P $(AD_PORT) -U flash:w:$(TARGET_HEX):i

flash_test: test
	$(AVRDUDE) -p $(AD_MCU) -c $(AD_PROGRAMMER) -P $(AD_PORT) -U flash:w:$(TEST_HEX):i

#####################################################################################################################################
# Cleanup
#####################################################################################################################################
$(BIN_DIR) $(BUILD_DIR):
	mkdir -p $@

clean:
	@echo "Cleaning project..."
	@rm -rf $(BIN_DIR) $(BUILD_DIR)