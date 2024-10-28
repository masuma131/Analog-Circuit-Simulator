
//Inductor.cpp - functions implemention for Inductor

#include "Inductor.h"

// Constructor
Inductor::Inductor(double inductorValue, float red, float green, float blue, const std::string& inductorName)
    : inductance(inductorValue), curr_current(0.0), prev_current(0.0) {
    Red = red;
    Green = green;
    Blue = blue;
    name = inductorName;
}

// GetName - Returns the name of the inductor.
std::string Inductor::GetName() const {

	return name;
};

// Update - Updates the previous current to the current current value for use in the next voltage calculation.
void Inductor::Update() {
    prev_current = curr_current;
};

// GetVoltage - Calculates and returns the voltage across the inductor based on the rate of change of current (V = L * di/dt).
double Inductor::GetVoltage(double _current, double timestep) {
    double voltage = inductance * (_current - prev_current) / timestep;
    curr_current = _current;
    return voltage;
};

// Display - Sets the display color of the inductor to its specified RGB values.
void Inductor::Display() {

    AnalogCircuit::display(Red, Green, Blue); // RGB display based on inductor color
};