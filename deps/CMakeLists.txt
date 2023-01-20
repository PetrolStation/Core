# SPIRV-Cross
add_subdirectory(SPIRV-Cross)

#shaderc
set( SHADERC_SKIP_TESTS    ON  CACHE BOOL "Skip building tests"    FORCE )
set( SHADERC_SKIP_EXAMPLES ON  CACHE BOOL "Skip building examples" FORCE )

find_package (Python COMPONENTS Interpreter Development)

execute_process(COMMAND ${Python_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/shaderc/utils/git-sync-deps COMMAND_ECHO STDOUT)

add_subdirectory(shaderc)