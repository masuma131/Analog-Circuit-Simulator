//Masuma Begum, Mary-Anne Chinonyelum Ibeh, Chloe Quijano

//Capacitor.cpp - functions implemention for Capacitor

#include "Capacitor.h"

// Constructor
Capacitor::Capacitor(double capacitorValue, float red, float green, float blue, const std::string& capacitorName)
    : capacitance(capacitorValue), curr_voltage(0.0), prev_voltage(0.0) {
    Red = red;
    Green = green;
    Blue = blue;
    name = capacitorName;
}

// GetName - Returns the name of the capacitor.
std::string Capacitor::GetName() const {

	return name;
};

// Update - Updates the previous voltage to the current voltage value for use in the next voltage calculation.
void Capacitor::Update() {
    prev_voltage = curr_voltage;
};

// GetVoltage - Calculates and returns the voltage across the capacitor based on the current and capacitance (V = V_prev + I * dt / C).
double Capacitor::GetVoltage(double _current, double timestep) {
    double voltage = prev_voltage + (_current * timestep / capacitance);
    curr_voltage = voltage;
	return voltage;
};

// Display - Sets the display color of the capacitor to its specified RGB values.
void Capacitor::Display() {
    AnalogCircuit::display(Red, Green, Blue); // RGB display based on capacitor color
};