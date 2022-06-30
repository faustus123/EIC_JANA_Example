
cmake_minimum_required(VERSION 3.9)
project(EICRawData_project)

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 14)
endif()
set(CMAKE_POSITION_INDEPENDENT_CODE ON)   # Enable -fPIC for all targets

# Expose custom cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

# Set install directory to $JANA_HOME
set(CMAKE_INSTALL_PREFIX $ENV{JANA_HOME} CACHE PATH "magic incantation" FORCE)

# Find dependencies
find_package(JANA REQUIRED)


find_package(ROOT REQUIRED)
add_compile_definitions(HAVE_ROOT)

# According to the internet, CMake authors discourage the use
# of GLOB for identifying source files. IMHO, this is due to
# the flawed use of cache files in CMake itself. Here, GLOB
# is used as the default. What this means is you can add source
# files and re-run cmake (after clearing the cache file) and
# they will be found without needing to modify this file.
# You also have the option of switching the following to "false"
# and managing the source file list manually the way they recommend.
if(true)
  # Automatically determine source file list.
  file(GLOB EICRawData_PLUGIN_SOURCES *.cpp *.cc *.c  *.hpp *.hh *.h)
else()
  # Manually manage source file list (not used. for demonstration)
  set (EICRawData_PLUGIN_SOURCES
		EASIC_hit.h
		EICRawData.cc
		ERawDataSource.h
		JFactory_EEndCapDigiHit.h
		EEndCapDigiHit.h
		ERawDataSource.cc
		JFactory_EEndCapDigiHit.cc
  )
endif()

# ROOT TObject dictionaries are not strictly required unless you
# want to use features of the inspection tools with JANA.
# (See $JANA_HOME/src/plugins/JTestRoot/CMakeLists.txt for details.)
set(my_pcms)
set( TOBJECT_CLASSES EEndCapDigiHit ) # List of TObject based classes to create dictionaries for
foreach( CLASS ${TOBJECT_CLASSES} )
	ROOT_GENERATE_DICTIONARY(G__${CLASS} ${CLASS}.h)
	list(APPEND my_pcms ${CMAKE_CURRENT_BINARY_DIR}/lib${CLASS}_rdict.pcm )
	list(APPEND EICRawData_PLUGIN_SOURCES G__${CLASS}.cxx )
endforeach()


add_library(EICRawData_plugin SHARED ${EICRawData_PLUGIN_SOURCES})

target_include_directories(EICRawData_plugin PUBLIC ${CMAKE_SOURCE_DIR} ${JANA_INCLUDE_DIR} ${ROOT_INCLUDE_DIRS})
target_link_libraries(EICRawData_plugin ${JANA_LIB} ${ROOT_LIBRARIES})
set_target_properties(EICRawData_plugin PROPERTIES PREFIX "" OUTPUT_NAME "EICRawData" SUFFIX ".so")

install(TARGETS EICRawData_plugin DESTINATION plugins)

file(GLOB my_headers "*.h*")
install(FILES ${my_headers} DESTINATION include/EICRawData)

# For root dictionaries
message(STATUS "Installing ROOT PCM files: ${my_pcms}")
install(FILES ${my_pcms} DESTINATION plugins)

