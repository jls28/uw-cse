#ifndef INCLUDED_FORCE_H
#define INCLUDED_FORCE_H

/* Force class
*  All forces take a particle and return 
*  the force it applies to that particle
*/

#include "vec.h"
#include "Particle.h"

class Force {
public:
	virtual Vec3d calcForce(Particle particle) 
	{
		std::cout << "you shouldn't see this, subclass force fool" << std::endl;
		return Vec3d(0.0, 0.0, 0.0);
	}

	virtual void update(double newConst) {
		return;
	}
};
#endif
