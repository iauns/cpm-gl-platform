cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)

#-----------------------------------------------------------------------
# CPM configuration
#-----------------------------------------------------------------------
set(CPM_MODULE_NAME "gl_platform")
set(CPM_LIB_TARGET_NAME ${CPM_MODULE_NAME})

if ((DEFINED CPM_DIR) AND (DEFINED CPM_UNIQUE_ID) AND (DEFINED CPM_TARGET_NAME))
  set(CPM_LIB_TARGET_NAME ${CPM_TARGET_NAME})
  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CPM_DIR})
  include(CPM)
else()
  set (CPM_DIR "${CMAKE_CURRENT_BINARY_DIR}/cpm-packages" CACHE TYPE STRING)
  find_package(Git)
  if(NOT GIT_FOUND)
    message(FATAL_ERROR "CPM requires Git.")
  endif()
  if (NOT EXISTS ${CPM_DIR}/CPM.cmake)
    message(STATUS "Cloning repo (https://github.com/iauns/cpm)")
    execute_process(
      COMMAND "${GIT_EXECUTABLE}" clone https://github.com/iauns/cpm ${CPM_DIR}
      RESULT_VARIABLE error_code
      OUTPUT_QUIET ERROR_QUIET)
    if(error_code)
      message(FATAL_ERROR "CPM failed to get the hash for HEAD")
    endif()
  endif()
  include(${CPM_DIR}/CPM.cmake)
endif()

if (WIN32)
  # Include GLEW cpm module.
  CPM_AddModule("glew"
    GIT_REPOSITORY "https://github.com/iauns/cpm-glew"
    GIT_TAG "1.0.1"
    EXPORT_MODULE TRUE)
endif()

# This call will ensure all include directories and definitions are present
# in the target. These correspond to the modules that we added above.
CPM_InitModule(${CPM_MODULE_NAME})

# Enable debug macros only if we are debugging the program.
if (CMAKE_BUILD_TYPE MATCHES DEBUG) 
  CPM_ExportAdditionalDefinition("-DIAUNS_GLDEBUG_DEBUG")
endif (CMAKE_BUILD_TYPE MATCHES DEBUG) 

if ((DEFINED GL_PLATFORM_NO_DEBUGGING) AND (GL_PLATFORM_NO_DEBUGGING))
  CPM_ExportAdditionalDefinition("-DGL_PLATFORM_NO_DEBUGGING")
endif()

#-----------------------------------------------------------------------
# Source
#-----------------------------------------------------------------------

# Globbing has some downsides, but the advantages outweigh the
# disadvantages.
file (GLOB Sources
  "gl-platform/*.cpp"
  "gl-platform/*.hpp"
  )

#-----------------------------------------------------------------------
# Library setup
#-----------------------------------------------------------------------

# Build the library.
add_library(${CPM_LIB_TARGET_NAME} ${Sources})
if (NOT EMSCRIPTEN AND CPM_LIBRARIES)
  target_link_libraries(${CPM_LIB_TARGET_NAME} ${CPM_LIBRARIES})
endif()

