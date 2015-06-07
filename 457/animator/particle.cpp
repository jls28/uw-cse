#include "Particle.h"

Particle::Particle(Vec3d _p, Vec3d _v, Vec3d _f, float mass, int _type) :
p(_p), v(_v), f(_f), m(mass), type(_type)
{
	// yay everything's initialized already
}

Particle::~Particle() 
{
	//nothing to do...
}

void prettyVector(Vec3d v) {
	std::cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ") ";
}

void Particle::debug() {
	std::cout << "[";
	prettyVector(p);
	prettyVector(v);
	prettyVector(f);
	std::cout << "mass: " << m;
	std::cout << "]" << std::endl;
}