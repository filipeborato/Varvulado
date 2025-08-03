// --------------------
// Source/PluginEditor.cpp
// --------------------
#include "PluginEditor.h"

TubePreampPluginAudioProcessorEditor::TubePreampPluginAudioProcessorEditor(
    TubePreampPluginAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor(&p), processor(p), state(vts)
{
    setSize(400, 300);

    // Drive Slider
    driveSlider.setSliderStyle(juce::Slider::Rotary);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(driveSlider);
    driveAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(state, "drive", driveSlider);

    // Drive Label
    driveLabel.setText("DRIVE", juce::dontSendNotification);
    driveLabel.setJustificationType(juce::Justification::centred);
    driveLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(driveLabel);

    // Output Slider
    outputSlider.setSliderStyle(juce::Slider::Rotary);
    outputSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(outputSlider);
    outputAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(state, "output", outputSlider);

    // Output Label
    outputLabel.setText("OUTPUT", juce::dontSendNotification);
    outputLabel.setJustificationType(juce::Justification::centred);
    outputLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(outputLabel);

    // Bias Slider
    biasSlider.setSliderStyle(juce::Slider::Rotary);
    biasSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(biasSlider);
    biasAttach = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(state, "bias", biasSlider);

    // Bias Label
    biasLabel.setText("BIAS", juce::dontSendNotification);
    biasLabel.setJustificationType(juce::Justification::centred);
    biasLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(biasLabel);
}

TubePreampPluginAudioProcessorEditor::~TubePreampPluginAudioProcessorEditor() {}

void TubePreampPluginAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colours::darkgrey);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawFittedText("Tube Preamp 610", 0, 10, getWidth(), 30, juce::Justification::centred, 1);
}

void TubePreampPluginAudioProcessorEditor::resized() {
    auto area = getLocalBounds().reduced(20).removeFromBottom(220);
    
    // Drive section
    auto driveArea = area.removeFromLeft(120).reduced(10);
    driveLabel.setBounds(driveArea.removeFromTop(20));
    driveSlider.setBounds(driveArea);
    
    // Output section
    auto outputArea = area.removeFromLeft(120).reduced(10);
    outputLabel.setBounds(outputArea.removeFromTop(20));
    outputSlider.setBounds(outputArea);
    
    // Bias section
    auto biasArea = area.removeFromLeft(120).reduced(10);
    biasLabel.setBounds(biasArea.removeFromTop(20));
    biasSlider.setBounds(biasArea);
}
