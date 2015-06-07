#pragma warning(disable : 4786)

#include "particleSystem.h"
#include "modelerui.h"
#include "Force.h"
#include "gravity.h"
#include "drag.h"

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <limits>

using namespace std;

#define BALL_SPAWN_TIME 10
#define SNOW_SPAWN_COUNT 10

static float prevT;

static double frand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() : restitutionSlider("Restitution", 0.0f, 2.0f, 1.0f, 0.1f), 
texture("snow.jpg"), dragSlider("Drag", 0.0f, 0.5f, 0.05f, 0.01f), includeSnow(false),
gravSlider("Gravity", 0.0f, 20.0f, 9.8f, 0.1f)
{
	// YOUR CODE HERE
	num_particles = 0;
	tick = 0;
	deltaT = 0;
	particle_origin_prev = particle_origin = Vec3d(0.0, 0.0, 0.0);
	particle_direction = Vec3d(1.0, 0.0, 0.0);

	particles = new std::vector<Particle>;
	forces = new std::vector<Force*>;
	Gravity * g = new Gravity(Vec3d(0.0, -1.0, 0.0), gravSlider.getValue());
	Drag *d = new Drag(dragSlider.getValue());
	forces->push_back(g);
	forces->push_back(d);

	// Leave these here; the UI needs them to work correctly.
	dirty = false;
	simulate = false;
}




/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	// TODO
	delete particles;
	for (int i = 0; i < forces->size(); i++) {
		delete forces->at(i);
	}
	delete forces;
}


/******************
 * Simulation fxns
 ******************/

void ParticleSystem::setParticleOrigin(Vec3d origin) {
	if (particle_origin.length() == 0 && particle_origin_prev.length() == 0) {
		particle_origin_prev = origin;
	} else {
		particle_origin_prev = particle_origin;
	}
	particle_origin = origin;
}

void ParticleSystem::setParticleDirection(Vec3d direction) {
	particle_direction = direction;
	particle_direction.normalize();
}

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
	// YOUR CODE HERE

	// These values are used by the UI ...
	// negative bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.

	// if we want to be continuously adding particles, add them here 
	// WILL BE CALLED AT EVERY STEP

	// add particles every once in a while
	Vec3d emitterVelocity;
	if (deltaT > 0) {
		emitterVelocity = (particle_origin - particle_origin_prev) / deltaT;
	} else {
		emitterVelocity = Vec3d(0.0, 0.0, 0.0);
	}
	if (tick % BALL_SPAWN_TIME == 0) {
		/*particles->push_back(Particle(
			particle_origin,
			(3.0 * particle_direction + emitterVelocity),
			Vec3d(0.0, 0.0, 0.0),
			1.0,
			BALL));
		num_particles++;*/
	}

	// add snow particles
	if (includeSnow) {
		/*for (int i = 0; i < SNOW_SPAWN_COUNT; i++) {
			double x = frand(-10.0, 10.0);
			double z = frand(-10.0, 10.0);
			particles->push_back(Particle(
				Vec3d(x, 20.0, z),
				Vec3d(0.0, 0.0, 0.0),
				Vec3d(0.0, 0.0, 0.0),
				.05,
				SNOW));
			num_particles++;
		}*/
	}
	

	tick++;

	bake_end_time = -1;
	simulate = true;
	dirty = true;

}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
	// YOUR CODE HERE
	particles->clear();
	num_particles = 0;

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
	// YOUR CODE HERE
	particles->clear();
	num_particles = 0;

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{
	// YOUR CODE HERE

	deltaT = t - prevT;
	
	double collisionEpsilon = 0.0001;
	Vec3d bottomPlaneNormal(0.0, 1.0, 0.0);
	Vec3d bottomPlanePos(0.0, -1.5, 0.0);
	// for each particle
	for (int i = 0; i < particles->size(); i++) {
		// clear current force
		Particle cur = particles->at(i);
		if (cur.type == SNOW && !includeSnow) {
			continue;
		}

		Vec3d oldAcceleration = cur.f / cur.m;

		cur.f = Vec3d(0.0, 0.0, 0.0);
		// accumulate forces
		for (int j = 0; j < forces->size(); j++) {
			if (j == 0) { // gravity
				forces->at(j)->update(gravSlider.getValue());
			} else if (j == 1) { // drag
				forces->at(j)->update(dragSlider.getValue());
				//cout << "drag: " << forces->at(j)->calcForce(cur) << endl;
				//cout << "velocity: " << cur.v << endl;
			}
			cur.f += forces->at(j)->calcForce(cur);
		}
		
		// calculate new acceleration and velocity from forces
		Vec3d newAcceleration = cur.f / cur.m;
		Vec3d newVelocity = cur.v + deltaT * newAcceleration;
		Vec3d newPosition = cur.p + deltaT * cur.v;
		// ==== Calculating intersection goes here ====
		
		double restitution = restitutionSlider.getValue(); //aka bounciness
		if (cur.type == SNOW) {
			restitution = 0;
		}

		// Plane intersection
		if (newVelocity * bottomPlaneNormal < 0 &&
			(newPosition - bottomPlanePos) * bottomPlaneNormal <= collisionEpsilon) {
			Vec3d normalProjection = (bottomPlaneNormal * newVelocity) * bottomPlaneNormal;
			newVelocity = newVelocity - normalProjection - restitution * normalProjection;
		}
		
		// Sphere intersection
		// oh shit lol idk math
		// collisionSpherePosition vector and collisionSphereRadius double are available for u now tho
		Vec3d sphereNormal = newPosition - collisionSpherePosition;
		double radialDistance = sphereNormal.length();
		sphereNormal.normalize();
		if (newVelocity * sphereNormal < 0 &&
			(radialDistance <= collisionEpsilon + collisionSphereRadius)) {
			Vec3d normalProjection = (sphereNormal * newVelocity) * sphereNormal;
			newVelocity = newVelocity - normalProjection - restitution * normalProjection;
		}

		// Update with new particle
		particles->at(i) = Particle(
			newPosition,
			newVelocity,
			cur.f,
			cur.m,
			particles->at(i).type
			);
		//particles->at(i).debug();
	}


	//std::cout << "particles.size : " << particles->size() << std::endl;

	// Debugging info
	/*if( t - prevT > .08 )
		printf("(!!) Dropped Frame %lf (!!)\n", t-prevT);*/
	prevT = t;
}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{
	// YOUR CODE HERE
	//std::cout << "drew a particle" << std::endl;
	if (simulate) {
		startSimulation(t);
		for (int i = 0; i < particles->size(); ++i)
		{
			glPushMatrix();
			Vec3d p = particles->at(i).p;
			int type = particles->at(i).type;
			glTranslatef(GLfloat(p[0]), GLfloat(p[1]), GLfloat(p[2]));
			if (type == BALL) {
				// Stop applying textures to objects
				glBindTexture(GL_TEXTURE_2D, 0);
				GLUquadricObj *quadric;
				quadric = gluNewQuadric();

				gluQuadricDrawStyle(quadric, GLU_FILL);
				gluSphere(quadric, .2, 36, 18);

				gluDeleteQuadric(quadric);
			} else if (type == SNOW) {
				if (includeSnow) {
					// use snow texture
					texture.use();
					glEnable(GL_BLEND);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE);


					float modelview[16];

					glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

					// undo rotation/scaling
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							if (i == j) {
								modelview[i * 4 + j] = 1.0;
							}
							else {
								modelview[i * 4 + j] = 0.0;
							}
						}
					}

					glLoadMatrixf(modelview);

					glBegin(GL_QUADS);
					glTexCoord2f(0.0, 0.0);
					glVertex3f(-.05, -0.05, 0.0);
					glTexCoord2f(1.0, 0.0);
					glVertex3f(0.05, -.05, 0.0);
					glTexCoord2f(1.0, 1.0);
					glVertex3f(0.05, 0.05, 0.0);
					glTexCoord2f(0.0, 1.0);
					glVertex3f(-0.05, 0.05, 0.0);
					glEnd();
					glDisable(GL_BLEND);
				}
			}

			glPopMatrix(); 
		}
	}
}




/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{
	// TODO (baking is extra credit)
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
	// TODO (baking is extra credit)
	particles->clear();
	num_particles = 0;
}




