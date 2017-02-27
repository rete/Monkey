#################################################
# cmake file for building Monkey package
# @author Rémi Eté
# Copyright (c) Rémi Eté
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 FATAL_ERROR )
#################################################


# ----- Project name -----
PROJECT( Monkey )

SET( ${PROJECT_NAME}_VERSION_MAJOR 0 )
SET( ${PROJECT_NAME}_VERSION_MINOR 0 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )


# ----- Require C++11 -----
INCLUDE( CheckCXXCompilerFlag )

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)

IF( COMPILER_SUPPORTS_CXX11 )
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
	MESSAGE( SEND_ERROR "Monkey requires C++11 support. Please upgrade your compiler !" )
ENDIF()


# ----- Dependencies -----
LIST( APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )
INCLUDE( default_settings )

SET( SUPPORTED_FORMATS "MySQL Json Xml Binary Yaml" )
SET( SUPPORTED_FILE_FORMATS "Json Xml Binary Yaml" )
SET( FORMAT_PACKAGES "MySQL JsonCpp TinyXML YamlCpp" )


# ----- Define options -----
OPTION( INSTALL_DOC "Set to OFF to skip build/install Documentation" OFF )

FOREACH( format ${SUPPORTED_FORMATS} )
  OPTION( ${format}_SUPPORT "Whether to build the ${format} support" OFF )
ENDFOREACH()


# ----- Include package properties -----
FOREACH( pkg ${FORMAT_PACKAGES} )

  INCLUDE_DIRECTORIES( ${${pkg}_INCLUDE_DIRS} )
  LINK_LIBRARIES( ${${pkg}_LIBRARIES} )
  ADD_DEFINITIONS ( ${${pkg}_DEFINITIONS} )

  LIST( APPEND ${PROJECT_NAME}_DEPENDS_INCLUDE_DIRS ${${pkg}_INCLUDE_DIRS} )
  LIST( APPEND ${PROJECT_NAME}_DEPENDS_LIBRARY_DIRS ${${pkg}_LIBRARY_DIRS} )
  LIST( APPEND ${PROJECT_NAME}_DEPENDS_LIBRARIES ${${pkg}_LIBRARIES} )

ENDFOREACH()

# ----- Install doc -----
IF( INSTALL_DOC )
    FIND_PACKAGE( Doxygen )

    IF( DOXYGEN_FOUND )
        ADD_SUBDIRECTORY( ./doc )
    ELSE()
        MESSAGE( SEND_ERROR "Could not find doxygen required to build documentation" )
        MESSAGE( "Please install doxygen or set INSTALL_DOC to OFF" )
        MESSAGE( "" )
    ENDIF()
ENDIF()


# ----- generate MonkeyConfig.h -----
CONFIGURE_FILE( "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.h.cmake.in"
    "${PROJECT_SOURCE_DIR}/source/include/${PROJECT_NAME}Config.h" @ONLY )

# ----- Compile library and binaries -----
ADD_SUBDIRECTORY( source )

INSTALL ( DIRECTORY cmake DESTINATION . PATTERN "*.in" EXCLUDE )

# ----- display some variables and write them to cache -----
DISPLAY_STD_VARIABLES()


# ----- generate and install following configuration files -----
GENERATE_PACKAGE_CONFIGURATION_FILES( ${PROJECT_NAME}Config.cmake ${PROJECT_NAME}ConfigVersion.cmake ${PROJECT_NAME}LibDeps.cmake )
