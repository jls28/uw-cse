#include <cmath>

#include "Sphere.h"

using namespace std;


bool Sphere::intersectLocal( const ray& r, isect& i ) const
{
    // YOUR CODE HERE:
    // Add sphere intersection code here.
    // it currently ignores all spheres and just return false.

	Vec3d p = r.getPosition();
	Vec3d d = r.getDirection();

	double a = d.length2();
	double b = 2 * (p * d);
	double c = p.length2() - 1.0;

	double discr = b * b - 4 * a * c;
	if (discr <= 0.0) {
		return false;
	}
	double root1 = (-b + sqrt(discr)) / (2 * a);
	double root2 = (-b - sqrt(discr)) / (2 * a);
	root1 = max(RAY_EPSILON, root1);
	root2 = max(RAY_EPSILON, root2);
	double result = min(root1, root2);
	if (result == RAY_EPSILON) {
		result = max(root1, root2);
	}
	if (result == RAY_EPSILON) {
		return false;
	} else {
		i.obj = this;
		i.setT(result);
		Vec3d normal = p + result * d;
		normal.normalize();
		i.setN(normal);
		return true;
	}
}

