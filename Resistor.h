//Resistor.h - header file for Resistor

#include "AnalogCircuit.h"

#ifndef _RESISTOR_H_
#define _RESISTOR_H_

#include "AnalogCircuit.h"
#include "Component.h"

class Resistor : public Component {
	double resistance;

public:
	Resistor(double resistorValue, float red, float green, float blue, const std::string& resistorName);
	std::string GetName() const override;
	void Update() override;
	double GetVoltage(double _current, double timestep) override;
	void Display() override;
};

#endif// _RESISTOR_H_