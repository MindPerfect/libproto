# Top level CMake project
cmake_minimum_required(VERSION 3.15)
project(lss LANGUAGES C CXX VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

# Enforce out-of-source build, fail otherwise
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES  ON)

# Make the default build type as Debug in single-configuration generators
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()



# Commonly used locations by default
set(_opt /opt)
set(_opt_MP ${_opt}/MP)
set(_opt_MP_ext ${_opt_MP}/ext)
set(_opt_local ${_opt}/local)

# Project source directory
set(PrjSrc ${CMAKE_SOURCE_DIR}/src)




# Platform defaults and settings
message(STATUS "CMAKE_HOST_SYSTEM_NAME: ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "CMAKE_HOST_SYSTEM_VERSION: ${CMAKE_HOST_SYSTEM_VERSION}")

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux") 
  message(STATUS "Linux detected.")

  if(${CMAKE_HOST_SYSTEM_VERSION} MATCHES "WSL")
    #TODO
	set(GTest_DIR ${_opt_local}/lib/cmake/GTest)
    set(absl_DIR ${_opt_local}/lib/cmake/absl)
  else()  
    set(GTest_DIR ${_opt_local}/lib/cmake/GTest)
    set(absl_DIR ${_opt_local}/abseil/lib/cmake/absl)
    set(benchmark_DIR ${_opt_local}/benchmark/lib/cmake/benchmark)
  endif()


  include_directories(${_opt_local}/include)
  link_directories(${_opt_local}/lib)

  # Provide hints to package locations
  set(GTest_DIR ${_opt_local}/lib/cmake/GTest)

elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
  message(STATUS "Windows detected.")
  # Override default locations
  set(_opt C:/opt)
  set(_opt_MP ${_opt}/MP)
  set(_opt_MP_ext ${_opt_MP}/ext)
  set(_opt_local ${_opt}/local)

  # Provide hints to package locations
  set(GTest_DIR ${_opt_local}/gtest/lib/cmake/GTest)
  #-set(spdlog_DIR ${_opt_local}/spdlog/lib/cmake/spdlog)
  set(absl_DIR ${_opt_local}/abseil/lib/cmake/absl)
  #-set(TBB_DIR ${_opt_local}/oneapi-tbb-2021.10.0/lib/cmake/tbb)
  #-set(CLI11_DIR ${_opt_local}/CLI11/share/cmake/CLI11)
  #gperftools
  #benchmark
  set(benchmark_DIR ${_opt_local}/benchmark/lib/cmake/benchmark)

elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin") 
  message(FATAL_ERROR "MacOS is not supported yet")  

else()
  message(WARNING "Unknown platform")

endif() # Platform settings


# Compiler settings and defaults:
message(STATUS "CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")



# Identify compiler:
# https://stackoverflow.com/questions/10046114/in-cmake-how-can-i-test-if-the-compiler-is-clang
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using Gcc
  # lots of warnings and all warnings as errors
  #add_compile_options(-Wall -Wextra -pedantic -Werror)
  #
  # Add following for lttng tracing:
  #add_compile_options(-finstrument-functions)
  #
  # Add following for coverage support
  #add_compile_options(-O0 --coverage)
  #add_link_options(--coverage)
  #
  # gperftools support (Only on Linux)
  #link_libraries(-lprofiler -ltcmalloc) #Doesn't work why?
  #TODO: Inestigate later and install
  #link_libraries(-ltcmalloc_and_profiler)
  # HEAPCHECK=normal ./base_test
  # CPUPROFILE=tst.prof ./base_test

  # add variant optoins
  option(COV "Coverage" OFF)
  option(PROF "Profiler" OFF)
  option(ASAN "Sanitizer-Address" OFF)
  option(TSAN "Sanitizer-Thread" OFF)

  if(COV)
  add_compile_options(-O0 --coverage)
  add_link_options(--coverage)
  endif()

  if(PROF)
  add_compile_options(-pg)
  add_link_options(-pg)
  endif()

  if(ASAN)
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
  endif()

  if(TSAN)
  add_compile_options(-fsanitize=thread)
  add_link_options(-fsanitize=thread)
  endif()



elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
  # warning level 4 and all warnings as errors
  #add_compile_options(/W4 /WX)
  # Concurrent compile support (maybe /FS also?)
  add_compile_options(/MP)


  set(pdb_out ${CMAKE_CURRENT_BINARY_DIR}/pdb)
  set(CMAKE_PDB_OUTPUT_DIRECTORY ${pdb_out})
  set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY ${pdb_out})


  # end of MSVC
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
 # using Clang/LLVM
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
 # using Intel C++
else()
  message(WARNING "Unknown compiler!") 
endif()


# Adjust CMake Module Path list
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmk")


#
# Needed packages
#
# Google Libraries
find_package(GTest CONFIG REQUIRED) # Gtest/mock
find_package(absl CONFIG REQUIRED) # Abseil
#-find_package(benchmark CONFIG REQUIRED) # Benchmark
# Third party libraries
#-find_package(TBB CONFIG REQUIRED) # Threading Building Blocks
#-find_package(CLI11 CONFIG REQUIRED) # CLI11
# SpdLog
#-find_package(spdlog CONFIG REQUIRED)

# Doxygen for documentation
find_package(Doxygen REQUIRED dot)


if ( DOXYGEN_FOUND )

set( DOXYGEN_OUTPUT_DIRECTORY doc )
set( DOXYGEN_COLLABORATION_GRAPH YES )
set( DOXYGEN_EXTRACT_ALL YES )
set( DOXYGEN_CLASS_DIAGRAMS YES )
set( DOXYGEN_HIDE_UNDOC_RELATIONS NO )
set( DOXYGEN_HAVE_DOT YES )
set( DOXYGEN_CLASS_GRAPH YES )
set( DOXYGEN_CALL_GRAPH YES )
set( DOXYGEN_CALLER_GRAPH YES )
set( DOXYGEN_COLLABORATION_GRAPH YES )
set( DOXYGEN_BUILTIN_STL_SUPPORT YES )
set( DOXYGEN_EXTRACT_PRIVATE YES )
set( DOXYGEN_EXTRACT_PACKAGE YES )
set( DOXYGEN_EXTRACT_STATIC YES )
set( DOXYGEN_EXTRACT_LOCALMETHODS YES )
set( DOXYGEN_UML_LOOK YES )
set( DOXYGEN_UML_LIMIT_NUM_FIELDS 50 )
set( DOXYGEN_TEMPLATE_RELATIONS YES )
set( DOXYGEN_DOT_GRAPH_MAX_NODES 100 )
set( DOXYGEN_MAX_DOT_GRAPH_DEPTH 0 )
set( DOXYGEN_DOT_TRANSPARENT YES )

#-doxygen_add_docs( doxygen ${RPP_PROJECT_SOURCE_DIR} )
doxygen_add_docs(
    doxygen
    ${PrjSrc}
    COMMENT "Generate html pages"
)

else()
message( "Doxygen need to be installed to generate the doxygen documentation" )
endif()



# Define sources and targets
add_subdirectory(src)


# Enable testing for current directory and below.
enable_testing()

# Define test targets
add_subdirectory(tst)

