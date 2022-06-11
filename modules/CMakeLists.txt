add_subdirectory(JUCE)
add_subdirectory(chowdsp_utils)

subproject_version(JUCE juce_version)
message(STATUS "VERSION for JUCE: ${juce_version}")
subproject_version(chowdsp_utils chowdsp_version)
message(STATUS "VERSION for chowdsp: ${chowdsp_version}")

juce_add_modules(foleys_gui_magic)

include(cmake/WarningFlags.cmake)
add_library(juce_plugin_modules STATIC)
target_link_libraries(juce_plugin_modules
    PRIVATE
        BinaryData
        juce::juce_audio_utils
        juce::juce_dsp
        foleys_gui_magic
        chowdsp_plugin_base
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        warning_flags
)

target_compile_definitions(juce_plugin_modules
    PUBLIC
        JUCE_DISPLAY_SPLASH_SCREEN=0
        JUCE_REPORT_APP_USAGE=0
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_JACK=1
        JUCE_ALSA=1
        JucePlugin_Manufacturer="${COMPANY_NAME}"
        JucePlugin_VersionString="${CMAKE_PROJECT_VERSION}"
        JucePlugin_Name="${PRODUCT_NAME}"
        JUCE_MODAL_LOOPS_PERMITTED=0
        FOLEYS_SHOW_GUI_EDITOR_PALLETTE=0
        FOLEYS_ENABLE_BINARY_DATA=1
    INTERFACE
        $<TARGET_PROPERTY:juce_plugin_modules,COMPILE_DEFINITIONS>
)

target_include_directories(juce_plugin_modules
    INTERFACE
        $<TARGET_PROPERTY:juce_plugin_modules,INCLUDE_DIRECTORIES>
)

set_target_properties(juce_plugin_modules PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
    VISIBILITY_INLINES_HIDDEN TRUE
    C_VISBILITY_PRESET hidden
    CXX_VISIBILITY_PRESET hidden
)

if(NOT APPLE)
    message(STATUS "Linking with OpenGL")
    target_link_libraries(juce_plugin_modules PRIVATE juce::juce_opengl)
    target_compile_definitions(juce_plugin_modules PUBLIC FOLEYS_ENABLE_OPEN_GL_CONTEXT=1)
endif()
