// --------------------
// Source/PluginEditor.h
// --------------------
#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class TubePreampPluginAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    TubePreampPluginAudioProcessorEditor(TubePreampPluginAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~TubePreampPluginAudioProcessorEditor() override;
    void paint(juce::Graphics&) override;
    void paintOverChildren(juce::Graphics&) override;
    void resized() override;

private:
    TubePreampPluginAudioProcessor& processor;
    juce::AudioProcessorValueTreeState& state;

    juce::Slider driveSlider, outputSlider, biasSlider;
    juce::Label driveLabel, outputLabel, biasLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttach, outputAttach, biasAttach;

    // Logo image (optional, drawn bottom-right without affecting layout)
    juce::Image logo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TubePreampPluginAudioProcessorEditor)
};
