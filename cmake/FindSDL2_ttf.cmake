
# Sets the following variables

# SDL2_TTF_LIBRARY, the name of the library to link against
# SDL2_TTF_FOUND, if false, do not try to link to SDL2
# SDL2_TTF_INCLUDE_DIR, where to find SDL.h



SET(SDL2_TTF_SEARCH_DIRS
	"./libs/SDL2_ttf"
	"${CMAKE_CURRENT_SOURCE_DIR}/libs/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/libs/SDL2_ttf"
	"/usr/include"
	"/usr"
	"/usr/local/include"
	"/opt"
	"/Library/Frameworks"
	"~/Library/Frameworks"
	)

# check environment variable
SET(_SDL2_TTF_ENV_ROOT_DIR "$ENV{SDL2_TTF_ROOT_DIR}")

# set SDL2 ROOT if needed
IF(NOT SDL2_TTF_ROOT_DIR AND _SDL2_TTF_ENV_ROOT_DIR)
    SET(SDL2_TTF_ROOT_DIR "${_SDL2_TTF_ENV_ROOT_DIR}")
ENDIF(NOT SDL2_TTF_ROOT_DIR AND _SDL2_TTF_ENV_ROOT_DIR)

IF(SDL2_TTF_ROOT_DIR)
    SET(_SDL2_TTF_HEADER_SEARCH_DIRS "${SDL2_TTF_ROOT_DIR}"
                                "${SDL2_TTF_ROOT_DIR}"
                                 ${SDL2_TTF_SEARCH_DIRS})
ENDIF(SDL2_TTF_ROOT_DIR)



FIND_PATH(SDL2_TTF_INCLUDE_DIR
		SDL_ttf.h
		SDL2/SDL_ttf.h
		${SDL2_TTF_SEARCH_DIRS}/include 
		DOC "SDL2_ttf include directory"
)

FIND_LIBRARY(SDL2_TTF_LIBRARY
	NAMES	SDL2 SDL2
	PATHS	${SDL2_TTF_SEARCH_DIRS}
	PATH_SUFFIXES
		lib
		lib64
		lib/x86
		lib/x64
	DOC "SDL2_ttf library"
)


IF (SDL2_TTF_INCLUDE_DIR AND SDL2_TTF_LIBRARY )
	SET(SDL2_TTF_FOUND TRUE )
	MESSAGE(STATUS "SDL2_TTF_INCLUDE_DIR = ${SDL2_TTF_INCLUDE_DIR}")
ELSE ( SDL2_TTF_INCLUDE_DIR AND SDL2_TTF_LIBRARY )
	SET( SDL2_TTF_FOUND FALSE )
	MESSAGE(STATUS "SDL2_ttf not found")
ENDIF ( SDL2_TTF_INCLUDE_DIR AND SDL2_TTF_LIBRARY )