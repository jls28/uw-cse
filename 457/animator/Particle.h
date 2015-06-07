/* Particle class
*  represents a particle
*  position vector, velocity vector, force vector, and mass float 
*/
#ifndef INCLUDED_PARTICLE_H
#define INCLUDED_PARTICLE_H

#include "vec.h"

#define BALL 0
#define SNOW 1

class Particle {
public:
	
	// Constructors
	Particle(Vec3d _p = Vec3d(0.0, 0.0, 0.0),
			 Vec3d _v = Vec3d(0.0, 0.0, 0.0), 
			 Vec3d _f = Vec3d(0.0, 0.0, 0.0), 
			 float _m = 1.0,
			 int _type = BALL);
	~Particle();

	// Position vector
	Vec3d p;
	// Velocity vector
	Vec3d v;
	// Force vector
	Vec3d f;
	// Mass
	float m;
	int type;

	void debug();
};
#endif