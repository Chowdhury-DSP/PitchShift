include(SourceFileGroup)

setup_source_group(PitchShift PLUGIN_SRCS SOURCES
PitchShift.cpp
)

file(GLOB_RECURSE juce_module_sources CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/../modules/JUCE/modules/juce_*/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../modules/JUCE/modules/juce_*/*.mm
    ${CMAKE_CURRENT_SOURCE_DIR}/../modules/chowdsp_utils/modules/*/chowdsp_*/*.cpp
)
set_source_files_properties(${juce_module_sources}
    TARGET_DIRECTORY PitchShift
    PROPERTIES SKIP_PRECOMPILE_HEADERS TRUE SKIP_UNITY_BUILD_INCLUSION TRUE
)
set_target_properties(PitchShift PROPERTIES
    UNITY_BUILD ON
    UNITY_BUILD_MODE GROUP
    UNITY_BUILD_BATCH_SIZE 8
)
target_precompile_headers(PitchShift PRIVATE pch.h)

#-----------------------------------------------
#
#include(SourceFileGroup)
#
#setup_source_group(SourceTone PLUGIN_SRCS
#SOURCES
#SourceTone.cpp
#dsp/Dry_Wet_Processor.cpp
#dsp/Gain_Processor.cpp
#dsp/Source_Tone_Processor.cpp
#dsp/context/Context.cpp
#dsp/filter/Filter_Processor.cpp
#dsp/fuzz/ResampledRNNAccelerated.cpp
#dsp/fuzz/Fuzz_Processor.cpp
#dsp/pitch_shifter/Pitch_Shift_Processor.cpp
#)
#
## AVX/SSE lib for SIMD-accelerated DSP
#include(${CMAKE_CURRENT_SOURCE_DIR}/../modules/cmake/RuntimeSIMDLib.cmake)
#make_lib_simd_runtime(dsp_accelerated
#SOURCES
#dsp/fuzz/RNN_Accelerated.h
#dsp/fuzz/RNN_Accelerated.cpp
#)
#foreach (target IN ITEMS dsp_accelerated_sse_or_arm dsp_accelerated_avx)
#target_link_libraries(${target}
#PRIVATE
#math_approx
#juce::juce_recommended_config_flags
#juce::juce_recommended_lto_flags
#warning_flags
#)
#target_include_directories(${target}
#PRIVATE
#${CMAKE_CURRENT_SOURCE_DIR}/../modules/RTNeural
#${CMAKE_CURRENT_SOURCE_DIR}/../modules/RTNeural/modules/xsimd/include
#)
#target_compile_definitions(${target} PRIVATE RTNEURAL_USE_XSIMD=1)
#endforeach()
#target_compile_definitions(dsp_accelerated_sse_or_arm PRIVATE RTNEURAL_DEFAULT_ALIGNMENT=16 RTNEURAL_NAMESPACE=RTNeural_sse_arm)
#target_compile_definitions(dsp_accelerated_avx PRIVATE RTNEURAL_DEFAULT_ALIGNMENT=32 RTNEURAL_NAMESPACE=RTNeural_avx)
#target_link_libraries(SourceTone PRIVATE dsp_accelerated)
#
#file(GLOB_RECURSE juce_module_sources CONFIGURE_DEPENDS
#${CMAKE_CURRENT_SOURCE_DIR}/../modules/JUCE/modules/juce_*/*.cpp
#${CMAKE_CURRENT_SOURCE_DIR}/../modules/JUCE/modules/juce_*/*.mm
#${CMAKE_CURRENT_SOURCE_DIR}/../modules/chowdsp_utils/modules/*/chowdsp_*/*.cpp
#)
#set_source_files_properties(${juce_module_sources}
#TARGET_DIRECTORY SourceTone
#PROPERTIES SKIP_PRECOMPILE_HEADERS TRUE SKIP_UNITY_BUILD_INCLUSION TRUE
#)
#set_target_properties(SourceTone PROPERTIES
#UNITY_BUILD ON
#UNITY_BUILD_MODE GROUP
#UNITY_BUILD_BATCH_SIZE 8
#)
#target_precompile_headers(SourceTone PRIVATE pch.h)
