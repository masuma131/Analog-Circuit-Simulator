//Masuma Begum, Mary-Anne Chinonyelum Ibeh, Chloe Quijano
//AnalogCircuit.cpp - function definitions for the analog circuit
// 20-May-22  M. Watler         Created.
// 27-May-22  M. Watler         Added graphical display.


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

// Entry point of the program
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

// Function to display a point on the screen
void AnalogCircuit::display(float R, float G, float B)  {//draw a point on the screen
	//	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(R, G, B);//RGB
	glBegin(GL_POINTS);
	glVertex2f(xpos, ypos);
	glEnd();
	glFlush();
}

// Constructor initializes the circuit and opens the output file
AnalogCircuit::AnalogCircuit(string filename) : fout(filename) {
	//dump data to filename, initialize variables
		if (!fout.is_open()) {
			std::cerr << "Error opening file: " << filename << std::endl;
		}
		I = 0.0;  
}

// Main function to run the simulation
void AnalogCircuit::run() {
	component.push_back(new Capacitor(0.000100, 0.0, 1.0, 0.0, "C1"));//100uF, Green
	component.push_back(new Inductor(0.020, 0.0, 0.0, 1.0, "L1"));//20mH, Blue
	component.push_back(new Resistor(10, 1.0, 0.0, 0.0, "R1"));//10ohm, Red

	glColor3f(255.0, 255.0, 255.0);


	// Horizontal line
	glBegin(GL_LINES);
	glVertex2f(0, scalingFactor * windowHeight / 2.0); // Starting from the left edge with scaling applied
	glVertex2f(windowWidth, scalingFactor * windowHeight / 2.0); // Going across the width of the window
	glEnd();

	// Draw a vertical line at xoffset
	glBegin(GL_LINES);
	glVertex2f(xoffset, 0); // Starting from the bottom edge
	glVertex2f(xoffset, scalingFactor * windowHeight); // Going to the top of the window with scaling applied
	glEnd();


	//Draw horizontal line markers every 50 pixels
	for (int i = 0; i <= windowWidth; i += 50) {
		glBegin(GL_LINES);
		glVertex2f(i, scalingFactor * windowHeight / 2.0 - 10); // Adjust to keep markers centered
		glVertex2f(i, scalingFactor * windowHeight / 2.0 + 10); // Adjust to keep markers centered
		glEnd();
	}

	//vertical line markers
	//Draw positive direction vertical markers every 50 pixels
	for (ypos = scalingFactor * windowHeight / 2.0; ypos < scalingFactor * windowHeight; ypos += 50) {
		glBegin(GL_LINES);
		glVertex2f(xoffset + 10, ypos);
		glVertex2f(xoffset - 10, ypos);
		glEnd();
	}
	// Draw negative direction vertical markers every 50 pixels
	for (ypos = scalingFactor * windowHeight / 2.0; ypos > 0; ypos -= 50) {
		glBegin(GL_LINES);
		glVertex2f(xoffset + 10, ypos);  // Right side of the vertical line
		glVertex2f(xoffset - 10, ypos);  // Left side of the vertical line
		glEnd();
	}

	//Display each component's name and colour
	list<Component*>::iterator it;
	ypos = windowHeight - 20;
	for (it = component.begin(); it != component.end(); ++it) {
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(0, ypos);
		for (int i = 0; i < (*it)->GetName().length(); ++i) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, (*it)->GetName()[i]);
		for (xpos = xoffset - 30; xpos < xoffset - 20; xpos += 1) {
			(*it)->Display();
		}
		ypos -= 15;

	}
	
	//Dump data to a file as well as display on the screen
	fout << "		time		Voltage		Current		V_cap		V_ind		V_res" <<endl;;  // Header for the output file

	// Run simulation for the first 0.06 seconds with sinusoidal voltage
	for (double time = 0.0; time < 0.6 * timeMax; time += T) {
		double V = Vpeak * sin(2.0 * M_PI * freq * time);

		// Output data to the console
		// std::cout << "Time: " << time << " s, Voltage: " << V << " V, Current: " << I << " A" << std::endl;

		// Save data to the file
		fout.setf(ios::fixed);
		fout.precision(7);
		fout << setw(12) << time;
		fout << setw(12) << V;

		glBegin(GL_POINTS);
		xpos = time * (windowWidth - xoffset) / timeMax + xoffset;
		ypos = (windowHeight * V / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		display(1.0, 1.0, 1.0);
		// Calculate current and update the output for this voltage
		CostFunctionV(I, V);

	}

	// Run simulation for the remaining time up to 0.1 seconds with zero voltage
	for (double time = 0.6 * timeMax; time < timeMax; time += T) {
		double V = 0.0;

		// Output data to the console
		//std::cout << "Time: " << time << " s, Voltage: " << V << " V, Current: " << I << " A" << std::endl;

		// Save data to the file
		fout.setf(ios::fixed);
		fout.precision(7);
		fout << setw(12) << time;
		fout << setw(12) << V;
		glBegin(GL_POINTS);
		xpos = time * (windowWidth - xoffset) / timeMax + xoffset;
		ypos = (windowHeight * V / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0;
		display(1.0, 1.0, 1.0);

		// Calculate current and update the output for zero voltage
		CostFunctionV(I, V);

	}

}

void AnalogCircuit::CostFunctionV(double& current, double voltage) {
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
		if (alpha < tolerance / 1000000.0) {//reset alpha
			alpha = ((double)rand() / (RAND_MAX)) + 0.5;//between 0.5 and 1.5
		}
	} while (abs(J1) > tolerance);

	fout << setw(12) << I1;
	list<Component*>::iterator it;

	for (it = component.begin(); it != component.end(); ++it) {
		fout << setw(12) << (*it)->GetVoltage(I1, T);
		ypos = static_cast<int>((windowHeight * (*it)->GetVoltage(I1, T) / Vpeak) / 2.0 + scalingFactor * windowHeight / 2.0);
		(*it)->Display();
		(*it)->Update();
	}
	fout << endl;

	current = I1;
}

AnalogCircuit::~AnalogCircuit() {
	//perform cleanup
	for (auto& comp : component) {
		delete comp;
	}
	component.clear();

	// Close file output stream
	if (fout.is_open()) {
		fout.close();
	}
}