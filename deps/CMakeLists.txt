# SPIRV-Cross
add_subdirectory(SPIRV-Cross)

set( SPIRV_CROSS_CLI OFF  CACHE BOOL "Skip building examples" FORCE )
set( SPIRV_CROSS_ENABLE_TESTS OFF  CACHE BOOL "Skip building examples" FORCE )
set(SPIRV_CROSS_SHARED OFF CACHE BOOL "Build the C API as a single shared library." FORCE)
set(SPIRV_CROSS_ENABLE_UTIL OFF CACHE BOOL "Enable util module support." FORCE)

#shaderc
set( SHADERC_SKIP_TESTS    ON  CACHE BOOL "Skip building tests"    FORCE )
set( SHADERC_SKIP_EXAMPLES ON  CACHE BOOL "Skip building examples" FORCE )

find_package (Python COMPONENTS Interpreter Development)

execute_process(COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/shaderc/utils/git-sync-deps COMMAND_ECHO STDOUT)

add_subdirectory(shaderc)
