#include <cmath>

#include "light.h"

#include "../ui/TraceUI.h"
extern TraceUI* traceUI;


using namespace std;

//#define SINGLE_SIDED

double DirectionalLight::distanceAttenuation(const Vec3d& P, double dx, double dy) const
{
	// distance to light is infinite, so f(di) goes to 0.  Return 1.
	return 1.0;
}


Vec3d DirectionalLight::shadowAttenuation( const Vec3d& P, double dx, double dy ) const
{
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.
	// HINT: You can access the Scene using the getScene function inherited by Light object.
	
	//make new ray from P to light?
	Scene * scene = getScene();
	isect ret;
	Vec3d res = Vec3d(1, 1, 1);
	Vec3d d = getDirection(P, dx, dy);
	Vec3d point = P;
	bool didIntersect = scene->intersect(ray(point, d, ray::RayType::SHADOW), ret);
	while (didIntersect) {
		Vec3d kt = ret.getMaterial().kt(ret);
		if (kt.length2() == 0.0) {
			return Vec3d(0.0, 0.0, 0.0);
		}
		res = prod(res, kt);
		point = point + ret.t * d;
		didIntersect = scene->intersect(ray(point, d, ray::RayType::SHADOW), ret);
		// direction light will never get passed
	}
	return res;
}

Vec3d DirectionalLight::getColor() const
{
	return color;
}

Vec3d DirectionalLight::getDirection( const Vec3d& P, double dx, double dy ) const
{
	return -orientation;
}

double PointLight::distanceAttenuation(const Vec3d& P, double dx, double dy) const
{
	// YOUR CODE HERE

	// You'll need to modify this method to attenuate the intensity 
	// of the light based on the distance between the source and the 
	// point P.  For now, we assume no attenuation and just return 1.0
	// distance from light to point
	Vec3d pos = position;
	double lightArea = traceUI->getpointLightArea();
	if (lightArea > 0.0 && traceUI->getAntialiasingFactor() > 1.0) {
		Vec3d u = Vec3d(0.456, 1, .324) ^ (position - P);
		u.normalize();
		Vec3d v = u ^ (position - P);
		v.normalize();
		pos += (dx * u + dy * v) * lightArea;
	}
	double dist = (pos - P).length();

	return min(1.0, 1.0 / (constantTerm + linearTerm * dist + quadraticTerm * dist * dist));
}

Vec3d PointLight::getColor() const
{
	return color;
}

Vec3d PointLight::getDirection(const Vec3d& P, double dx, double dy) const
{
	Vec3d pos = position;
	double lightArea = traceUI->getpointLightArea();
	if (lightArea > 0.0 && traceUI->getAntialiasingFactor() > 1.0) {
		Vec3d u = Vec3d(0.456, 1, .324) ^ (position - P);
		u.normalize();
		Vec3d v = u ^ (position - P);
		v.normalize();
		pos += (dx * u + dy * v) * lightArea;
	}
	Vec3d ret = pos - P;
	ret.normalize();
	return ret;
}


Vec3d PointLight::shadowAttenuation(const Vec3d& P, double dx, double dy) const
{
    // YOUR CODE HERE:
    // You should implement shadow-handling code here.
	// HINT: You can access the Scene using the getScene function inherited by Light object.
	Scene * scene = getScene();
	isect ret;
	Vec3d res = Vec3d(1, 1, 1);
	Vec3d d = getDirection(P, dx, dy);
	Vec3d point = P;
	bool didIntersect = scene->intersect(ray(point, d, ray::RayType::SHADOW), ret);
	while (didIntersect) {
		if (getDirection(point + ret.t * d, dx, dy) * d < 0) {	// passed light
			didIntersect = false;
			continue;
		}
		Vec3d kt = ret.getMaterial().kt(ret);
		if (kt.length2() == 0.0) {
			return Vec3d(0.0, 0.0, 0.0);
		}
		res = prod(res, kt);
		point = point + ret.t * d;
		didIntersect = scene->intersect(ray(point, d, ray::RayType::SHADOW), ret);
	}
	return res;
}
