
# Sets the following variables

# ASSIMP_INCLUDE_DIRS - include directories for ASSIMP
# ASSIMP_LIBRARIES - libraries to link against ASSIMP
# ASSIMP_FOUND - true if ASSIMP has been found and can be used
SET(ASSIMP_FOUND "NO")

# default search dirs
SET(_assimp_SEARCH_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp"
	"/usr/include"
	"/usr"
	"/usr/local/include"
	"/opt"
	"/Library/Frameworks"
	"~/Library/Frameworks"
    )

# check environment variable
SET(_assimp_ENV_ROOT_DIR "$ENV{ASSIMP_ROOT_DIR}")

# set ASSIMP ROOT if needed
IF(NOT ASSIMP_ROOT_DIR AND _assimp_ENV_ROOT_DIR)
    SET(ASSIMP_ROOT_DIR "${_assimp_ENV_ROOT_DIR}")
ENDIF(NOT ASSIMP_ROOT_DIR AND _assimp_ENV_ROOT_DIR)

IF(ASSIMP_ROOT_DIR)
    SET(_assimp_HEADER_SEARCH_DIRS "${ASSIMP_ROOT_DIR}"
                                "${ASSIMP_ROOT_DIR}/include"
                                 ${_assimp_SEARCH_DIRS})
ENDIF(ASSIMP_ROOT_DIR)


FIND_PATH(ASSIMP_INCLUDE_DIRS
		assimp/config.h
		${_assimp_SEARCH_DIRS}/include 
		DOC "ASSIMP include directory"
)

FIND_LIBRARY(ASSIMP_LIBRARIES
	NAMES	assimp ASSIMP
	PATHS	${_assimp_SEARCH_DIRS}
	PATH_SUFFIXES
		lib
		lib64
		lib/x86
		lib/x64
	DOC "ASSIMP library"
)

IF (ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES )
	SET(ASSIMP_FOUND TRUE )
	MESSAGE(STATUS "ASSIMP_INCLUDE_DIRS = ${ASSIMP_INCLUDE_DIRS}")
ELSE ( ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES )
	SET( ASSIMP_FOUND FALSE )
	MESSAGE(STATUS "ASSIMP not found")
ENDIF ( ASSIMP_INCLUDE_DIRS AND ASSIMP_LIBRARIES )