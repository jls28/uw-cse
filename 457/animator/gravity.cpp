/*
	Implementation for gravity.h
*/

#include "gravity.h"

Gravity::Gravity(Vec3d dir, double acc) : direction(dir), acceleration(acc) 
{
	direction.normalize();
}

Gravity::~Gravity()
{
	//literally do nothing
}

Vec3d Gravity::calcForce(Particle particle) 
{
	// F = ma
	// direction is normalized, so final force
	// will be properly distributed
	return direction * (particle.m * acceleration);
}

void Gravity::update(double newConst) {
	acceleration = newConst;
}