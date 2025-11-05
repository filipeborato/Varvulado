// --------------------
// Source/VintageLookAndFeel.h
// --------------------
#pragma once
#include <JuceHeader.h>

class VintageLookAndFeel : public juce::LookAndFeel_V4 {
public:
    VintageLookAndFeel() = default;
    ~VintageLookAndFeel() override = default;

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider& slider) override;

    int getSliderThumbRadius(juce::Slider&) override { return 10; }
};

