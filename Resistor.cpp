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

	return "Nothing";
};

void Resistor::Update() {

};

double Resistor::GetVoltage(double _current, double timestep) {

	return 0.0;
};

void Resistor::Display() {

};