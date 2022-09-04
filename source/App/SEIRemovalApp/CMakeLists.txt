# executable
set( EXE_NAME SEIRemovalApp )

# get source files
file( GLOB SRC_FILES "*.cpp" )

# get include files
file( GLOB INC_FILES "*.h" )

# get additional libs for gcc on Ubuntu systems
if( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
  if( CMAKE_CXX_COMPILER_ID STREQUAL "GNU" )
    if( USE_ADDRESS_SANITIZER )
      set( ADDITIONAL_LIBS asan )
    endif()
  endif()
endif()

# NATVIS files for Visual Studio
if( MSVC )
  file( GLOB NATVIS_FILES "../../VisualStudio/*.natvis" )
endif()

# add executable
add_executable( ${EXE_NAME} ${SRC_FILES} ${INC_FILES} )

# include the output directory, where the svnrevision.h file is generated
include_directories(${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries( ${EXE_NAME} TLibCommon TLibDecoder Utilities Threads::Threads ${ADDITIONAL_LIBS} )

# set the folder where to place the projects
set_target_properties( ${EXE_NAME}  PROPERTIES FOLDER app LINKER_LANGUAGE CXX )
