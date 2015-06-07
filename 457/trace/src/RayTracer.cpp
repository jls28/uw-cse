// The main ray tracer.

#pragma warning (disable: 4786)

#include "RayTracer.h"
#include "scene/light.h"
#include "scene/material.h"
#include "scene/ray.h"

#include "parser/Tokenizer.h"
#include "parser/Parser.h"

#include "ui/TraceUI.h"
#include <cmath>
#include <algorithm>

extern TraceUI* traceUI;

#include <iostream>
#include <fstream>

using namespace std;

// Use this variable to decide if you want to print out
// debugging messages.  Gets set in the "trace single ray" mode
// in TraceGLWindow, for example.
bool debugMode = false;

static double frand(double min, double max);

// Trace a top-level ray through normalized window coordinates (x,y)
// through the projection plane, and out into the scene.  All we do is
// enter the main ray-tracing method, getting things started by plugging
// in an initial ray weight of (0.0,0.0,0.0) and an initial recursion depth of 0.
Vec3d RayTracer::trace( double x, double y, double dx, double dy, double t, Vec3d focalPoint )
{
	double apertureRadius = traceUI->getApertureRadius();
	// Clear out the ray cache in the scene for debugging purposes,
	if (!traceUI->isMultithreading())
		scene->intersectCache.clear();

    ray r( Vec3d(0,0,0), Vec3d(0,0,0), ray::VISIBILITY );

    scene->getCamera().rayThrough( x,y,r );
	if (apertureRadius > 0.0) {
		Vec3d eye = r.getPosition();
		Vec3d dir = r.getDirection();
		Vec3d u = Vec3d(0.456, 1, .324) ^ dir;
		u.normalize();
		Vec3d v = u ^ dir;
		Vec3d aperturePos = eye + apertureRadius * (dx + .5) * u + apertureRadius * (dy + .5) * v;
		Vec3d newDir = focalPoint - aperturePos;
		newDir.normalize();
		r = ray(aperturePos, newDir, ray::VISIBILITY);
	}
	
	int depth = traceUI->getDepth();

	Vec3d ret = traceRay( r, Vec3d(1.0,1.0,1.0), depth, dx, dy, t);

	return ret;
}

// Do recursive ray tracing!  You'll want to insert a lot of code here
// (or places called from here) to handle reflection, refraction, etc etc.
Vec3d RayTracer::traceRay( ray& r, 
	const Vec3d& thresh, int depth, double dx, double dy, double t )
{
	isect i;
	// depth == 0 means final bounce
	if (depth < 0) {
		return Vec3d(0, 0, 0);
	}
	if (thresh.length2() < traceUI->getThresh()) {
		return Vec3d(0, 0, 0);
	}
	if (depth == traceUI->getDepth()) {
		Vec3d displacement = t * Vec3d(traceUI->getMotionBlurX(), traceUI->getMotionBlurY(), traceUI->getMotionBlurZ());
		r = ray(r.getPosition() + displacement, r.getDirection(), r.type());
	}
	if( scene->intersect( r, i ) ) {
		// YOUR CODE HERE

		// An intersection occured!  We've got work to do.  For now,
		// this code gets the material for the surface that was intersected,
		// and asks that material to provide a color for the ray.  

		// This is a great place to insert code for recursive ray tracing.
		// Instead of just returning the result of shade(), add some
		// more steps: add in the contributions from reflected and refracted
		// rays.

		// make reflection ray and factor that in
		// make refraction ray and factor that in

		// reflection?!?
		
		// intersection point
		Vec3d intersectionPoint = r.at(i.t);

		// need angle of new ray (changes the direction
		// will be the normal + mirrored d (se lecture slides)
		Vec3d d = r.getDirection();
		const Material& m = i.getMaterial();
		double AIR_REFRACTIVE_INDEX = 1.0003;
		double n_i;
		double n_t;
		if (i.N * -d > 0)
		{
			// ray is entering an object
			n_i = AIR_REFRACTIVE_INDEX;
			n_t = m.index(i);
		}
		else
		{
			// ray is leaving the object
			i.setN(-i.N);
			n_i = m.index(i);
			n_t = AIR_REFRACTIVE_INDEX;
		}
		Vec3d n = i.N;

		// calculate soem trig stuff for refraction/fresnel reflection
		double cosTheta_i = n * -d;
		double refractRatio = n_i / n_t;
		double cosTheta_tSquared = 1 - (refractRatio * refractRatio) * (1 - (cosTheta_i * cosTheta_i));
		boolean tir = cosTheta_tSquared < 0;
		double cosTheta_t = sqrt(max(cosTheta_tSquared, 0.0));

		// calculate fresnel factor
		double fresnel = (n_i - n_t) / (n_i + n_t);
		fresnel *= fresnel;
		if (!tir) {
			fresnel = fresnel + (1 - fresnel) * (pow(1 - cosTheta_i, 2.0));
		} else {
			fresnel = 1;
		}

		// glossiness/translucency
		double glossiness = traceUI->getGlossiness();
		
		Vec3d reflectionDirection = 2 * (-d * n) * n + d;
		reflectionDirection.normalize();

		// handle glossiness
		Vec3d u = Vec3d(0.456, 1, .324) ^ reflectionDirection;
		u.normalize();
		Vec3d v = u ^ reflectionDirection;
		// compute random direction in the same "lobe" as reflectionDirection
		Vec3d randDir = glossiness*dx * u + glossiness*dy * v + reflectionDirection;
		if (n * randDir < 0) {
			randDir = -(randDir * u) * u - (randDir * v) * v + (randDir * reflectionDirection) * reflectionDirection;
		}
		randDir.normalize();
		if (traceUI->getAntialiasingFactor() > 1) {
			reflectionDirection = randDir;
		}
		

		Vec3d finalIllumination = m.shade(scene, r, i, dx, dy);
		ray reflectRay(intersectionPoint, reflectionDirection, ray::RayType::REFLECTION);
		Vec3d kr = m.kr(i);
		if (traceUI->getFresnelEnabled()) {
			kr *= fresnel;
		}
		finalIllumination += prod(kr, traceRay(reflectRay, prod(kr, thresh), depth - 1, dx, dy, t));
		
		// refraction time! :D
		if (!tir) {	// not total internal reflection
			Vec3d refractionDirection = (refractRatio * cosTheta_i - cosTheta_t) * n + refractRatio * d;
			refractionDirection.normalize();

			// handle translucency
			u = Vec3d(0.456, 1, .324) ^ refractionDirection;
			u.normalize();
			v = u ^ refractionDirection;
			// compute random direction in the same "lobe" as refractionDirection
			randDir = glossiness*dx * u + glossiness*dy * v + refractionDirection;
			if (n * randDir > 0) {
				randDir = -(randDir * u) * u - (randDir * v) * v + (randDir * refractionDirection) * refractionDirection;
			}
			randDir.normalize();
			if (traceUI->getAntialiasingFactor() > 1) {
				refractionDirection = randDir;
			}

			ray refractRay(intersectionPoint, refractionDirection, ray::RayType::REFRACTION);
			Vec3d kt = m.kt(i);
			if (traceUI->getFresnelEnabled()) {
				kt *= (1 - fresnel);
			}
			finalIllumination += prod(kt, traceRay(refractRay, prod(kt, thresh), depth - 1, dx, dy, t));
		}

		return finalIllumination;
	} else {
		// No intersection.  This ray travels to infinity, so we color
		// it according to the background color, which in this (simple) case
		// is just black.

		return Vec3d( 0.0, 0.0, 0.0 );
	}
}

RayTracer::RayTracer()
	: scene( 0 ), buffer( 0 ), buffer_width( 0 ), buffer_height( 0 ), m_bBufferReady( false )
{
}


RayTracer::~RayTracer()
{
	delete scene;
	delete [] buffer;
}

void RayTracer::getBuffer( unsigned char *&buf, int &w, int &h )
{
	buf = buffer;
	w = buffer_width;
	h = buffer_height;
}

double RayTracer::aspectRatio()
{
	return sceneLoaded() ? scene->getCamera().getAspectRatio() : 1;
}

bool RayTracer::loadScene( const char* fn )
{
	ifstream ifs( fn );
	if( !ifs ) {
		string msg( "Error: couldn't read scene file " );
		msg.append( fn );
		traceUI->alert( msg );
		return false;
	}
	
	// Strip off filename, leaving only the path:
	string path( fn );
	if( path.find_last_of( "\\/" ) == string::npos )
		path = ".";
	else
		path = path.substr(0, path.find_last_of( "\\/" ));

	// Call this with 'true' for debug output from the tokenizer
	Tokenizer tokenizer( ifs, false );
    Parser parser( tokenizer, path );
	try {
		delete scene;
		scene = 0;
		scene = parser.parseScene();
	} 
	catch( SyntaxErrorException& pe ) {
		traceUI->alert( pe.formattedMessage() );
		return false;
	}
	catch( ParserException& pe ) {
		string msg( "Parser: fatal exception " );
		msg.append( pe.message() );
		traceUI->alert( msg );
		return false;
	}
	catch( TextureMapException e ) {
		string msg( "Texture mapping exception: " );
		msg.append( e.message() );
		traceUI->alert( msg );
		return false;
	}


	if( ! sceneLoaded() )
		return false;


	// Initialize the scene's BSP tree
	scene->initBSPTree();

	
	return true;
}

void RayTracer::traceSetup( int w, int h )
{
	if( buffer_width != w || buffer_height != h )
	{
		buffer_width = w;
		buffer_height = h;

		bufferSize = buffer_width * buffer_height * 3;
		delete [] buffer;
		buffer = new unsigned char[ bufferSize ];

	}
	memset( buffer, 0, w*h*3 );
	m_bBufferReady = true;
}

void RayTracer::tracePixel( int i, int j )
{
	Vec3d color;
	int ANTIALIASING_FACTOR = traceUI->getAntialiasingFactor();
	double antialiasingDenom = 0;
	double centerX = double(i * ANTIALIASING_FACTOR + ANTIALIASING_FACTOR / 2) / double(buffer_width * ANTIALIASING_FACTOR);
	double centerY = double(j * ANTIALIASING_FACTOR + ANTIALIASING_FACTOR / 2) / double(buffer_height * ANTIALIASING_FACTOR);
	double focalDistance = traceUI->getFocalDistance();
	ray r(Vec3d(0, 0, 0), Vec3d(0, 0, 0), ray::VISIBILITY);
	scene->getCamera().rayThrough(centerX, centerY, r);
	Vec3d focalPoint = r.at(focalDistance);
	
	if( ! sceneLoaded() )
		return;
	for (int row = 0; row < ANTIALIASING_FACTOR; row++) {
		for (int col = 0; col < ANTIALIASING_FACTOR; col++) {

			double x = double(i * ANTIALIASING_FACTOR + col) / double(buffer_width * ANTIALIASING_FACTOR);
			double y= double(j * ANTIALIASING_FACTOR + row) / double(buffer_height * ANTIALIASING_FACTOR);
			double dx = double(col) / ANTIALIASING_FACTOR;
			double dy = double(row) / ANTIALIASING_FACTOR;
			double t = double(row * ANTIALIASING_FACTOR + col) / double(ANTIALIASING_FACTOR * ANTIALIASING_FACTOR);
			// jittering
			if (traceUI->getJitterEnabled()) {
				x += frand(-.5, .5) / double(buffer_width * ANTIALIASING_FACTOR);
				y += frand(-.5, .5) / double(buffer_height * ANTIALIASING_FACTOR);
				dx += frand(-.5, .5) / ANTIALIASING_FACTOR;
				dy += frand(-.5, .5) / ANTIALIASING_FACTOR;
				t += frand(-.5, .5) / double(ANTIALIASING_FACTOR * ANTIALIASING_FACTOR);
			}
			dx -= .5;
			dy -= .5;
			if (ANTIALIASING_FACTOR == 1) t = 0;
			color += trace(x, y, dx, dy, t, focalPoint);
			antialiasingDenom++;
		}
	}
	color /= antialiasingDenom;
	color.clamp();
	

	unsigned char *pixel = buffer + ( i + j * buffer_width ) * 3;

	pixel[0] = (int)( 255.0 * color[0]);
	pixel[1] = (int)( 255.0 * color[1]);
	pixel[2] = (int)( 255.0 * color[2]);
}

// random double between min and max
static double frand(double min, double max) {
	double f = (double)rand() / RAND_MAX;	// random num between 0 and 1
	return min + f * (max - min);
}

