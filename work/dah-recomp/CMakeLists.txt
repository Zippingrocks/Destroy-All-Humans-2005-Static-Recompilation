cmake_minimum_required(VERSION 3.20)
project(DestroyAllHumansRecomp C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX _CRT_SECURE_NO_WARNINGS)

option(DAH_INTERNAL_BUILD "Name the executable as a hidden-test build" OFF)
option(DAH_REPORTER_BUILD "Build the opt-in Debug-Reporter edition" OFF)
if(DAH_INTERNAL_BUILD)
    set(DAH_EXECUTABLE_NAME "dah_recomp_internal")
elseif(DAH_REPORTER_BUILD)
    set(DAH_EXECUTABLE_NAME "dah_recomp_debug_reporter")
else()
    set(DAH_EXECUTABLE_NAME "dah_recomp_working")
endif()

set(XBOXRECOMP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../third_party/xboxrecomp")
add_subdirectory("${XBOXRECOMP_DIR}" "${CMAKE_BINARY_DIR}/xboxrecomp")

file(GLOB RECOMP_SOURCES CONFIGURE_DEPENDS "src/recomp/gen/*.c")
add_executable(DestroyAllHumans WIN32
    src/main.c
    src/dah_crashlog.c
    src/dah_event_trace.c
    src/dah_run_evidence.c
    src/dah_frame.c
    src/dah_renderdoc.c
    src/recomp_manual.c
    ${RECOMP_SOURCES}
)
if(DAH_REPORTER_BUILD)
    target_sources(DestroyAllHumans PRIVATE src/dah_public_report.c)
    target_compile_definitions(DestroyAllHumans PRIVATE DAH_REPORTER_BUILD=1)
    target_link_libraries(DestroyAllHumans PRIVATE bcrypt shell32)
endif()

if(WIN32)
    find_package(Python3 REQUIRED COMPONENTS Interpreter)
    set(DAH_RETAIL_XBE "${CMAKE_CURRENT_SOURCE_DIR}/../default.xbe")
    set(DAH_GENERATED_RESOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_resources")
    set(DAH_ICON_ICO "${DAH_GENERATED_RESOURCE_DIR}/dah1_retail_title.ico")
    set(DAH_ICON_RC "${DAH_GENERATED_RESOURCE_DIR}/dah_icon.rc")
    file(MAKE_DIRECTORY "${DAH_GENERATED_RESOURCE_DIR}")
    add_custom_command(
        OUTPUT "${DAH_ICON_ICO}"
        COMMAND "${Python3_EXECUTABLE}"
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_xbe_title_icon.py"
            "${DAH_RETAIL_XBE}"
            "${DAH_ICON_ICO}"
        DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/extract_xbe_title_icon.py"
            "${DAH_RETAIL_XBE}"
        COMMENT "Extracting the retail DAH title icon from default.xbe"
        VERBATIM
    )
    file(TO_CMAKE_PATH "${DAH_ICON_ICO}" DAH_ICON_ICO_RC)
    configure_file(src/dah_icon.rc.in "${DAH_ICON_RC}" @ONLY)
    set_source_files_properties("${DAH_ICON_RC}" PROPERTIES
        OBJECT_DEPENDS "${DAH_ICON_ICO}"
    )
    target_sources(DestroyAllHumans PRIVATE "${DAH_ICON_RC}")
endif()
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
add_executable(dah_player_recording_test tools/test_player_recording.c)
target_include_directories(dah_player_recording_test PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
enable_testing()
add_test(NAME dah_keyboard_mapping COMMAND dah_keyboard_mapping_test)
add_test(NAME dah_stick_conditioner COMMAND dah_stick_conditioner_test)
add_test(NAME dah_player_recording COMMAND dah_player_recording_test)

if(MSVC)
    target_compile_options(DestroyAllHumans PRIVATE /bigobj /W0 /MP)
    target_link_options(DestroyAllHumans PRIVATE /LARGEADDRESSAWARE /MAP:DestroyAllHumans.map)
endif()

add_custom_command(TARGET DestroyAllHumans POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/../default.xbe"
        "$<TARGET_FILE_DIR:DestroyAllHumans>/default.xbe"
)
