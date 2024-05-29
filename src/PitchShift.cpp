#include "PitchShift.h"

PitchShift::PitchShift() = default;

void PitchShift::prepareToPlay ([[maybe_unused]] double sample_rate, [[maybe_unused]] int samples_per_block)
{
    int num_channels = getMainBusNumInputChannels();
    bungee.emplace (Bungee::SampleRates {
                        .input = static_cast<int> (sample_rate),
                        .output = static_cast<int> (sample_rate),
                    },
                    num_channels);
    bungee_input_buffer.emplace (std::abs (bungee->maxInputFrameCount()) + static_cast<int> (samples_per_block), num_channels);

    request = {
        .position = 0.0,
        .speed = 1.0,
        .pitch = 2.0,
        .reset = false,
    };

    bungee->preroll (request);
    const auto input_chunk = bungee->specifyGrain (request);
    bungee_input_buffer->grain (input_chunk);

    overflow_buffer.setMaxSize (num_channels, bungee->maxInputFrameCount() + 2 * static_cast<int> (samples_per_block));
    overflow_count = 0;

    smoothed_pitch.setParameterHandle (state.params.pitch_shift_amount.get());
    smoothed_pitch.prepare (sample_rate, samples_per_block);
}

void PitchShift::processAudioBlock ([[maybe_unused]] juce::AudioBuffer<float>& buffer)
{
    if (!state.params.pitch_shift_on_off->get())
    {
        // @TODO: we might need to smooth this, or reset Bungee's state in some way...
        return;
    }

    const auto num_samples = buffer.getNumSamples();

    smoothed_pitch.process (num_samples); //update utils and add Context with arena?
    request.pitch = std::exp2 (smoothed_pitch.getCurrentValue() / 12.0f);

    for (const auto& [ch, data] : chowdsp::buffer_iters::channels (buffer))
        std::copy (data.begin(), data.end(), bungee_input_buffer->inputData() + ch * bungee_input_buffer->stride());

    bungee_input_buffer->deliver (num_samples);
    push_count += num_samples;

    buffer.clear();

    int samples_written = 0;
    if (overflow_count > 0)
    {
        const auto overflow_samples_to_copy = std::min (overflow_count, num_samples);
        chowdsp::BufferMath::copyBufferData (overflow_buffer, buffer, 0, 0, overflow_samples_to_copy);
        overflow_count -= overflow_samples_to_copy;
        samples_written += overflow_samples_to_copy;

        if (overflow_count > 0)
        {
            //                jassertfalse; // not sure if we'll ever hit this?
            chowdsp::BufferMath::copyBufferData (overflow_buffer, overflow_buffer, overflow_samples_to_copy, 0, overflow_count);
        }
    }

    while (bungee_input_buffer->inputFrameCountRequired() <= 0)
    {
        Bungee::OutputChunk output_chunk {};
        bungee->analyseGrain (bungee_input_buffer->outputData(), bungee_input_buffer->stride());
        bungee->synthesiseGrain (output_chunk);
        bungee->next (request);
        pull_count += output_chunk.frameCount;

        for (const auto& [ch, data] : chowdsp::buffer_iters::channels (overflow_buffer))
        {
            std::copy (output_chunk.data + ch * output_chunk.channelStride,
                       output_chunk.data + ch * output_chunk.channelStride + output_chunk.frameCount,
                       data.begin() + overflow_count);
        }
        overflow_count += output_chunk.frameCount;

        const auto next_input_chunk = bungee->specifyGrain (request);
        bungee_input_buffer->grain (next_input_chunk);
    }

    if (overflow_count > 0 && samples_written < num_samples)
    {
        const auto samples_to_fill = num_samples - samples_written;
        if (overflow_count >= samples_to_fill)
        {
            chowdsp::BufferMath::copyBufferData (overflow_buffer, buffer, 0, samples_written, samples_to_fill);
            overflow_count -= samples_to_fill;
            chowdsp::BufferMath::copyBufferData (overflow_buffer, overflow_buffer, samples_to_fill, 0, overflow_count);
        }
        else // if (overflow_count < samples_to_fill)
        {
//            jassertfalse; // not sure if we'll ever hit this?
            chowdsp::BufferMath::copyBufferData (overflow_buffer, buffer, 0, num_samples - overflow_count, overflow_count);
            overflow_count = 0;
        }
    }
}

juce::AudioProcessorEditor* PitchShift::createEditor()
{
    return new chowdsp::ParametersViewEditor { *this, state, state.params };
}

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PitchShift();
}