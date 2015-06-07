#include "modelerview.h"
#include "modelerdraw.h"
#include "modelerui.h"
#include "vault.h"
#include "FL/glut.h"
#include "model.h"
#include <cmath>
#include <time.h>

Mat4f getModelViewMatrix();

class Spider : public Model {

protected:
	//Add the properties here 
	RangeProperty upperLegAngle;
	RangeProperty headZ;
	RangeProperty headY;
	RangeProperty legLength;
	RangeProperty legThickness;
	RangeProperty eyeAngle;
	RangeProperty raiseLeftFrontLeg;
	RangeProperty raiseRightFrontLeg;
	RangeProperty walk;
	RangeProperty numLegs;
	RangeProperty walkingSpeed;
	RangeProperty teapotMode;
	RangeProperty rotateX, rotateY, rotateZ;
	RangeProperty translateX, translateY, translateZ;
	RangeProperty squashX, squashY, squashZ;
	Mat4f CameraTransforms;
	int time;

	ParticleSystem ps;
	void SpawnParticles();

public:
	Spider();
	void draw();
	void tick();
	ParticleSystem* getParticleSystem();
	void setCameraTransforms(Mat4f CameraTransforms);
};