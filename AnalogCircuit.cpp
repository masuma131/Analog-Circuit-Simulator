//AnalogCircuit.cpp - function definitions for the analog circuit
//
// 20-May-22  M. Watler         Created.
// 27-May-22  M. Watler         Added graphical display.


// TODO: Complete the code

#include <iomanip>//setw
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>//M_PI
#include <stdlib.h>//abs

#include "AnalogCircuit.h"
#include "Capacitor.h"
#include "Inductor.h"
#include "Resistor.h"

using namespace std;

int xpos, ypos;
int windowWidth, windowHeight;
double scalingFactor;

void start() {
	cout << "BEGIN" << endl;
	AnalogCircuit circuit("RLC.dat");
	circuit.run();
	cout << "Press any key + ENTER to end..." << endl;
	char key;
	cin >> key;
	glutLeaveMainLoop();
	cout << "DONE!" << endl;
}

void AnalogCircuit::display(float R, float G, float B) {//draw a point on the screen
//	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);//RGB
	glBegin(GL_POINTS);
	glVertex2f(xpos, ypos);
	glEnd();
	glFlush();
}

// TODO:dump data to filename
// Constructor: dump data to filename, initialize variables
AnalogCircuit::AnalogCircuit(string filename) {
	fout.open(filename);
	if (!fout.is_open()) {
		cerr << "Failed to open output file: " << filename << endl;
		exit(1);
	}
	fout << setw(12) << "Time" << setw(12) << "Current" << setw(12) << "Voltage" << endl;
	I = 0.0; // initial current
}

void AnalogCircuit::run() {
	component.push_back(new Capacitor(0.000100, 0.0, 1.0, 0.0, "C1"));//100uF, Green
	component.push_back(new Inductor(0.020, 0.0, 0.0, 1.0, "L1"));//20mH, Blue
	component.push_back(new Resistor(10, 1.0, 0.0, 0.0, "R1"));//10ohm, Red

	// TODO:
	//Horizontal line
	// 
	// TODO:
	//Vertical line

	// Draw horizontal and vertical lines
	glColor3f(1.0, 1.0, 1.0); // White color for axis lines
	glBegin(GL_LINES);
	glVertex2f(-1.0, 0.0); glVertex2f(1.0, 0.0); // Horizontal line
	glVertex2f(0.0, -1.0); glVertex2f(0.0, 1.0); // Vertical line
	glEnd();

	// TODO:
	//Horizontal line markers

	// TODO:
	//Vertical line markers

	// Draw line markers
	for (int i = -10; i <= 10; i++) {
		glBegin(GL_LINES);
		glVertex2f(i * 0.1, 0.05); glVertex2f(i * 0.1, -0.05); // Horizontal markers
		glVertex2f(0.05, i * 0.1); glVertex2f(-0.05, i * 0.1); // Vertical markers
		glEnd();
	}

	// TODO:
    //Display each component's name and colour


	// TODO:
    //Run the simulation for the first 0.06 seconds (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	for (double time = 0.0; time < 0.6*timeMax; time += T) {
		double V = Vpeak * sin(2.0 * M_PI * freq * time);

        //...

		CostFunctionV(I, V);
	}

	// TODO:
	//Run the simulation to the end (timeMax is 0.1 sec)
	//Dump data to a file as well as display on the screen
	for (double time = 0.6*timeMax; time < timeMax; time += T) {
		double V = 0.0;

        //...

		CostFunctionV(I, V);
	}
}

void AnalogCircuit::CostFunctionV(double &current, double voltage) {
	double I1 = current;
    double J1 = 0.0;
	double J0 = 0.0;
	double alpha = 1.0;

	do {
		double sumVoltage = 0.0;
		list<Component*>::iterator it;
		for (it = component.begin(); it != component.end(); ++it) {
			double Vcomponent = (*it)->GetVoltage(I1, T);
			sumVoltage += Vcomponent;
		}
		J1 = sumVoltage - voltage;
        //Reduce alpha if J1 and J0 are of opposite signs or are equal to each other
		if ((abs(J0 - J1) != (J0 - J1)) || J0 == J1)alpha /= 2.0;

		if (abs(J1) > tolerance) {
			if (J1 < 0) {//increase the current
				I1 += alpha;
			}
			else {
				I1 -= alpha;
			}
			J0 = J1;
		}
		if(alpha<tolerance/1000000.0) {//reset alpha
			alpha = ((double)rand() / (RAND_MAX)) + 0.5;//between 0.5 and 1.5
		}
	} while (abs(J1) > tolerance);

	fout << setw(12) << I1;
	list<Component*>::iterator it;
	for (it = component.begin(); it != component.end(); ++it) {
		fout << setw(12) << (*it)->GetVoltage(I1, T);
		ypos = (windowHeight * (*it)->GetVoltage(I1, T) / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		(*it)->Display();
		(*it)->Update();
	}
	fout << endl;

	current = I1;
}

// TODO:
AnalogCircuit::~AnalogCircuit() {//perform cleanup
}
