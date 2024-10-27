//Capacitor.cpp - functions implemention for Capacitor

// TODO: Complete the functions

#include "Capacitor.h"

Capacitor::Capacitor(double capacitorValue, float red, float green, float blue, const std::string& capacitorName)
    : capacitance(capacitorValue), prev_voltage(0.0) {
    Red = red;
    Green = green;
    Blue = blue;
    name = capacitorName;
}

std::string Capacitor::GetName() const {

	return name;
};


void Capacitor::Update() {

};

double Capacitor::GetVoltage(double _current, double timestep) {
    double voltage = prev_voltage + (_current * timestep / capacitance);
    prev_voltage = voltage;
	return voltage;
};

void Capacitor::Display() {
    AnalogCircuit::display(Red, Green, Blue); // RGB display based on capacitor color
};