# library
set( LIB_NAME HARDWARE )

# get source files
file( GLOB SRC_FILES "*.cpp" )

# get include files
file( GLOB INC_FILES "*.h" )

# NATVIS files for Visual Studio
if( MSVC )
  file( GLOB NATVIS_FILES "../../VisualStudio/*.natvis" )
endif()

set( CONFIG_HW ON CACHE BOOL "Enable Hardware" )
set( CONFIG_HW_DEQUANT ON CACHE BOOL "Enable Hardware Dequant" )

# library
add_library( ${LIB_NAME} STATIC ${SRC_FILES} ${INC_FILES} ${NATVIS_FILES} )

if( CONFIG_HW )
target_compile_definitions( ${LIB_NAME} PUBLIC CONFIG_HW=1)
endif()
if( CONFIG_HW_DEQUANT )
target_compile_definitions( ${LIB_NAME} PUBLIC CONFIG_HW_DEQUANT=1)
endif()

target_include_directories( ${LIB_NAME} PUBLIC . )
target_link_libraries( ${LIB_NAME} TLibCommon Threads::Threads )

# example: place header files in different folders
source_group( "Natvis Files" FILES ${NATVIS_FILES} )

# set the folder where to place the projects
set_target_properties( ${LIB_NAME} PROPERTIES FOLDER lib )
