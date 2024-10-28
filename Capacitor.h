//Capacitor.h - header file for Capacitor

#ifndef _CAPACITOR_H_
#define _CAPACITOR_H_

#include "AnalogCircuit.h"
#include "Component.h"

class Capacitor : public Component{
	double capacitance;
	double curr_voltage;
	double prev_voltage;
public:
	Capacitor(double capacitorValue, float red, float green, float blue, const std::string& capacitorName);

	std::string GetName() const override;
	void Update() override;
	double GetVoltage(double _current, double timestep) override;
	void Display() override;
};

#endif// _CAPACITOR_H_