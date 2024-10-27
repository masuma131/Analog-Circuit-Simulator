//Inductor.cpp - functions implemention for Inductor


#include "Inductor.h"

Inductor::Inductor(double inductorValue, float red, float green, float blue, const std::string& inductorName)
    : inductance(inductorValue), curr_current(0.0), prev_current(0.0) {
    Red = red;
    Green = green;
    Blue = blue;
    name = inductorName;
}

std::string Inductor::GetName() const {

	return name;
};

void Inductor::Update() {
    prev_current = curr_current;
};

double Inductor::GetVoltage(double _current, double timestep) {
    double voltage = inductance * (_current - prev_current) / timestep;
    curr_current = _current;
    return voltage;
};

void Inductor::Display() {
    AnalogCircuit::display(Red, Green, Blue); // RGB display based on inductor color
};