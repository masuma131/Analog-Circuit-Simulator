
//Resistor.cpp - functions implemention for Resistor

#include "Resistor.h"

// Constructor
Resistor::Resistor(double resistorValue, float red, float green, float blue, const std::string& resistorName)
    : resistance(resistorValue) {
    Red = red;
    Green = green;
    Blue = blue;
    name = resistorName;
}

// GetName - Returns the name of the resistor.
std::string Resistor::GetName() const {

	return name;
};

// Update - Placeholder function. No action needed, as resistors don't have time-dependent states.
void Resistor::Update() {
    // Resistors don't have internal states that change over time

};

// GetVoltage - Calculates and returns the voltage across the resistor based on current and Ohm's Law (V = I * R).
double Resistor::GetVoltage(double _current, double timestep) {

	return _current * resistance;
};

// Display - Sets the display color of the resistor to its specified RGB values.
void Resistor::Display() {
    AnalogCircuit::display(Red, Green, Blue); 
};