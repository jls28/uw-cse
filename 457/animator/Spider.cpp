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

Spider::Spider() : Model("Spider"), upperLegAngle("Spider Squats", 0.f, 160.f, 20.f, 1.f),
	headY("Move Head Y", -20.f, 20.f, 0.f, 1.f), headZ("Move Head Z", -60.f, 60.f, 0.f, 1.f),
	legLength("Leg Length", .5, 10, 4.f, .1f), legThickness("Leg Thickness", 0, .5, .125f, .005f),
	eyeAngle("Eye Distance", 0.f, 50.f, 30.f, 1.f), raiseLeftFrontLeg("Raise Left Front Leg", 0.f, 80.f, 0.f, 1.f), raiseRightFrontLeg("Raise Right Front Leg", 0.f, 80.f, 0.f, 1.f),
	walk("Walk", 0.f, 1800.f, 0.f, 1.f), teapotMode("Teapot Mode:", 0.0f, 1.0f, 0.0f, 1.0f), numLegs("Number of Legs", 2.f, 30.f, 8.f, 2.f),
	walkingSpeed("Walking Speed", 1.f, 30.f, 10.f, 1.f), rotateX("Rotate Spider X", -180, 180, 0, 1),
	rotateY("Rotate Spider Y", -180, 180, 0, 1), rotateZ("Rotate Spider Z", -180, 180, 0, 1), translateX("Translate Spider X", -30, 30, 0, 1),
	translateY("Translate Spider Y", -5, 15, 0, 1), translateZ("Translate Spider Z", -30, 30, 0, 1), squashX("Squash Spider X", .25f, 4.0f, 1.0f, .01f),
	squashY("Squash Spider Y", .25f, 4.0f, 1.0f, .01f), squashZ("Squash Spider Z", .25f, 4.0f, 1.0f, .01f){
	//Add the property to the model's GroupProperty, which is a group of properties that's a property of every Model.
	properties.add(&upperLegAngle);
	properties.add(&headY);
	properties.add(&headZ);
	properties.add(&legLength);
	properties.add(&legThickness);
	properties.add(&eyeAngle);
	properties.add(&raiseRightFrontLeg);
	properties.add(&raiseLeftFrontLeg);
	properties.add(&walk);
	properties.add(&numLegs);
	properties.add(&walkingSpeed);
	properties.add(&teapotMode);
	properties.add(&rotateX);
	properties.add(&rotateY);
	properties.add(&rotateZ);
	properties.add(&translateX);
	properties.add(&translateY);
	properties.add(&translateZ);
	properties.add(&squashX);
	properties.add(&squashY);
	properties.add(&squashZ);
	time = 0;
}

void Spider::tick() {
	time += walkingSpeed.getValue();
	time = time % ((int) walk.getMax());
	walk.setValue(time);
}

ParticleSystem* Spider::getParticleSystem() {
	return &ps;
}

void Spider::draw() {
	const float PI = 3.14159265f;
	double bodyRadius = 1.0;
	double headRadius = bodyRadius / 2;
	double eyeRadius = headRadius / 4;
	int legs = numLegs.getValue();
	numLegs.setValue(legs - (legs % 2));

	// Here, modelview matrix is in world space
	glPushMatrix(); // save world space matrix
	// Still in world space

	// Translations
	glTranslated(translateX.getValue(), translateY.getValue(), translateZ.getValue());

	// Rotate around the X-axis
	glRotatef(rotateX.getValue(), 1, 0, 0);

	// Rotate around the Y-axis
	glRotatef(rotateY.getValue(), 0, 1, 0);

	// Rotate around the Z-axis
	glRotatef(rotateZ.getValue(), 0, 0, 1);

	glScaled(squashX.getValue(), squashY.getValue(), squashZ.getValue());

	//draw body
	double walkDistance = (walk.getValue() / 180.0) * legLength.getValue();
	if (upperLegAngle.getValue() >= 90.f) {
		walkDistance *= sin(upperLegAngle.getValue()* PI / 180.f);
	}
	//glTranslated(walkDistance, 0, 0);
	double height = legLength.getValue() - legLength.getValue() * (cos(upperLegAngle.getValue() * PI / 180.f)) - 2;
	glTranslated(0.0, height, 0.0);
	if (teapotMode.getValue() > .5) {
		glutSolidTeapot(bodyRadius);
	} else {
		drawSphere(bodyRadius);
	}

	glPushMatrix();

		// draw head and eyes
		glRotatef(headZ.getValue(), 0.f, 0.f, 1.f);
		glRotatef(headY.getValue(), 0.f, 1.f, 0.f);
		glTranslated(bodyRadius + headRadius, 0.0, 0.0);
		if (teapotMode.getValue() > .5) {
			glutSolidTeapot(headRadius);
		} else {
			drawSphere(headRadius);
		}
		glPushMatrix();

			//set up particle system at mouth
			glRotated(-30.0, 0, 0, 1);
			glTranslated(headRadius, 0.0, 0.0);
			SpawnParticles();

		glPopMatrix();
		glPushMatrix();

			// draw left eye
			glRotated(eyeAngle.getValue(), 0, 1, 0);
			glRotated(10.0, 0, 0, 1);
			glTranslated(headRadius, 0.0, 0.0);
			glScaled(.5, .5, 1);
			if (teapotMode.getValue() > .5) {
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
			if (teapotMode.getValue() > .5) {
				glutSolidTeapot(eyeRadius);
			} else {
				drawSphere(eyeRadius);
			}

	glPopMatrix();
	
	// draw legs
	for (float i = 1.f; i <= numLegs.getValue(); i++) {
		glPushMatrix();
			// upper leg
			if (i == 1.f) {
				// raise upper front legs
				glRotatef(raiseLeftFrontLeg.getValue() , 0.f, 0.f, 1.f);
			} else if (i == numLegs.getValue()) {
				// raise upper front legs
				glRotatef(raiseRightFrontLeg.getValue(), 0.f, 0.f, 1.f);
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
					glRotatef(raiseLeftFrontLeg.getValue(), 1.f, 0.f, 0.f);
				} else if (i == numLegs.getValue()) {
					glRotatef(-raiseRightFrontLeg.getValue(), 1.f, 0.f, 0.f);
				}
				drawUprightCylinder(legLength.getValue(), legThickness.getValue(), 0);
				if (teapotMode.getValue() > .5) {
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

Mat4f getModelViewMatrix()
{
	/**************************
	**
	**	GET THE OPENGL MODELVIEW MATRIX
	**
	**	Since OpenGL stores it's matricies in
	**	column major order and our library
	**	use row major order, we will need to
	**	transpose what OpenGL gives us before returning.
	**
	**	Hint:  Use look up glGetFloatv or glGetDoublev
	**	for how to get these values from OpenGL.
	**
	*******************************/

	GLfloat m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	Mat4f matMV(m[0], m[1], m[2], m[3],
		m[4], m[5], m[6], m[7],
		m[8], m[9], m[10], m[11],
		m[12], m[13], m[14], m[15]);

	return matMV.transpose(); // convert to row major
}

void Spider::setCameraTransforms(Mat4f CameraTransforms) {
	this->CameraTransforms = CameraTransforms;
}

void Spider::SpawnParticles()
{
	/****************************************************************
	**
	**	THIS FUNCTION WILL ADD A NEW PARTICLE TO OUR WORLD
	**
	**	Suppose we want particles to spawn from a the model's arm.
	**	We need to find the location of the model's arm in world
	**  coordinates so that we can set the initial position of new
	**  particles.	As discussed on the Animator project page,
	**  all particle positions should be in world coordinates.
	**
	**  At this point in execution, the MODELVIEW matrix contains the
	**  camera transforms multiplied by some model transforms.  In other words,
	**
	**  MODELVIEW = CameraTransforms * ModelTransforms
	**
	**	We are interested only in ModelTransforms, which is the
	**  transformation that will convert a point from the current, local
	**  coordinate system to the world coordinate system.
	**
	**	To do this, we're going to "undo" the camera transforms from the
	**  current MODELVIEW matrix.  The camera transform is passed in as
	**  a parameter to this function (remember when we saved it
	**  near the top of the model's draw method?).  We can "undo" the
	**  camera transforms by pre-multiplying the current MODELVIEW matrix
	**  with the inverse of the camera matrix.  In other words,
	**
	**  ModelTransforms = InverseCameraTransforms * MODELVIEW
	**
	********************************************************************/
		//... Get the current MODELVIEW matrix.
		//... "Undo" the camera transforms from the MODELVIEW matrix
		//... by multiplying Inverse(CameraTransforms) * CurrentModelViewMatrix.
		//... Store the result of this in a local variable called WorldMatrix.
		Mat4f WorldMatrix = CameraTransforms.inverse() * getModelViewMatrix();
		Mat3f WorldMatrix3d = WorldMatrix.upper33();


		/*****************************************************************
		**
		**	At this point, we have the transformation that will convert a point
		**  in the local coordinate system to a point in the world coordinate
		**  system.
		**
		**  We need to find the actual point in world coordinates
		**  where particle should be spawned.  This is simply
		**  "the origin of the local coordinate system" transformed by
		**  the WorldMatrix.
		**
		******************************************************************/
		//...
		//... WorldPoint = WorldMatrix * Vector(0, 0, 0, 1)
		//...
		Vec3f WorldPoint = WorldMatrix * Vec3f(0, 0, 0);
		Vec3d WorldPointd = Vec3d(WorldPoint[0], WorldPoint[1], WorldPoint[2]);
		// errors when using 4d vectors for some reason
		Vec3f WorldParticleDirection = WorldMatrix3d * Vec3f(1, 0, 0);
		WorldParticleDirection.normalize();
		Vec3d WorldParticleDirectiond = Vec3d(WorldParticleDirection[0], WorldParticleDirection[1], WorldParticleDirection[2]);

		/*****************************************************************
		**
		**	Now that we have the particle's initial position, we
		**  can finally add it to our system!
		**
		***************************************************************/
		//...
		//...	AddParticleStartingAt(WorldPoint)
		//...
		ps.setParticleOrigin(WorldPointd);
		ps.setParticleDirection(WorldParticleDirectiond);

		return;

}