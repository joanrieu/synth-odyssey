cmake_minimum_required(VERSION 3.16)
project(SynthOdyssey)

set(EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)

if (EXISTS ${EMPTY_FILE})
    set(HAS_EMPTY_FILE 1)
else()
    set(HAS_EMPTY_FILE 0)
endif()

file(
    GENERATE OUTPUT ${EMPTY_FILE}
    CONTENT ""
    CONDITION $<NOT:${HAS_EMPTY_FILE}>
)

add_subdirectory(core)
add_subdirectory(drivers/alsa)
add_subdirectory(ui/imgui)
add_subdirectory(ui/qt)

add_executable(SynthAlsaImgui ${EMPTY_FILE})
target_link_libraries(SynthAlsaImgui SynthAlsa SynthImgui)

add_executable(SynthAlsaQt ${EMPTY_FILE})
target_link_libraries(SynthAlsaQt SynthAlsa SynthQt)
