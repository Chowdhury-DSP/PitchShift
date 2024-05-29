#pragma once

#include <pch.h>

struct PitchShiftParams : chowdsp::ParamHolder
{
    PitchShiftParams()
    {
        add(pitch_shift_amount, pitch_shift_on_off);
    }

    chowdsp::FloatParameter::Ptr pitch_shift_amount {
        juce::ParameterID { "shift_semitones", 1},
        "Pitch Shift Amount",
        juce::NormalisableRange (-12.0f, 12.0f, 1.0f),
        0.0f,
        &chowdsp::ParamUtils::floatValToString,
        &chowdsp::ParamUtils::stringToFloatVal
    };

    chowdsp::BoolParameter::Ptr pitch_shift_on_off {
        juce::ParameterID { "pitch_shift_on_off", 1},
        "Pitch Shift On/Off",
        false,
    };
};

class PitchShift : public chowdsp::PluginBase<chowdsp::PluginStateImpl<PitchShiftParams>>
{
public:
    PitchShift();

    void prepareToPlay (double sample_rate, int samples_per_block) override;
    void releaseResources() override {}
    void processAudioBlock (juce::AudioBuffer<float>& buffer) override;

    juce::AudioProcessorEditor* createEditor() override;

private:

    Bungee::Request request {};
    std::optional<Bungee::Stretcher<Bungee::Basic>> bungee;
    std::optional<Bungee::Push::InputBuffer> bungee_input_buffer;
    chowdsp::SmoothedBufferValue<float, juce::ValueSmoothingTypes::Linear> smoothed_pitch;

    int push_count = 0;
    int pull_count = 0;

    chowdsp::Buffer<float> overflow_buffer;
    int overflow_count = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PitchShift)
};