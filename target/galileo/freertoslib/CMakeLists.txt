# configuration for target
MESSAGE("ENTER ${CMAKE_CURRENT_SOURCE_DIR}")

# get module name
GET_FILENAME_COMPONENT(LIB_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# include configuration for the board
INCLUDE_DIRECTORIES("${BOARD_SPECIFIC_INCLUDE_DIRECTORY}")

# include target specific directory
INCLUDE_DIRECTORIES("${TARGET_SPECIFIC_INCLUDE_DIRECTORY}")

# include defintions from common
INCLUDE_DIRECTORIES(${COMMON_INCLUDE_DIRECTORY})

# include freertos directory
INCLUDE_DIRECTORIES("${FREERTOS_INCLUDE_DIRECTORY}")

# Collect all source file
FILE (GLOB FREERTOS_SRC *.c *.S)

# build library for peripherals
ADD_LIBRARY(${LIB_NAME}
        ${FREERTOS_SRC}
)

# ADD_DEPENDENCIES(${LIB_NAME})
# TARGET_LINK_LIBRARIES(${LIB_NAME})
