cmake_minimum_required(VERSION 3.20)
project(DestroyAllHumansRecomp C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX _CRT_SECURE_NO_WARNINGS)

option(DAH_INTERNAL_BUILD "Name the executable as a hidden-test build" OFF)
if(DAH_INTERNAL_BUILD)
    set(DAH_EXECUTABLE_NAME "dah_recomp_internal")
else()
    set(DAH_EXECUTABLE_NAME "dah_recomp_working")
endif()

set(XBOXRECOMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/xboxrecomp")
add_subdirectory("${XBOXRECOMP_DIR}" "${CMAKE_BINARY_DIR}/xboxrecomp")

file(GLOB RECOMP_SOURCES CONFIGURE_DEPENDS "src/recomp/gen/*.c")
add_executable(DestroyAllHumans WIN32
    src/main.c
    src/dah_crashlog.c
    src/dah_frame.c
    src/dah_renderdoc.c
    src/recomp_manual.c
    ${RECOMP_SOURCES}
)
set_target_properties(DestroyAllHumans PROPERTIES OUTPUT_NAME "${DAH_EXECUTABLE_NAME}")

target_include_directories(DestroyAllHumans PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/recomp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/recomp/gen"
    "${XBOXRECOMP_DIR}/templates/runtime"
    "${XBOXRECOMP_DIR}/include"
)
target_link_libraries(DestroyAllHumans PRIVATE xboxrecomp d3d11 dxgi dxguid xinput winmm dbghelp)

add_executable(dah_keyboard_mapping_test tools/test_keyboard_mapping.c)
target_include_directories(dah_keyboard_mapping_test PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
add_executable(dah_stick_conditioner_test
    "${XBOXRECOMP_DIR}/tools/input/test_stick_conditioner.c"
    "${XBOXRECOMP_DIR}/src/input/stick_conditioner.c"
)
target_include_directories(dah_stick_conditioner_test PRIVATE
    "${XBOXRECOMP_DIR}/src/input"
)
if(NOT MSVC)
    target_link_libraries(dah_stick_conditioner_test PRIVATE m)
endif()
add_executable(dah_xinput_probe tools/probe_xinput.c)
target_link_libraries(dah_xinput_probe PRIVATE xinput)
add_executable(dah_rockwell_vehicle_vsh_dump tools/dump_rockwell_vehicle_vsh.c)
target_link_libraries(dah_rockwell_vehicle_vsh_dump PRIVATE xbox_d3d8)
enable_testing()
add_test(NAME dah_keyboard_mapping COMMAND dah_keyboard_mapping_test)
add_test(NAME dah_stick_conditioner COMMAND dah_stick_conditioner_test)

if(MSVC)
    target_compile_options(DestroyAllHumans PRIVATE /bigobj /W0 /MP)
    target_link_options(DestroyAllHumans PRIVATE /LARGEADDRESSAWARE /MAP:DestroyAllHumans.map)
endif()

add_custom_command(TARGET DestroyAllHumans POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../default.xbe"
        "$<TARGET_FILE_DIR:DestroyAllHumans>/default.xbe"
)
