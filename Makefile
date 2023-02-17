# Defaults
# NOTE: change this to install in different dir.
DESTDIR = /usr/arm-none-eabi

# Define the compiler
CC		= arm-none-eabi-gcc
AR		= arm-none-eabi-ar
OBJCOPY = arm-none-eabi-objcopy

# Define lib & test sources directory
LIB_SRC_DIR			= md407
TEST_SRC_DIR		= test

# Define the library files
LIBRARY_SRCS = $(wildcard $(LIB_SRC_DIR)/*.h)

# Define the test files
TEST_SRCS	= $(wildcard $(TEST_SRC_DIR)/*.c)

# Define the target tests
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Define the .s19 tests
TEST_S19 = $(TEST_SRCS:.c=.s19)

# Define the flags for the compiler
CC_FLAGS	=	-O0 -Wall -Wextra -Wpedantic -mthumb -march=armv6-m \
				-lgcc -lc_nano -Tmd407-ram.x \
				-L /usr/include/newlib/c++/9.2.1/arm-none-eabi/thumb/v6-m/nofp \
				-L /usr/lib/arm-none-eabi/newlib/thumb/v6-m/nofp \
				-L /usr/lib/gcc/arm-none-eabi/9.2.1/thumb/v6-m/nofp \
				-mno-unaligned-access -mfloat-abi=soft -std=gnu17 -nostartfiles -I. \
				-g \
				-D SIMULATOR

# NOTE: Remove "-D SIMULATOR" if compiling for actual hardware
# IMPORTANT: Remove "-g" to remove debug crap and reduce size

OBJCOPY_FLAGS = -O srec

# Define the build directory
BUILD_DIR		= build

# Define the built tests
BUILT_TESTS = $(addprefix $(BUILD_DIR)/, $(TEST_OBJS:.o=)) $(addprefix $(BUILD_DIR)/, $(TEST_S19))

# Rule to build the test sources inside the tests directory
$(BUILD_DIR)/$(TEST_SRC_DIR)/%: $(BUILD_DIR)/$(TEST_SRC_DIR)/%.o $(BUILT_LIBS_OBJ)
	$(CC) $(CC_FLAGS) $^ -o $@

$(BUILD_DIR)/$(TEST_SRC_DIR)/%.o: $(TEST_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_SRC_DIR)/%.s19: $(BUILD_DIR)/$(TEST_SRC_DIR)/%
	$(OBJCOPY) $(OBJCOPY_FLAGS) $< $@

# Rule to build all the files
test: $(BUILT_TESTS)

# Rule to install the header files and libraries
install: build
	mkdir -p $(DESTDIR)/include/md407
	cp $(LIBRARY_SRCS) $(DESTDIR)/include/md407

# Rule to uninstall the header files and libraries
uninstall:
	rm -rf $(DESTDIR)/include/md407

# Rule to clean up the object files and target libraries
clean:
	rm -rf $(BUILD_DIR)

# Define the default target for the Makefile
all: test

.PHONY: test all install uninstall
