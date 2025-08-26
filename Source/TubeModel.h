// --------------------
// Source/TubeModel.h
// --------------------
#pragma once
#include <cmath>

/**
 * Enhanced triode model incorporating:
 * - Polynomial soft-clipping (a1*v + a3*v^3)
 * - tanh saturation stage
 * - 1st-order RC low-pass (plate resistor and capacitance)
 * - High-pass coupling capacitor (grid leak)
 */
class TubeModel {
public:
    TubeModel() = default;

    /**
     * Prepare internal coefficients based on sample rate and component values.
     * @param sampleRate Sampling frequency in Hz.
     * @param plateRes Plate resistor value (ohms).
     * @param plateCap Plate capacitance (farads).
     * @param couplingCap Grid coupling capacitance (farads).
     */
    void prepare(double sampleRate, float plateRes = 100e3f, float plateCap = 2e-12f, float couplingCap = 10e-9f) {
        // Low-pass RC: lpCoeff = dt / (RC + dt)
        float dt = 1.0f / sampleRate;
        float rcLP = plateRes * plateCap;
        lpCoeff = dt / (rcLP + dt);

        // High-pass RC: hpCoeff = RC / (RC + dt)
        float rcHP = plateRes * couplingCap;
        hpCoeff = rcHP / (rcHP + dt);
    }

    /**
     * Process one sample through the triode model.
     * @param in Input sample (voltage).
     * @param drive Gain factor simulating grid biasing.
     * @param bias DC bias voltage.
     * @return Processed output sample.
     */
    float processSample(float in, float drive, float bias) {
        // High-pass filter (grid coupling)
        float hpOut = hpCoeff * (hpPrev + in - hpPrev);
        hpPrev = hpOut;

        // Apply drive and bias
        float v = drive * (hpOut + bias);

        // Polynomial pre-emphasis (soft clipping)
        float poly = a1 * v + a2 * v * v + a3 * v * v * v;

        // Tanh saturation (triode characteristic)
        float sat = std::tanh(poly);

        // Low-pass filter (plate capacitance)
        float lpOut = lpPrev + lpCoeff * (sat - lpPrev);
        lpPrev = lpOut;

        return lpOut;
    }

    /** Reset internal filter states. */
    void reset() {
        lpPrev = 0.0f;
        hpPrev = 0.0f;
    }

private:
    // Soft-clipping polynomial coefficients
    const float a1 = 1.0f;
	const float a2 = 0.3f; // Not used, but can be set for more complex models
    const float a3 = 0.2f;
    float lpPrev = 0.0f;
    float hpPrev = 0.0f;
    float lpCoeff = 1.0f;
    float hpCoeff = 1.0f;
};