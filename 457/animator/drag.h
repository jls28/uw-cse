/* Simple drag force
*/

#ifndef INCLUDED_DRAG_H
#define INCLUDED_DRAG_H

#include "Force.h"
#include "vec.h"

class Drag : public Force {
public:

	double dragConstant;

	Drag(double constant = 5.0);
	~Drag();

	virtual Vec3d calcForce(Particle particle);
	virtual void update(double newConst);

};
#endif