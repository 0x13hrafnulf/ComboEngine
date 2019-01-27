# Sets the following variables

# GLEW_INCLUDE_DIRS - include directories for GLEW
# GLEW_LIBRARIES - libraries to link against GLEW
# GLEW_FOUND - true if GLEW has been found and can be used

SET(GLEW_FOUND "NO")

# default search dirs
SET(_glew_SEARCH_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glew"
    "/usr/include"
	"/usr"
	"/usr/local/include"
	"/opt"
	"/Library/Frameworks"
	"~/Library/Frameworks"
    )

# check environment variable
SET(_glew_ENV_ROOT_DIR "$ENV{GLEW_ROOT_DIR}")

# set GLEW ROOT if needed
IF(NOT GLEW_ROOT_DIR AND _glew_ENV_ROOT_DIR)
    SET(GLEW_ROOT_DIR "${_glew_ENV_ROOT_DIR}")
ENDIF(NOT GLEW_ROOT_DIR AND _glew_ENV_ROOT_DIR)

IF(GLEW_ROOT_DIR)
    SET(_glew_SEARCH_DIRS "${GLEW_ROOT_DIR}"
                                "${GLEW_ROOT_DIR}/include"
                                 ${_glew_SEARCH_DIRS})
ENDIF(GLEW_ROOT_DIR)

FIND_PATH(GLEW_INCLUDE_DIR "GL/glew.h"
    PATHS ${_glew_SEARCH_DIRS})

message(STATUS "glew.h: ${GLEW_INCLUDE_DIR}")

IF (GLEW_INCLUDE_PATH AND GLEW_LIBRARY)
    SET(GLEW_LIBRARIES ${GLEW_LIBRARY})
    SET(GLEW_FOUND "YES")
ENDIF (GLEW_INCLUDE_PATH AND GLEW_LIBRARY)


IF(NOT GLEW_FOUND)
    MESSAGE(STATUS "GLEW not found")
ENDIF(NOT GLEW_FOUND)

IF(GLEW_FOUND)
    SET(GLEW_INCLUDE_DIRS "${GLEW_INCLUDE_DIR}")
    MESSAGE(STATUS "GLEW_INCLUDE_DIR = ${GLEW_INCLUDE_DIR}")
ENDIF(GLEW_FOUND)
