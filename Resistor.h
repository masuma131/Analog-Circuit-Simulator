//Resistor.h - header file for Resistor

#ifndef _RESISTOR_H_
#define _RESISTOR_H_

#include "Component.h"

class Resistor : public Component {
	double resistance;

public:
	Resistor(double resistorValue, float red, float green, float blue, const std::string& resistorName);
	std::string GetName() const;
	void Update();
	double GetVoltage(double _current, double timestep);
	void Display();
};

#endif// _RESISTOR_H_