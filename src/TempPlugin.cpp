#include "TempPlugin.h"

TempPlugin::TempPlugin()
{
}

void TempPlugin::addParameters (Parameters& params)
{
}

void TempPlugin::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void TempPlugin::processAudioBlock (AudioBuffer<float>& buffer)
{
}

AudioProcessorEditor* TempPlugin::createEditor()
{
    return new GenericAudioProcessorEditor { *this };
}

// This creates new instances of the plugin
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TempPlugin();
}
