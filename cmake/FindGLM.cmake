# Sets the following variables

# GLM_INCLUDE_DIRS - include directories for GLM
# GLM_LIBRARIES - libraries to link against GLM
# GLM_FOUND - true if GLM has been found and can be used

SET(GLM_FOUND "NO")

# default search dirs
SET(_glm_SEARCH_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/glm"
    "/usr/include"
	"/usr"
	"/usr/local/include"
	"/opt"
	"/Library/Frameworks"
	"~/Library/Frameworks"
    )

# check environment variable
SET(_glm_ENV_ROOT_DIR "$ENV{GLM_ROOT_DIR}")

# set GLM ROOT if needed
IF(NOT GLM_ROOT_DIR AND _glm_ENV_ROOT_DIR)
    SET(GLM_ROOT_DIR "${_glm_ENV_ROOT_DIR}")
ENDIF(NOT GLM_ROOT_DIR AND _glm_ENV_ROOT_DIR)

IF(GLM_ROOT_DIR)
    SET(_glm_SEARCH_DIRS "${GLM_ROOT_DIR}"
                                "${GLM_ROOT_DIR}/include"
                                 ${_glm_SEARCH_DIRS})
ENDIF(GLM_ROOT_DIR)

FIND_PATH(GLM_INCLUDE_DIR "glm/glm.hpp"
    PATHS ${_glm_SEARCH_DIRS})

message(STATUS "glm.hpp: ${GLM_INCLUDE_DIR}")

IF (GLM_INCLUDE_PATH AND GLM_LIBRARY)
    SET(GLM_LIBRARIES ${GLM_LIBRARY})
    SET(GLM_FOUND "YES")
ENDIF (GLM_INCLUDE_PATH AND GLM_LIBRARY)

IF(NOT GLM_FOUND)
    MESSAGE(STATUS "GLM not found")
ENDIF(NOT GLM_FOUND)

IF(GLM_FOUND)
    SET(GLM_INCLUDE_DIRS "${GLM_INCLUDE_DIR}")
    MESSAGE(STATUS "GLM_INCLUDE_DIR = ${GLM_INCLUDE_DIR}")
ENDIF(GLM_FOUND)
