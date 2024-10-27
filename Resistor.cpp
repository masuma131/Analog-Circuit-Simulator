//Resistor.cpp - functions implemention for Resistor

// TODO: Complete the functions

#include "Resistor.h"

Resistor::Resistor(double resistorValue, float red, float green, float blue, const std::string& resistorName)
    : resistance(resistorValue) {
    Red = red;
    Green = green;
    Blue = blue;
    name = resistorName;
}

std::string Resistor::GetName() const {

	return name;
};

void Resistor::Update() {

};

double Resistor::GetVoltage(double _current, double timestep) {

	return _current * resistance;
};

void Resistor::Display() {
    AnalogCircuit::display(Red, Green, Blue); // RGB display based on inductor color
};