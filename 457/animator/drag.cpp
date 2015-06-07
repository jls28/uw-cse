/*
Implementation for drag.h
*/

#include "drag.h"

Drag::Drag(double constant) : dragConstant(constant)
{
	
}

Vec3d Drag::calcForce(Particle particle)
{
	// F = -k_drag * v
	return  -dragConstant * particle.v;
}

void Drag::update(double newConst) {
	dragConstant = newConst;
}