CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (GrizzlyManager)

SET(dest /tmp/GrizzlyManager)
SET(libDest ${dest}/data/modules)
SET(progDest ${dest}/Grizzly)

#compile shared libraries
ADD_SUBDIRECTORY(modules)


FILE(GLOB GrizzlyManager_src
    "tools/*.cpp"
    "webtools/*.cpp"
    "mongoose/*.c"
    "*.cpp"
)


#compile main program
ADD_EXECUTABLE(GrizzlyManager ${GrizzlyManager_src})
TARGET_LINK_LIBRARIES(GrizzlyManager dl pthread)


#copy main program to destination
INSTALL(PROGRAMS ../GrizzlyManager DESTINATION ${progDest})

#copy data folder to destination
INSTALL(DIRECTORY ../data DESTINATION ${dest})

ADD_CUSTOM_TARGET(clean
	COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
	COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
	COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/install_manifest.txt
	
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/modules
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
)

