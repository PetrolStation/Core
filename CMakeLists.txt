cmake_minimum_required(VERSION 3.16)

PA_NEW(Core)

PA_INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/entt/single_include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/shaderc/libshaderc/include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/SPIRV-Cross
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/stb
)

PA_LINK_LIBRARIES(
    PRIVATE common
    PRIVATE shaderc
    PRIVATE spirv-cross-cpp
)

File(GLOB_RECURSE SOURCE_FILES src/*.cpp )
File(GLOB_RECURSE HEADER_FILES src/*.h   )

pa_add_source_files(
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

add_subdirectory(deps)