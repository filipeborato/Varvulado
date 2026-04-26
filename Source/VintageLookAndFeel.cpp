#include "VintageLookAndFeel.h"

VintageLookAndFeel::VintageLookAndFeel()
{
    setColour(juce::Slider::textBoxTextColourId, juce::Colour::fromRGB(250, 238, 199));
    setColour(juce::Slider::textBoxBackgroundColourId, juce::Colour::fromRGB(39, 24, 72));
    setColour(juce::Slider::textBoxOutlineColourId, juce::Colour::fromRGB(191, 159, 76));
    setColour(juce::Slider::textBoxHighlightColourId, juce::Colour::fromRGB(117, 49, 79));
}

void VintageLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                          float sliderPosProportional, float rotaryStartAngle,
                                          float rotaryEndAngle, juce::Slider& slider)
{
    juce::ignoreUnused(slider);

    const auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat();
    const auto centre = bounds.getCentre();
    const float diameter = juce::jmin(bounds.getWidth(), bounds.getHeight());
    const float radius = diameter * 0.5f;
    const float pad = juce::jmax(7.0f, diameter * 0.10f);
    const float rScale = radius - 3.0f;
    const float rOuter = radius - pad - 3.0f;
    const float rFace = rOuter * 0.74f;
    const float rHub = rFace * 0.23f;
    const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    g.setImageResamplingQuality(juce::Graphics::highResamplingQuality);

    // Brass dial scale behind the knob, so the control reads on the dark velvet.
    {
        juce::Path scaleArc;
        scaleArc.addCentredArc(centre.x, centre.y, rScale, rScale, 0.0f,
                               rotaryStartAngle, rotaryEndAngle, true);
        g.setColour(juce::Colour::fromRGB(154, 112, 42).withAlpha(0.42f));
        g.strokePath(scaleArc, juce::PathStrokeType(2.2f, juce::PathStrokeType::curved,
                                                   juce::PathStrokeType::rounded));

        const int ticks = 13;
        for (int i = 0; i < ticks; ++i)
        {
            const float t = (float) i / (float) (ticks - 1);
            const float a = rotaryStartAngle + t * (rotaryEndAngle - rotaryStartAngle);
            const bool major = (i == 0 || i == ticks - 1 || i == (ticks - 1) / 2);
            const float tickLen = major ? 8.0f : 4.5f;
            const auto p0 = juce::Point<float>(centre.x + std::cos(a) * (rScale - tickLen),
                                               centre.y + std::sin(a) * (rScale - tickLen));
            const auto p1 = juce::Point<float>(centre.x + std::cos(a) * rScale,
                                               centre.y + std::sin(a) * rScale);
            g.setColour(juce::Colour::fromRGB(241, 210, 129).withAlpha(major ? 0.80f : 0.48f));
            g.drawLine({ p0, p1 }, major ? 1.6f : 1.0f);
        }
    }

    g.setColour(juce::Colours::black.withAlpha(0.32f));
    g.fillEllipse(centre.x - rOuter, centre.y - rOuter + 4.0f, rOuter * 2.0f, rOuter * 2.0f);

    // Thin black bakelite skirt.
    {
        juce::ColourGradient skirt(juce::Colour::fromRGB(62, 58, 62),
                                   centre.x - rOuter * 0.45f, centre.y - rOuter * 0.55f,
                                   juce::Colour::fromRGB(8, 8, 10),
                                   centre.x + rOuter * 0.55f, centre.y + rOuter * 0.70f, true);
        g.setGradientFill(skirt);
        g.fillEllipse(centre.x - rOuter, centre.y - rOuter, rOuter * 2.0f, rOuter * 2.0f);

        const int ridges = 36;
        for (int i = 0; i < ridges; ++i)
        {
            const float a = juce::MathConstants<float>::twoPi * (float) i / (float) ridges;
            const float inner = rOuter * 0.84f;
            const float outer = rOuter * 0.98f;
            const auto p0 = juce::Point<float>(centre.x + std::cos(a) * inner,
                                               centre.y + std::sin(a) * inner);
            const auto p1 = juce::Point<float>(centre.x + std::cos(a) * outer,
                                               centre.y + std::sin(a) * outer);
            g.setColour((i % 2 == 0 ? juce::Colours::white : juce::Colours::black).withAlpha(i % 2 == 0 ? 0.075f : 0.25f));
            g.drawLine({ p0, p1 }, 1.0f);
        }

        g.setColour(juce::Colours::black.withAlpha(0.82f));
        g.drawEllipse(centre.x - rOuter, centre.y - rOuter, rOuter * 2.0f, rOuter * 2.0f, 1.8f);
        g.setColour(juce::Colour::fromRGB(230, 195, 103).withAlpha(0.65f));
        g.drawEllipse(centre.x - rOuter + 2.5f, centre.y - rOuter + 2.5f,
                      (rOuter - 2.5f) * 2.0f, (rOuter - 2.5f) * 2.0f, 1.0f);
    }

    // Champagne face: intentionally kitsch, but brighter and cleaner than the old black disk.
    {
        juce::ColourGradient face(juce::Colour::fromRGB(253, 237, 190),
                                  centre.x - rFace * 0.35f, centre.y - rFace * 0.45f,
                                  juce::Colour::fromRGB(142, 94, 42),
                                  centre.x + rFace * 0.70f, centre.y + rFace * 0.75f, true);
        g.setGradientFill(face);
        g.fillEllipse(centre.x - rFace, centre.y - rFace, rFace * 2.0f, rFace * 2.0f);

        g.setColour(juce::Colour::fromRGB(58, 30, 28).withAlpha(0.46f));
        g.drawEllipse(centre.x - rFace, centre.y - rFace, rFace * 2.0f, rFace * 2.0f, 1.2f);

        juce::Path gloss;
        gloss.addPieSegment(centre.x - rFace, centre.y - rFace, rFace * 2.0f, rFace * 2.0f,
                            -2.45f, -0.80f, 0.18f);
        g.setColour(juce::Colours::white.withAlpha(0.18f));
        g.fillPath(gloss);
    }

    // Slim ruby pointer with a brass cap. It is loud, but much more legible.
    {
        const float baseR = rHub * 0.55f;
        const float tipR = rFace * 0.88f;
        const float halfW = juce::jmax(2.4f, rFace * 0.055f);
        const auto tangent = juce::Point<float>(-std::sin(angle), std::cos(angle));
        const auto base = juce::Point<float>(centre.x + std::cos(angle) * baseR,
                                             centre.y + std::sin(angle) * baseR);
        const auto tip = juce::Point<float>(centre.x + std::cos(angle) * tipR,
                                            centre.y + std::sin(angle) * tipR);

        juce::Path pointer;
        pointer.startNewSubPath(base + tangent * halfW);
        pointer.lineTo(tip);
        pointer.lineTo(base - tangent * halfW);
        pointer.closeSubPath();

        juce::ColourGradient ruby(juce::Colour::fromRGB(255, 68, 66), base.x, base.y,
                                  juce::Colour::fromRGB(108, 14, 33), tip.x, tip.y, false);
        g.setGradientFill(ruby);
        g.fillPath(pointer);
        g.setColour(juce::Colours::black.withAlpha(0.45f));
        g.strokePath(pointer, juce::PathStrokeType(0.9f, juce::PathStrokeType::curved,
                                                  juce::PathStrokeType::rounded));

        g.setColour(juce::Colour::fromRGB(255, 236, 178).withAlpha(0.75f));
        g.drawLine({ base + tangent * (halfW * 0.25f), tip - tangent * (halfW * 0.15f) }, 0.8f);
    }

    // Center cap.
    {
        juce::ColourGradient cap(juce::Colour::fromRGB(255, 226, 148),
                                 centre.x - rHub * 0.35f, centre.y - rHub * 0.45f,
                                 juce::Colour::fromRGB(103, 63, 28),
                                 centre.x + rHub * 0.65f, centre.y + rHub * 0.75f, true);
        g.setGradientFill(cap);
        g.fillEllipse(centre.x - rHub, centre.y - rHub, rHub * 2.0f, rHub * 2.0f);
        g.setColour(juce::Colours::black.withAlpha(0.48f));
        g.drawEllipse(centre.x - rHub, centre.y - rHub, rHub * 2.0f, rHub * 2.0f, 1.0f);

        g.setColour(juce::Colours::white.withAlpha(0.20f));
        g.fillEllipse(centre.x - rHub * 0.45f, centre.y - rHub * 0.55f, rHub * 0.55f, rHub * 0.38f);
    }
}
