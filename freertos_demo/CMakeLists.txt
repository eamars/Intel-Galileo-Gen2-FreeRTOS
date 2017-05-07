MESSAGE("ENTER ${CMAKE_CURRENT_SOURCE_DIR}")

# override linker flags
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -lc -lm -nostartfiles -L${CMAKE_CURRENT_SOURCE_DIR} -T${CMAKE_CURRENT_SOURCE_DIR}/elf_ia32_efi.lds -Wl,--gc-sections -Wl,-Map=symbols.map")

# override executable
SET(EXECUTABLE "FREERTOS_DEMO")

# Collect all source file
FILE (GLOB SRC *.c *.cxx *.cpp *.S)

# include device specific configurations
INCLUDE_DIRECTORIES(${TARGET_SPECIFIC_INCLUDE_DIRECTORY})

# include board specific configurations
INCLUDE_DIRECTORIES(${BOARD_SPECIFIC_INCLUDE_DIRECTORY})

# include common
INCLUDE_DIRECTORIES(${COMMON_INCLUDE_DIRECTORY})

# include definitions from free rtos
INCLUDE_DIRECTORIES(${FREERTOS_INCLUDE_DIRECTORY})

# build source code as library
ADD_EXECUTABLE (${EXECUTABLE}.${ELF_EXTENSION} ${SRC})

ADD_DEPENDENCIES(${EXECUTABLE}.${ELF_EXTENSION} target common)

TARGET_LINK_LIBRARIES(${EXECUTABLE}.${ELF_EXTENSION} target common c)

# include size command
INCLUDE("${PROJECT_SOURCE_DIR}/cmake/size.cmake")

# strip debug info from executable
ADD_CUSTOM_COMMAND(
        TARGET
        ${EXECUTABLE}.${ELF_EXTENSION}
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}.${ELF_EXTENSION}" "${EXECUTABLE_OUTPUT_PATH}/${EXECUTABLE}.${BINARY_EXTENSION}"
)
