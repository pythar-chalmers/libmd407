.PHONY: build clean

C_SOURCES	= $(wildcard src/*.c)
HEADERS		= $(wildcard src/*.h)
OBJ 		= $(C_SOURCES:.c=.o)

CC		= arm-none-eabi-gcc

# Debug flags
CC_FLAGS	= -g -O0 -Wall -Wextra -Wpedantic -mthumb -march=armv6-m -mno-unaligned-access -mfloat-abi=soft -std=gnu17
CC_PREPROC	= SIMULATOR # NOTE: remove when compiling for real hardware

# Release flags
# Use these ↓ flags for when building for release.
# CC_FLAGS	= -g -Os -Wall -Wextra -Werror -mthumb -march=armv6-m -mno-unaligned-access -mfloat-abi=soft -std=gnu17

BUILD_DIR	= build
BUILD_BIN	= MOP

%.o : %.c ${HEADERS}
	mkdir -p ${BUILD_DIR} 
	${CC} -c $< ${CC_FLAGS} -I. -I ${HEADERS}
	arm-none-eabi-g++ -o ${BUILD_DIR}/${BUILD_BIN} -L. *.o -lgcc -lc_nano -Tmd407-ram.x -nostartfiles \
		-L /usr/include/newlib/c++/9.2.1/arm-none-eabi/thumb/v6-m/nofp \
		-L /usr/lib/arm-none-eabi/newlib/thumb/v6-m/nofp \
		-L /usr/lib/gcc/arm-none-eabi/9.2.1/thumb/v6-m/nofp \
		-D ${CC_PREPROC}

build : ${OBJ}
	mv *.o ${BUILD_DIR}/
	arm-none-eabi-objcopy -S -O srec ${BUILD_DIR}/${BUILD_BIN} ${BUILD_DIR}/${BUILD_BIN}.s19
	arm-none-eabi-objdump -D -S ${BUILD_DIR}/${BUILD_BIN} > ${BUILD_DIR}/${BUILD_BIN}.dass

clean:
	rm -rf src/*.o src/*.gch build/ *.o
