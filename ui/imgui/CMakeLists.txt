find_package(GLFW REQUIRED)
find_package(OpenGL REQUIRED)

add_library(
    SynthImgui
    main
    ui
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/imgui_impl_glfw
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
    ${GLFW_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(
    SynthImgui
    PUBLIC
    SynthCore
    SynthAlsa
    ${GLFW_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
