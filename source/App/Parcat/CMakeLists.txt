# executable
set( EXE_NAME parcat )

# get source files
file( GLOB SRC_FILES "*.cpp" )

# get include files
file( GLOB INC_FILES "*.h" )

# add executable
add_executable( ${EXE_NAME} ${SRC_FILES} ${INC_FILES} )

target_link_libraries( ${EXE_NAME} Threads::Threads ${ADDITIONAL_LIBS} )

# include the output directory, where the svnrevision.h file is generated
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# set the folder where to place the projects
set_target_properties( ${EXE_NAME}  PROPERTIES FOLDER app LINKER_LANGUAGE CXX )

