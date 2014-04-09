#macro that finds all subdirectories
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
        SET(dirlist ${dirlist} ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

#get all subdirectories
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

#destination for modules
SET(dest /tmp/GrizzlyManager/data/modules)

#for each library folder
FOREACH(subdir ${SUBDIRS})

	#all .cpp files in subdirectory
	FILE(GLOB module_src
    	   "${subdir}/*.cpp"
	)

	#compile library named as folder
	ADD_LIBRARY(${subdir} MODULE ${module_src})

	#copy libraries to destination
	INSTALL(FILES ${CMAKE_BINARY_DIR}/modules/lib${subdir}.so DESTINATION ${dest})

	#directory MUST have name "lib<nameOfLibraryDirectory>"
	IF(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${subdir}/lib${subdir})
		#copy folder to destination
		INSTALL(DIRECTORY ${subdir}/lib${subdir} 
			DESTINATION ${dest} 
			DESTINATION ${CMAKE_BINARY_DIR}/modules/
		)
	ENDIF()

ENDFOREACH()

