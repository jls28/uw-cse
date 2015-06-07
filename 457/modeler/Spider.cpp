#include "modelerview.h"
#include "modelerdraw.h"
#include "modelerui.h"
#include "vault.h"
#include "FL/glut.h"
#include "model.h"
#include <cmath>
#include <time.h>
#include "spider.h"

static void drawUprightCylinder(double h, double r1, double r2);
static void drawSphere(double radius, int divisions);

Spider::Spider() : Model("Spider"), upperLegAngle("Spider Squats", 20.f, 160.f, 20.f, 1.f),
	headY("Move Head Y", -20.f, 20.f, 0.f, 1.f), headZ("Move Head Z", -60.f, 60.f, 0.f, 1.f),
	legLength("Leg Length", .5, 10, 4.f, .1f), legThickness("Leg Thickness", 0, .5, .125f, .005f),
	eyeAngle("Eye Distance", 0.f, 50.f, 30.f, 1.f), raiseFrontLegs("Raise Front Legs", 0.f, 80.f, 0.f, 1.f), 
	walk("Walk", 0.f, 1000.f, 0.f, 1.f), teapotMode("Teapot Mode:", false), numLegs("Number of Legs", 2.f, 30.f, 8.f, 2.f),
	walkingSpeed("Walking Speed", 1.f, 30.f, 10.f, 1.f){
	//Add the property to the model's GroupProperty, which is a group of properties that's a property of every Model.
	properties.add(&upperLegAngle);
	properties.add(&headY);
	properties.add(&headZ);
	properties.add(&legLength);
	properties.add(&legThickness);
	properties.add(&eyeAngle);
	properties.add(&raiseFrontLegs);
	properties.add(&walk);
	properties.add(&numLegs);
	properties.add(&walkingSpeed);
	properties.add(&teapotMode);
	time = 0;
}

void Spider::tick() {
	time += walkingSpeed.getValue();
	time = time % ((int) walk.getMax());
	walk.setValue(time);
}

void Spider::draw() {
	const float PI = 3.14159265f;
	double bodyRadius = 1.0;
	double headRadius = bodyRadius / 2;
	double eyeRadius = headRadius / 4;

	// Here, modelview matrix is in world space
	glPushMatrix(); // save world space matrix
	// Still in world space

	//draw body
	double walkDistance = (walk.getValue() / 180.0) * legLength.getValue();
	if (upperLegAngle.getValue() >= 90.f) {
		walkDistance *= sin(upperLegAngle.getValue()* PI / 180.f);
	}
	glTranslated(walkDistance, 0, 0);
	double height = legLength.getValue() - legLength.getValue() * (cos(upperLegAngle.getValue() * PI / 180.f)) - 2;
	glTranslated(0.0, height, 0.0);
	if (teapotMode.getValue()) {
		glutSolidTeapot(bodyRadius);
	} else {
		drawSphere(bodyRadius);
	}

	glPushMatrix();

		// draw head and eyes
		glRotatef(headZ.getValue(), 0.f, 0.f, 1.f);
		glRotatef(headY.getValue(), 0.f, 1.f, 0.f);
		glTranslated(bodyRadius + headRadius, 0.0, 0.0);
		if (teapotMode.getValue()) {
			glutSolidTeapot(headRadius);
		} else {
			drawSphere(headRadius);
		}
		glPushMatrix();

		// draw left eye
		glRotated(eyeAngle.getValue(), 0, 1, 0);
		glRotated(10.0, 0, 0, 1);
		glTranslated(headRadius, 0.0, 0.0);
		glScaled(.5, .5, 1);
		if (teapotMode.getValue()) {
			glutSolidTeapot(eyeRadius);
		} else {
			drawSphere(eyeRadius);
		}

		glPopMatrix();

		// draw right eye
		glRotated(-eyeAngle.getValue(), 0, 1, 0);
		glRotated(10.0, 0, 0, 1);
		glTranslated(headRadius, 0.0, 0.0);
		glScaled(.5, .5, 1);
		if (teapotMode.getValue()) {
			glutSolidTeapot(eyeRadius);
		} else {
			drawSphere(eyeRadius);
		}

	glPopMatrix();
	
	// draw legs
	for (float i = 1.f; i <= numLegs.getValue(); i++) {
		glPushMatrix();
			// upper leg
			if (i == 1.f || i == numLegs.getValue()) {
				// raise upper front legs
				glRotatef(raiseFrontLegs.getValue() , 0.f, 0.f, 1.f);
			}
			float angle = (i / (numLegs.getValue() + 1)) * 360.f;
			glRotatef( angle, 0.f, 1.f, 0.f);
			glTranslated(bodyRadius, 0.0, 0.0);
			glRotatef(-upperLegAngle.getValue(), 0.f, 0.f, 1.f);
			// walk
			if ((int)i % 2 == 0) {
				glRotatef(walk.getValue(), 0.1f, 1.f, 0.1f);
			}
			else {
				glRotatef(-walk.getValue(), 0.1f, 1.f, 0.1f);
			}
			drawUprightCylinder(legLength.getValue(), 0, legThickness.getValue());
			glPushMatrix();

				//lower leg
				glTranslated(0.0, legLength.getValue(), 0.0);
				// walk
				if ((int)i % 2 == 0) {
					glRotatef(-walk.getValue(), 0.1f, 1.f, 0.1f);
				} else {
					glRotatef(walk.getValue(), 0.1f, 1.f, 0.1f);
				}
				
				glRotatef(upperLegAngle.getValue() + 180.0, 0.f, 0.f, 1.f);

				// raise lower front legs
				if (i == 1) {
					glRotatef(raiseFrontLegs.getValue(), 1.f, 0.f, 0.f);
				} else if (i == numLegs.getValue()) {
					glRotatef(-raiseFrontLegs.getValue(), 1.f, 0.f, 0.f);
				}
				drawUprightCylinder(legLength.getValue(), legThickness.getValue(), 0);
				if (teapotMode.getValue()) {
					glTranslated(0.0, legLength.getValue() - headRadius, 0.0);
					glRotatef(180.f, 0.f, 0.f, 1.f);
					glutSolidTeapot(headRadius);
				}

			glPopMatrix();
		glPopMatrix();
	}

	glPopMatrix();

	// Back in model space
	glPopMatrix(); // copy world space matrix into modelview matrix
	// Back in world space
}


static void drawUprightCylinder(double h, double r1, double r2) {
	glRotatef(-90.f, 1.f, 0.f, 0.f);
	drawCylinder(h, r1, r2);
	glRotatef(90.f, 1.f, 0.f, 0.f);
}