# configuration for target
MESSAGE("ENTER ${CMAKE_CURRENT_SOURCE_DIR}")

# get module name
GET_FILENAME_COMPONENT(LIB_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# include configuration for the board
INCLUDE_DIRECTORIES("${BOARD_SPECIFIC_INCLUDE_DIRECTORY}")

# include target specific directory
INCLUDE_DIRECTORIES("${TARGET_SPECIFIC_INCLUDE_DIRECTORY}")

# enable drivers to build
SET(ENABLED_DRIVERS gpio_i2c hpet quark_x1000 pci io_register legacy gpio)

# build modules
FOREACH(MODULE ${ENABLED_DRIVERS})
    # update include list
    SET(TARGET_SPECIFIC_INCLUDE_DIRECTORY ${TARGET_SPECIFIC_INCLUDE_DIRECTORY} "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}")

    # compile those libraries
    ADD_SUBDIRECTORY("${MODULE}")
ENDFOREACH(MODULE)

# build library for peripherals
ADD_LIBRARY(${LIB_NAME}
        "drivers.c"
)

ADD_DEPENDENCIES(${LIB_NAME}
        ${ENABLED_DRIVERS}
)

TARGET_LINK_LIBRARIES(${LIB_NAME}
        ${ENABLED_DRIVERS}
)

# forward include header files
SET(TARGET_SPECIFIC_INCLUDE_DIRECTORY ${TARGET_SPECIFIC_INCLUDE_DIRECTORY} PARENT_SCOPE)