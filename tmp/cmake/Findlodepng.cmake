# Sets the following variables

# LODE_PNG_INCLUDE_DIRS - include directories for LODE_PNG
# LODE_PNG_LIBRARIES - libraries to link against LODE_PNG
# LODE_PNG_FOUND - true if LODE_PNG has been found and can be used

SET(LODE_PNG_FOUND "NO")

# default search dirs
SET(_lode_png_SEARCH_DIRS
	"./libs/lodepng"
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
                                "${LODE_PNG_ROOT_DIR}"
                                 ${_lode_png_SEARCH_DIRS})
ENDIF(LODE_PNG_ROOT_DIR)


FIND_PATH(LODE_PNG_INCLUDE_DIRS
		lode_png/lode_png.h
		${_lode_png_SEARCH_DIRS}/include 
		DOC "LODE_PNG include directory"
)

IF (LODE_PNG_INCLUDE_DIRS)
	SET(LODE_PNG_FOUND TRUE )
	MESSAGE(STATUS "LODE_PNG_INCLUDE_DIRS = ${LODE_PNG_INCLUDE_DIRS}")
ELSE ( LODE_PNG_INCLUDE_DIRS)
	SET( LODE_PNG_FOUND FALSE )
	MESSAGE(STATUS "LODE_PNG not found")
ENDIF ( LODE_PNG_INCLUDE_DIRS)