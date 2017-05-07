MESSAGE("ENTER ${CMAKE_CURRENT_SOURCE_DIR}")

SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED(VERSION 3.8.1)

# set version number
SET (VERSION_MAJOR 0)
SET (VERSION_MINOR 1)

# define project name
PROJECT("Intel Galileo Bare Metal")

# define product
SET(EXECUTABLE)
SET(ELF_EXTENSION "elf")
SET(BINARY_EXTENSION "bin")

# add folder for modules
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

# find compiler
INCLUDE("compiler")

# find git module
INCLUDE("GetGitRevisionDescription")

# enable assembly
ENABLE_LANGUAGE(ASM)

# define generic compiler name
SET(COMPILER_GENERIC_NAME "GCC")

# set target variables
SET (TARGET ${BUILD_TARGET})
MESSAGE ("TARGET: ${TARGET}")

SET(TARGET_ARCH)
SET(TARGET_CORE)

# define directories
SET(BOARD_SPECIFIC_INCLUDE_DIRECTORY)

SET(FREERTOS_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/target/${TARGET}/freertoslib/include")
SET(FREERTOS_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/target/${TARGET}/freertoslib")

SET(COMMON_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/common")
SET(COMMON_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/common")

SET(TARGET_ROOT_DIRECTORY "${CMAKE_SOURCE_DIR}/target/${TARGET}")
SET(TARGET_SPECIFIC_INCLUDE_DIRECTORY "${CMAKE_SOURCE_DIR}/target/${TARGET}") # currently set use the same directory

# parse version info
STRING(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
STRING(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${VERSION}")
SET(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

INCLUDE_DIRECTORIES(/Users/eamars/Workspace/i686-elf/i686-elf/include)

# build modules
ADD_SUBDIRECTORY(target)
ADD_SUBDIRECTORY(common)
ADD_SUBDIRECTORY(freertos_demo)