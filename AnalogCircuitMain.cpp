//AnalogCircuitMain.cpp - main function for the analog circuit simulation
//                        Generate graphs with the OpenGL graphics library


#include <iostream>
#include "AnalogCircuit.h"

using namespace std;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	cout << "Enter the width of the window: ";
	cin >> windowWidth;
	cout << "Enter the height of the window: ";
	cin >> windowHeight;
	cout << "Enter the height scaling factor: ";
	cin >> scalingFactor;
	glutInitWindowSize(windowWidth, scalingFactor * windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("ANASIM");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, scalingFactor * windowHeight);
	glutDisplayFunc(start);
	glutMainLoop();

	return 0;
}
