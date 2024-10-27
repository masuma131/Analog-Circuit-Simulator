//Capacitor.cpp - functions implemention for Capacitor

// TODO: Complete the functions

#include "Capacitor.h"

Capacitor::Capacitor(double capacitorValue, float red, float green, float blue, const std::string& capacitorName)
    : capacitance(capacitorValue) {
    Red = red;
    Green = green;
    Blue = blue;
    name = capacitorName;
}

std::string Capacitor::GetName() const {

	return "Nothing";
};

void Capacitor::Update() {

};

double Capacitor::GetVoltage(double _current, double timestep) {

	return 0.0;
};

void Capacitor::Display() {
    AnalogCircuit::display(Red, Green, Blue); // RGB display based on capacitor color
};