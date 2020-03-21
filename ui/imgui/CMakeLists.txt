find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(
    SynthImgui
    SHARED
    main
    ui
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/imgui_impl_sdl
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/imgui_impl_opengl3
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/libs/gl3w/GL/gl3w
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets
)

add_compile_definitions(
    SynthImgui
    IMGUI_IMPL_OPENGL_LOADER_GL3W
)

target_include_directories(
    SynthImgui
    PUBLIC
    ${PROJECT_SOURCE_DIR}/vendor/imgui/
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/libs/gl3w/
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(
    SynthImgui
    PUBLIC
    SynthCore
    SynthAlsa
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
