#######################################################
# cmake file for building Monkey package
# @author Eté Rémi , IPNL
# Copyright (c) CNRS / IPNL
#######################################################

# ----- compile project library -----
INCLUDE_DIRECTORIES( BEFORE include/format )
INCLUDE_DIRECTORIES( BEFORE include )

# require proper c++
ADD_DEFINITIONS( "-pedantic -Wunused-value -O2" )
ADD_DEFINITIONS("-Wno-long-long -Wreturn-type -Werror")

AUX_SOURCE_DIRECTORY( src SRC_FILES )

FOREACH( format ${SUPPORTED_FORMATS} )
  IF( ${${format}_SUPPORT} )
    LIST( APPEND SRC_FILES src/format/${format}Interface.cc )
  ENDIF()
ENDFOREACH()

ADD_SHARED_LIBRARY( ${PROJECT_NAME} ${SRC_FILES} )
INSTALL(
        TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib
)

# ----- file converters binaries -----
INCLUDE( MacroConvertFileExecutable )

# compile converter binary for each supported format
FOREACH( format1 ${SUPPORTED_FORMATS} )
  IF( ${format1}_SUPPORT )
    FOREACH( format2 ${SUPPORTED_FORMATS} )
      IF( ${format2}_SUPPORT )
        IF( NOT ${format1} EQUALS ${format2} )
          CONVERT_FILE_EXECUTABLE( ${format1} ${format2} )
        ENDIF()
      ENDIF()
    ENDFOREACH()
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE( test_bin main/test.cc )
TARGET_LINK_LIBRARIES( test_bin ${PROJECT_NAME} )
INSTALL(
        TARGETS test_bin
        RUNTIME DESTINATION bin/tests
)

INSTALL_DIRECTORY( include/monkey DESTINATION ./include/monkey FILES_MATCHING PATTERN "*.h" )
