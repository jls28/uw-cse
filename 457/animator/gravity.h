/* Simple gravitational force
*  by default points -y with earth's gravity at sea level
*/

#ifndef INCLUDED_GRAVITY_H
#define INCLUDED_GRAVITY_H

#include "Force.h"
#include "vec.h"

class Gravity : public Force {
public:
	double acceleration;
	Vec3d direction;

	Gravity(Vec3d dir = Vec3d(0.0, -1.0, 0.0), double acc = 9.8);
	~Gravity();

	virtual Vec3d calcForce(Particle particle);
	virtual void update(double newConst);

};
#endif