// --------------------
// Source/PluginProcessor.cpp
// --------------------
#include "PluginProcessor.h"
#include "PluginEditor.h"

TubePreampPluginAudioProcessor::TubePreampPluginAudioProcessor()
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)),
    parameters(*this, nullptr, "PARAMETERS", createParameterLayout())
{
    driveParam = parameters.getRawParameterValue("drive");
    outputParam = parameters.getRawParameterValue("output");
    biasParam = parameters.getRawParameterValue("bias");
}

TubePreampPluginAudioProcessor::~TubePreampPluginAudioProcessor() {}

void TubePreampPluginAudioProcessor::prepareToPlay(double, int) {}
void TubePreampPluginAudioProcessor::releaseResources() {}

void TubePreampPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    float drive = *driveParam;
    float output = *outputParam;
    float bias = *biasParam;

    for (int channel = 0; channel < totalNumInputChannels; ++channel) {
        auto* data = buffer.getWritePointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            float in = data[i];
            TubeModel tubeModel;
            float out = tubeModel.processSample(in, drive, bias);
            data[i] = out * output;
        }
    }
}

void TubePreampPluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
    auto xml = parameters.copyState().createXml();
    copyXmlToBinary(*xml, destData);
}

void TubePreampPluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
    if (auto xml = getXmlFromBinary(data, sizeInBytes))
        parameters.replaceState(juce::ValueTree::fromXml(*xml));
}

juce::AudioProcessorEditor* TubePreampPluginAudioProcessor::createEditor() {
    return new TubePreampPluginAudioProcessorEditor(*this, parameters);
}

// Esta funo 	 obrigatria para plugins JUCE
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TubePreampPluginAudioProcessor();
}