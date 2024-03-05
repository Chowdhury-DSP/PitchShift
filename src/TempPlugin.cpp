#include "TempPlugin.h"

TempPlugin::TempPlugin() = default;

void TempPlugin::prepareToPlay ([[maybe_unused]] double sample_rate, [[maybe_unused]] int samples_per_block)
{
}

void TempPlugin::processAudioBlock ([[maybe_unused]] juce::AudioBuffer<float>& buffer)
{
}

juce::AudioProcessorEditor* TempPlugin::createEditor()
{
    return new chowdsp::ParametersViewEditor { *this, state, state.params };
}

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TempPlugin();
}
