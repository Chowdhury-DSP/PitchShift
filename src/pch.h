#pragma once

/**
 * Pre-compiled headers for JUCE plugins
 */

// C++/STL headers here...

// JUCE modules
#include <chowdsp_gui/chowdsp_gui.h>
#include <chowdsp_plugin_base/chowdsp_plugin_base.h>
#include <chowdsp_dsp_data_structures/chowdsp_dsp_data_structures.h>
#include <chowdsp_buffers/chowdsp_buffers.h>

// third-party includes
JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE ("-Wshadow-field-in-constructor")
#include <bungee/Bungee.h>
#include <bungee/Push.h>
JUCE_END_IGNORE_WARNINGS_GCC_LIKE

// Any other widely used headers that don't change...
