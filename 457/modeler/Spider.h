#include "modelerview.h"
#include "modelerdraw.h"
#include "modelerui.h"
#include "vault.h"
#include "FL/glut.h"
#include "model.h"
#include <cmath>
#include <time.h>

class Spider : public Model {

protected:
	//Add the properties here 
	RangeProperty upperLegAngle;
	RangeProperty headZ;
	RangeProperty headY;
	RangeProperty legLength;
	RangeProperty legThickness;
	RangeProperty eyeAngle;
	RangeProperty raiseFrontLegs;
	RangeProperty walk;
	RangeProperty numLegs;
	RangeProperty walkingSpeed;
	BooleanProperty teapotMode;
	int time;

public:
	Spider();
	void draw();
	void tick();
};