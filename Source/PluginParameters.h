// --------------------
// Source/PluginParameters.h
// --------------------
#pragma once
#include <JuceHeader.h>

inline juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterFloat>("drive", "Drive", 0.1f, 10.0f, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("output", "Output", 0.0f, 1.0f, 0.8f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("bias", "Bias", -5.0f, 5.0f, 0.0f));
    return { params.begin(), params.end() };
}