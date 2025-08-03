

// --------------------
// Source/PluginProcessor.h
// --------------------
#pragma once
#include <JuceHeader.h>
#include "PluginParameters.h"
#include "TubeModel.h"

class TubePreampPluginAudioProcessor : public juce::AudioProcessor {
public:
    TubePreampPluginAudioProcessor();
    ~TubePreampPluginAudioProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override { return true; }

    const juce::String getName() const override { return "Tube610"; }
    bool acceptsMidi() const override { return false; }
    bool producesMidi() const override { return false; }
    double getTailLengthSeconds() const override { return 0.0; }

    int getNumPrograms() override { return 1; }
    int getCurrentProgram() override { return 0; }
    void setCurrentProgram(int) override {}
    const juce::String getProgramName(int) override { return {}; }
    void changeProgramName(int, const juce::String&) override {}

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* driveParam = nullptr;
    std::atomic<float>* outputParam = nullptr;
    std::atomic<float>* biasParam = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TubePreampPluginAudioProcessor)
};
