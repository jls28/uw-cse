#include "modelerview.h"
#include "modelerdraw.h"
#include "modelerui.h"
#include "vault.h"
#include "FL/glut.h"
#include "model.h"
#include <cmath>
#include <time.h>
#include "evilSpongebob.h"

static void drawUprightCylinder(double h, double r1, double r2);

EvilSpongebob::EvilSpongebob() : Model("Spongebob's Evil Twin"), legAngle("Leg Angle", 0.0f, 90.0f, 0.0f, 0.1f),
legRadius("Leg Radius", 0.0f, 1.0f, .125f, 0.005f), legLength("Leg Length", 0.0f, 10.0f, 2.0f, 0.1f),
armRadius("Arm Radius", 0.0f, 1.0f, .125f, 0.005f), armLength("Arm Length", 0.0f, 10.0f, 2.0f, 0.1f),
elbowAngle("Elbow Angle", 0.0f, 180.0f, 0.0f, 0.1f), shoulderZ("Rotate Shoulder Z", 0.0f, 180.0f, 0.0f, 0.1f),
shoulderX("Rotate Shoulder X", -180.f, 180.0f, 0.0f, 0.1f){
	//Add the property to the model's GroupProperty, which is a group of properties that's a property of every Model.
	properties.add(&legAngle);
	properties.add(&legRadius);
	properties.add(&legLength);
	properties.add(&armRadius);
	properties.add(&armLength);
	properties.add(&elbowAngle);
	properties.add(&shoulderZ);
	properties.add(&shoulderX);
}

void EvilSpongebob::draw() {
	// Here, modelview matrix is in world space
	glPushMatrix(); // save world space matrix
	// Still in world space

		// right lower leg
		glTranslated(1, -2, 0);
		glRotatef(legAngle.getValue(), 1.f, 0.f, 0.f);
		drawUprightCylinder(legLength.getValue(), 0, legRadius.getValue());
		glPushMatrix();
			// right upper leg
			glTranslated(0, legLength.getValue(), 0);
			glRotatef(-2 * legAngle.getValue(), 1.f, 0.f, 0.f);
			drawUprightCylinder(legLength.getValue(), legRadius.getValue(), legRadius.getValue());

		glPopMatrix();
	glPopMatrix();

	// lets add a middle leg!
	//glPushMatrix();
	//glTranslated(0, -2, 0);
	//	glRotatef(legAngle.getValue(), 1.f, 0.f, 0.f);
	//	drawUprightCylinder(legLength.getValue(), 0, legRadius.getValue());
	//	glPushMatrix();
	//		glTranslated(0, legLength.getValue(), 0);
	//		glRotatef(-2 * legAngle.getValue(), 1.f, 0.f, 0.f);
	//		drawUprightCylinder(legLength.getValue(), legRadius.getValue(), legRadius.getValue());
	//	
	//	glPopMatrix();
	//glPopMatrix();

	glPushMatrix();
		//left lower leg
		glTranslated(-1, -2, 0);
		glRotatef(legAngle.getValue(), 1.f, 0.f, 0.f);
		drawUprightCylinder(legLength.getValue(), 0, legRadius.getValue());
		glPushMatrix();
			// left upper leg
			glTranslated(0, legLength.getValue(), 0);
			glRotatef(-2 * legAngle.getValue(), 1.f, 0.f, 0.f);
			drawUprightCylinder(legLength.getValue(), legRadius.getValue(), legRadius.getValue());
			glPushMatrix();
				
				// draw body
				glTranslated(-.5, legLength.getValue(), -.5);
				glRotatef(legAngle.getValue(), 1.f, 0.f, 0.f);
				drawBox(3, 4, 1);
				glPushMatrix();

				// draw eyes
				glTranslated(1, 2.5, .7);
				glScalef(1.f, 1.5f, 1.f);
				drawSphere(.5);
				glTranslated(1, 0, 0);
				drawSphere(.5);
				glScalef(1.f, 1.0f / 1.5f, 1.f);
				glTranslated(-2, -2.5, -.7); //undo translate for eyes


					//draw right shoulder
					glTranslated(0, 3, .5);
					glRotatef(-shoulderZ.getValue(), 0.f, 0.f, 1.f);
					glRotatef(shoulderX.getValue(), 1.f, 0.f, 0.f);
					glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
					drawUprightCylinder(armLength.getValue(), armRadius.getValue(), armRadius.getValue());
					glPushMatrix();

						// draw right arm
						glTranslated(0, armLength.getValue(), 0);
						glRotatef(-elbowAngle.getValue(), 1.f, 0.f, 0.f);
						drawUprightCylinder(armLength.getValue(), armRadius.getValue(), 0);
						
					glPopMatrix();
				glPopMatrix();
				glPushMatrix();

					//draw left shoulder
					glTranslated(3, 3, .5);
					glRotatef(shoulderZ.getValue(), 0.f, 0.f, 1.f);
					glRotatef(shoulderX.getValue(), 1.f, 0.f, 0.f);
					glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
					drawUprightCylinder(armLength.getValue(), armRadius.getValue(), armRadius.getValue());
					glPushMatrix();

					// draw left arm
					glTranslated(0, armLength.getValue(), 0);
					glRotatef(-elbowAngle.getValue(), 1.f, 0.f, 0.f);
					drawUprightCylinder(armLength.getValue(), armRadius.getValue(), 0);

					glPopMatrix();

				glPopMatrix();
				

			glPopMatrix();
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