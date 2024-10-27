//Inductor.h - header file for Inductor

#include "AnalogCircuit.h"

#ifndef _INDUCTOR_H_
#define _INDUCTOR_H_

#include "Component.h"

class Inductor : public Component{
	double inductance;
	double prev_current;

public:
	Inductor(double inductorValue, float red, float green, float blue, const std::string& inductorName);
	std::string GetName() const override;
	void Update() override;
	double GetVoltage(double _current, double timestep) override;
	void Display() override;
};

#endif// _INDUCTOR_H_