# Sets the following variables

# LODE_PNG_INCLUDE_DIRS - include directories for LODE_PNG
# LODE_PNG_LIBRARIES - libraries to link against LODE_PNG
# LODE_PNG_FOUND - true if LODE_PNG has been found and can be used

SET(LODE_PNG_FOUND "NO")

# default search dirs
SET(_lode_png_SEARCH_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/lodepng"
    "/usr/include"
	"/usr"
	"/usr/local/include"
	"/opt"
	"/Library/Frameworks"
	"~/Library/Frameworks"
    )

# check environment variable
SET(_lode_png_ENV_ROOT_DIR "$ENV{LODE_PNG_ROOT_DIR}")

# set LODE_PNG ROOT if needed
IF(NOT LODE_PNG_ROOT_DIR AND _lode_png_ENV_ROOT_DIR)
    SET(LODE_PNG_ROOT_DIR "${_lode_png_ENV_ROOT_DIR}")
ENDIF(NOT LODE_PNG_ROOT_DIR AND _lode_png_ENV_ROOT_DIR)

IF(LODE_PNG_ROOT_DIR)
    SET(_lode_png_SEARCH_DIRS "${LODE_PNG_ROOT_DIR}"
                                "${LODE_PNG_ROOT_DIR}/include"
                                 ${_lode_png_SEARCH_DIRS})
ENDIF(LODE_PNG_ROOT_DIR)

FIND_PATH(LODE_PNG_INCLUDE_DIR "lode_png/lode_png.hpp"
    PATHS ${_lode_png_SEARCH_DIRS})

message(STATUS "lode_png.hpp: ${LODE_PNG_INCLUDE_DIR}")

IF (LODE_PNG_INCLUDE_PATH AND LODE_PNG_LIBRARY)
    SET(LODE_PNG_LIBRARIES ${LODE_PNG_LIBRARY})
    SET(LODE_PNG_FOUND "YES")
ENDIF (LODE_PNG_INCLUDE_PATH AND LODE_PNG_LIBRARY)

IF(NOT LODE_PNG_FOUND)
    MESSAGE(STATUS "LODE_PNG not found")
ENDIF(NOT LODE_PNG_FOUND)

IF(LODE_PNG_FOUND)
    SET(LODE_PNG_INCLUDE_DIRS "${LODE_PNG_INCLUDE_DIR}")
    MESSAGE(STATUS "LODE_PNG_INCLUDE_DIR = ${LODE_PNG_INCLUDE_DIR}")
ENDIF(LODE_PNG_FOUND)
