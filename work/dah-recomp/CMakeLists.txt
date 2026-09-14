cmake_minimum_required(VERSION 3.20)
project(DestroyAllHumansRecomp C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX _CRT_SECURE_NO_WARNINGS)

set(XBOXRECOMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../Repos/xboxrecomp-main")
add_subdirectory("${XBOXRECOMP_DIR}" "${CMAKE_BINARY_DIR}/xboxrecomp")

file(GLOB RECOMP_SOURCES CONFIGURE_DEPENDS "src/recomp/gen/*.c")
add_executable(DestroyAllHumans WIN32
    src/main.c
    src/dah_frame.c
    src/recomp_manual.c
    ${RECOMP_SOURCES}
)

target_include_directories(DestroyAllHumans PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/recomp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/recomp/gen"
    "${XBOXRECOMP_DIR}/templates/runtime"
    "${XBOXRECOMP_DIR}/include"
)
target_link_libraries(DestroyAllHumans PRIVATE xboxrecomp d3d11 dxgi dxguid xinput winmm)

if(MSVC)
    target_compile_options(DestroyAllHumans PRIVATE /bigobj /W0 /MP)
    target_link_options(DestroyAllHumans PRIVATE /LARGEADDRESSAWARE /MAP:DestroyAllHumans.map)
endif()

add_custom_command(TARGET DestroyAllHumans POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../default.xbe"
        "$<TARGET_FILE_DIR:DestroyAllHumans>/default.xbe"
)
