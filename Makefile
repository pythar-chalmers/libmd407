# Defaults
# NOTE: change this to install in different dir.
DESTDIR = /usr/arm-none-eabi

# Define the compiler
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar

# Define lib & test sources directory
LIB_SRC_DIR			= md407
TEST_SRC_DIR		= test

# Define the source files
SRCS		= $(wildcard $(LIB_SRC_DIR)/*.c)

# Define the header files
HEADERS		= $(wildcard $(LIB_SRC_DIR)/*.h)

# Define the test files
TEST_SRCS	= $(wildcard $(TEST_SRC_DIR)/*.c)

# Define the target libraries
TARGETS = $(SRCS:.c=.a)

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the target tests
TEST_OBJS = $(TEST_SRCS:.c=.o)

# Define the flags for the compiler
# Debug flags
CC_FLAGS	=	-g -O0 -Wall -Wextra -Wpedantic -mthumb -march=armv6-m \
				-lgcc -lc_nano -Tmd407-ram.x \
				-L /usr/include/newlib/c++/9.2.1/arm-none-eabi/thumb/v6-m/nofp \
				-L /usr/lib/arm-none-eabi/newlib/thumb/v6-m/nofp \
				-L /usr/lib/gcc/arm-none-eabi/9.2.1/thumb/v6-m/nofp \
				-mno-unaligned-access -mfloat-abi=soft -std=gnu17 -nostartfiles -I.

# Define the build directory
BUILD_DIR		= build
# BUILD_DIR	= build-tests

# Define the built libraries
BUILT_LIBS = $(addprefix $(BUILD_DIR)/, $(TARGETS))
BUILT_LIBS_OBJ = $(addprefix $(BUILD_DIR)/, $(OBJS))

# Define the built tests
BUILT_TESTS = $(TEST_OBJS:.o=)

# Rule to build the target libraries
$(BUILD_DIR)/$(LIB_SRC_DIR)/%.a: $(BUILD_DIR)/$(LIB_SRC_DIR)/%.o
	$(AR) rcs $@ $^

$(BUILD_DIR)/$(LIB_SRC_DIR)/%.o: $(LIB_SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c $< -o $@

# Rule to build and test the sources inside the tests directory
$(BUILD_DIR)/$(TEST_SRC_DIR)/%: $(BUILD_DIR)/$(TEST_SRC_DIR)/%.o $(BUILT_LIBS_OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CC_FLAGS) $< $(BUILT_LIBS_OBJ) -o $(BUILD_DIR)/$@

$(BUILD_DIR)/$(TEST_SRC_DIR)/%.o: $(TEST_SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -I$(HEADERS) -c $< -o $(BUILD_DIR)/$@

# Rule to build all the files
build: $(BUILT_LIBS)
test: $(BUILT_TESTS)

# Rule to install the header files and libraries
install: build
	mkdir -p $(DESTDIR)/include/md407
	cp $(HEADERS) $(DESTDIR)/include/md407
	mkdir -p $(DESTDIR)/lib/md407
	cp $(BUILT_LIBS) $(DESTDIR)/lib/md407

# Rule to uninstall the header files and libraries
uninstall:
	rm -rf $(DESTDIR)/include/md407
	rm -rf $(DESTDIR)/lib/md407

# Rule to clean up the object files and target libraries
clean:
	rm -rf $(BUILD_DIR)

# Dependency to ensure the build directory is created
$(BUILT_LIBS): $(addprefix $(BUILD_DIR)/, $(OBJS))

# Define the default target for the Makefile
all: build

.PHONY: all build install uninstall test
