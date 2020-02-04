add_executable(
    SynthImgui
    main
    ui
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/imgui_impl_glfw
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/imgui_impl_opengl3
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_draw
    ${PROJECT_SOURCE_DIR}/vendor/imgui/imgui_widgets
)

target_include_directories(
    SynthImgui
    PUBLIC
    ${PROJECT_SOURCE_DIR}/vendor/imgui/
    ${PROJECT_SOURCE_DIR}/vendor/imgui/examples/
)

target_link_libraries(
    SynthImgui
    PUBLIC
    SynthCore
    SynthAlsa
    glfw
    GLEW
    GL
)
