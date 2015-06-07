#include "modelerview.h"
#include "modelerdraw.h"
#include "modelerui.h"
#include "vault.h"
#include "FL/glut.h"
#include "model.h"
#include <cmath>
#include <time.h>

class EvilSpongebob : public Model {

protected:
	//Add the properties here 
	RangeProperty legAngle;
	RangeProperty legLength;
	RangeProperty legRadius;
	RangeProperty armLength;
	RangeProperty armRadius;
	RangeProperty elbowAngle;
	RangeProperty shoulderZ;
	RangeProperty shoulderX;
	
public:
	EvilSpongebob();
	void draw();
};