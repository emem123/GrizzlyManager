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

#copy script to /etc/init.d
INSTALL(PROGRAMS ../grizzlymanagerd DESTINATION /etc/init.d)

#create symbolic links to rcX.d
INSTALL(CODE "execute_process(COMMAND ln -s /etc/init.d/grizzlymanagerd /etc/rc2.d/S80grizzlymanagerd)")
INSTALL(CODE "execute_process(COMMAND ln -s /etc/init.d/grizzlymanagerd /etc/rc6.d/K10grizzlymanagerd)")


ADD_CUSTOM_TARGET(uninstall
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${dest}
	COMMAND ${CMAKE_COMMAND} -E remove /etc/init.d/grizzlymanagerd
	COMMAND ${CMAKE_COMMAND} -E remove /etc/rc2.d/S80grizzlymanagerd
	COMMAND ${CMAKE_COMMAND} -E remove /etc/rc6.d/K10grizzlymanagerd
)

