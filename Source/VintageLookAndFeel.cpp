// --------------------
// Source/VintageLookAndFeel.cpp
// --------------------
#include "VintageLookAndFeel.h"

static juce::Colour withGain(juce::Colour c, float gain) {
    return juce::Colour::fromFloatRGBA(
        juce::jlimit<float>(0.0f, 1.0f, c.getFloatRed()   * gain),
        juce::jlimit<float>(0.0f, 1.0f, c.getFloatGreen() * gain),
        juce::jlimit<float>(0.0f, 1.0f, c.getFloatBlue()  * gain),
        c.getFloatAlpha());
}

void VintageLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                                          float sliderPosProportional, float rotaryStartAngle,
                                          float rotaryEndAngle, juce::Slider& slider)
{
    const auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat();
    const auto centre = bounds.getCentre();
    const float diameter = juce::jmin(bounds.getWidth(), bounds.getHeight());
    const float radius = diameter * 0.5f;
    const float pad = juce::jmax(4.0f, diameter * 0.08f);
    const float rOuter = radius - pad;
    const float rInner = rOuter * 0.72f;

    // Angles
    const float angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    g.setImageResamplingQuality(juce::Graphics::highResamplingQuality);
    g.setOpacity(1.0f);

    // Drop shadow ellipse
    {
        juce::Path shadow;
        shadow.addEllipse(centre.x - rOuter, centre.y - rOuter + 2.0f, rOuter * 2.0f, rOuter * 2.0f);
        g.setColour(juce::Colours::black.withAlpha(0.25f));
        g.fillPath(shadow);
    }

    // Skirt (outer ring) — Fairchild bakelite with rim highlight
    {
        juce::Colour cDark(10, 10, 12);
        juce::Colour cLight(58, 58, 62);
        juce::ColourGradient grad(cLight, centre.x - rOuter * 0.3f, centre.y - rOuter * 0.3f,
                                  cDark, centre.x + rOuter * 0.8f, centre.y + rOuter * 0.8f, true);
        g.setGradientFill(grad);
        g.fillEllipse(centre.x - rOuter, centre.y - rOuter, rOuter * 2.0f, rOuter * 2.0f);

        // Outer rim
        g.setColour(juce::Colours::black.withAlpha(0.8f));
        g.drawEllipse(centre.x - rOuter, centre.y - rOuter, rOuter * 2.0f, rOuter * 2.0f, 1.5f);

        // Inner rim
        g.setColour(juce::Colours::grey.withAlpha(0.4f));
        g.drawEllipse(centre.x - rInner, centre.y - rInner, rInner * 2.0f, rInner * 2.0f, 1.0f);
    }

    // Scalloped knurl on skirt (deep flutes)
    {
        const int flutes = 16; // large scallops
        const float inner = rOuter * 0.80f;
        for (int i = 0; i < flutes; ++i)
        {
            const float a = juce::MathConstants<float>::twoPi * (float) i / (float) flutes;
            const float nx = std::cos(a), ny = std::sin(a);
            auto p0 = juce::Point<float>(centre.x + nx * (inner - 1.0f), centre.y + ny * (inner - 1.0f));
            auto p1 = juce::Point<float>(centre.x + nx * (rOuter - 1.0f), centre.y + ny * (rOuter - 1.0f));

            // Shadow stroke
            g.setColour(juce::Colours::black.withAlpha(0.35f));
            g.drawLine({ p0, p1 }, 2.0f);
            // Highlight stroke slightly offset
            g.setColour(juce::Colours::white.withAlpha(0.08f));
            g.drawLine({ p0 + juce::Point<float>(-ny, nx) * 1.0f, p1 + juce::Point<float>(-ny, nx) * 1.0f }, 1.2f);
        }
    }

    // Face (inner disk) — black face, subtle dome and specular
    {
        juce::Colour faceBase = juce::Colour::fromRGB(22, 22, 24);
        juce::Colour faceHi   = juce::Colour::fromRGB(64, 64, 70);
        juce::ColourGradient face(faceHi, centre.x - rInner * 0.25f, centre.y - rInner * 0.25f,
                                  faceBase, centre.x + rInner * 0.6f, centre.y + rInner * 0.6f, true);
        g.setGradientFill(face);
        g.fillEllipse(centre.x - rInner, centre.y - rInner, rInner * 2.0f, rInner * 2.0f);

        // Specular sweep
        juce::Path sweep; sweep.addPieSegment(centre.x - rInner, centre.y - rInner, rInner * 2.0f, rInner * 2.0f,
                                              -juce::MathConstants<float>::halfPi * 0.8f,
                                              -juce::MathConstants<float>::halfPi * 0.3f,
                                              0.14f);
        g.setColour(juce::Colours::white.withAlpha(0.06f));
        g.fillPath(sweep);
    }

    // Index tick ring on panel (subtle)
    {
        const float ringR = rOuter + 6.0f;
        const int ticks = 11; // includes center
        for (int i = 0; i < ticks; ++i)
        {
            const float t = (float) i / (float) (ticks - 1);
            const float a = rotaryStartAngle + t * (rotaryEndAngle - rotaryStartAngle);
            juce::Point<float> p0(centre.x + std::cos(a) * (ringR - 5.0f), centre.y + std::sin(a) * (ringR - 5.0f));
            juce::Point<float> p1(centre.x + std::cos(a) * (ringR - 2.0f), centre.y + std::sin(a) * (ringR - 2.0f));
            const bool endTick = (i == 0 || i == ticks - 1);
            const bool midTick = (i == (ticks - 1) / 2);
            g.setColour(juce::Colours::white.withAlpha(midTick ? 0.22f : (endTick ? 0.16f : 0.10f)));
            g.drawLine({ p0, p1 }, midTick ? 1.3f : (endTick ? 1.0f : 0.8f));
        }
    }

    // Pointer — Fairchild-style cream wedge on black face
    {
        const float pr0 = rInner * 0.18f;    // inner start
        const float pr1 = rInner * 0.96f;    // to rim
        const float halfA = juce::jlimit<float>(0.06f, 0.12f, rInner * 0.0008f + 0.09f); // wedge half-angle

        juce::Path wedge;
        auto p0 = juce::Point<float>(centre.x + std::cos(angle - halfA) * pr0,
                                     centre.y + std::sin(angle - halfA) * pr0);
        auto p1 = juce::Point<float>(centre.x + std::cos(angle + halfA) * pr0,
                                     centre.y + std::sin(angle + halfA) * pr0);
        auto p2 = juce::Point<float>(centre.x + std::cos(angle + halfA * 0.9f) * pr1,
                                     centre.y + std::sin(angle + halfA * 0.9f) * pr1);
        auto p3 = juce::Point<float>(centre.x + std::cos(angle - halfA * 0.9f) * pr1,
                                     centre.y + std::sin(angle - halfA * 0.9f) * pr1);
        wedge.startNewSubPath(p0); wedge.lineTo(p1); wedge.lineTo(p2); wedge.lineTo(p3); wedge.closeSubPath();

        // Antique ivory tone
        juce::Colour ivory(236, 224, 188);
        juce::Colour ivoryEdge(208, 194, 160);
        juce::ColourGradient wg(ivory, (p0.x + p1.x) * 0.5f, (p0.y + p1.y) * 0.5f,
                                ivoryEdge, (p2.x + p3.x) * 0.5f, (p2.y + p3.y) * 0.5f, false);
        g.setGradientFill(wg);
        g.fillPath(wedge);
        g.setColour(juce::Colours::black.withAlpha(0.25f));
        g.strokePath(wedge, juce::PathStrokeType(0.9f));

        // Fine center line on wedge
        juce::Point<float> c0(centre.x + std::cos(angle) * pr0, centre.y + std::sin(angle) * pr0);
        juce::Point<float> c1(centre.x + std::cos(angle) * pr1, centre.y + std::sin(angle) * pr1);
        g.setColour(juce::Colours::white.withAlpha(0.22f));
        g.drawLine({ c0, c1 }, 0.7f);
    }

    // Center screw (chrome with slot)
    {
        const float capR = rInner * 0.22f;
        juce::Colour c0 = juce::Colour::fromRGB(210, 210, 210);
        juce::Colour c1 = juce::Colour::fromRGB(120, 120, 120);
        juce::ColourGradient grad(c0, centre.x, centre.y - capR * 0.7f,
                                  c1, centre.x, centre.y + capR * 0.9f, true);
        g.setGradientFill(grad);
        g.fillEllipse(centre.x - capR, centre.y - capR, capR * 2.0f, capR * 2.0f);
        g.setColour(juce::Colours::black.withAlpha(0.5f));
        g.drawEllipse(centre.x - capR, centre.y - capR, capR * 2.0f, capR * 2.0f, 1.0f);

        // Slot
        const float slotW = juce::jmax(1.2f, capR * 0.20f);
        const float slotL = capR * 1.4f;
        juce::Path slot; slot.startNewSubPath(centre.x - slotL * 0.5f, centre.y);
        slot.lineTo(centre.x + slotL * 0.5f, centre.y);
        g.setColour(juce::Colours::black.withAlpha(0.75f));
        g.strokePath(slot, juce::PathStrokeType(slotW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
        g.setColour(juce::Colours::white.withAlpha(0.25f));
        g.strokePath(slot, juce::PathStrokeType(slotW * 0.4f));
    }
}
