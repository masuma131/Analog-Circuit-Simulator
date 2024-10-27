//Inductor.cpp - functions implemention for Inductor

// TODO: Complete the functions

#include "Inductor.h"

Inductor::Inductor(double inductorValue, float red, float green, float blue, const std::string& inductorName)
    : inductance(inductorValue) {
    Red = red;
    Green = green;
    Blue = blue;
    name = inductorName;
}

std::string Inductor::GetName() const {

	return "Nothing";
};

void Inductor::Update() {

};

double Inductor::GetVoltage(double _current, double timestep) {

	return 0.0;
};

void Inductor::Display() {

};