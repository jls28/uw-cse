#ifndef __RAYTRACER_H__
#define __RAYTRACER_H__

// The main ray tracer.

#include "scene/ray.h"

#define THREAD_CHUNKSIZE 32

class Scene;

class RayTracer
{
public:
    RayTracer();
    ~RayTracer();

    Vec3d trace( double x, double y, double dx, double dy, double t, Vec3d focalPoint);
	Vec3d traceRay( ray& r, const Vec3d& thresh, int depth, double dx, double dy, double t );


	void getBuffer( unsigned char *&buf, int &w, int &h );
	double aspectRatio();
	void traceSetup( int w, int h );
	void tracePixel( int i, int j );

	bool loadScene( const char* fn );

	bool sceneLoaded() { return scene != 0; }

    void setReady( bool ready )
      { m_bBufferReady = ready; }
    bool isReady() const
      { return m_bBufferReady; }

	const Scene& getScene() { return *scene; }

private:
	unsigned char *buffer;
	int buffer_width, buffer_height;
	int bufferSize;
	Scene* scene;

    bool m_bBufferReady;

};

#endif // __RAYTRACER_H__
