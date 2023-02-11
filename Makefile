# Define the compiler
CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar

# Define the source files
SRCS		= $(wildcard md407/*.c)

# Define the header files
HEADERS		= $(wildcard md407/*.h)

# Define the test files
TEST_SRCS	= $(wildcard test/*.c)

# Define the target libraries
TARGETS = $(SRCS:.c=.a)

# Define the target tests
TEST_TARGETS = $(TEST_SRCS:.c=.o)

# Define the flags for the compiler
# Debug flags
CC_FLAGS	= -g -O0 -Wall -Wextra -Wpedantic -mthumb -march=armv6-m \
			  -L /usr/include/newlib/c++/9.2.1/arm-none-eabi/thumb/v6-m/nofp \
			  -L /usr/lib/arm-none-eabi/newlib/thumb/v6-m/nofp \
			  -L /usr/lib/gcc/arm-none-eabi/9.2.1/thumb/v6-m/nofp \
			  -mno-unaligned-access -mfloat-abi=soft -std=gnu17 -nostartfiles -I.

# Release flags. Use these ↓ flags for when building for release.
# CC_FLAGS	= -g -Os -Wall -Wextra -Werror -mthumb -march=armv6-m -mno-unaligned-access -mfloat-abi=soft -std=gnu17 -I.

# Define the build directory
BUILD_DIR		= build
TEST_BUILD_DIR	= build-tests

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the built libraries
BUILT_LIBS = $(addprefix $(BUILD_DIR)/, $(TARGETS))

# Define the default target for the Makefile
all: $(BUILT_LIBS)

# Rule to build the target libraries
$(BUILD_DIR)/%.a: $(BUILD_DIR)/%.o
	$(AR) rcs $@ $^

$(BUILD_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS) -c $< -o $@

# Rule to build and test the sources inside the tests directory
test: $(TEST_TARGETS) $(BUILT_LIBS)
	@mkdir -p $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_TARGETS) $(BUILT_LIBS) -o $(TEST_BUILD_DIR)/test
	$(TEST_BUILD_DIR)/test

$(TEST_BUILD_DIR)/%.o: $(TEST_SRCS) $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to build all the files
build: $(BUILT_LIBS)

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
	rm -rf $(TEST_BUILD_DIR)

# Dependency to ensure the build directory is created
$(BUILT_LIBS): $(addprefix $(BUILD_DIR)/, $(OBJS))

.PHONY: all build install uninstall test
