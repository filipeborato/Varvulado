// --------------------
// Source/PluginEditor.h
// --------------------
#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "VintageLookAndFeel.h"

class TubePreampPluginAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer {
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

    // Cached velvet background
    juce::Image velvetBackground;
    void regenerateVelvetBackground();
    void drawLogoBlended(juce::Graphics& g, juce::Rectangle<int> dstArea);

    VintageLookAndFeel vintageLNF;

    // Tube valve animation (top-right)
    void timerCallback() override;
    void drawTubeValve(juce::Graphics& g, juce::Rectangle<int> area);
    float tubeAnimPhase { 0.0f };
    std::atomic<float>* driveParam { nullptr };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TubePreampPluginAudioProcessorEditor);
};
