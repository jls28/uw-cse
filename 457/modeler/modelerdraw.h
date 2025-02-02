// modelerdraw.h

// Contains object and routines related to rendering things

#ifndef MODELERDRAW_H
#define MODELERDRAW_H

#include <GL/glew.h>
#include <FL/gl.h>
#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include <vector>

enum DrawModeSetting_t 
{ NONE=0, NORMAL, WIREFRAME, FLATSHADE, };

enum QualitySetting_t 
{ HIGH, MEDIUM, LOW, POOR, };

// The ModelerDrawState just keeps 
// information about the current color, etc, etc.
class ModelerDrawState
{
public: 
	static ModelerDrawState* Instance();

	FILE* m_rayFile;

	DrawModeSetting_t m_drawMode;
	QualitySetting_t  m_quality;

	GLfloat m_ambientColor[4];
	GLfloat m_diffuseColor[4];
	GLfloat m_specularColor[4];
	GLfloat m_emissiveColor[4];
	GLfloat m_shininess;

	bool showMarkers;

private:
	ModelerDrawState();
	ModelerDrawState(const ModelerDrawState &) {}
	ModelerDrawState& operator=(const ModelerDrawState&) {}

	static ModelerDrawState *m_instance;
};

/**
 * Prints a string at the current raster position, which can be set using
 * glRasterPos3f(x,y,z), where (x,y,z) is the point in your scene where
 * you want text to appear around.
 */
void printString(char *s);

/** Draws axes. */
void drawAxes();

// ****************************************************************************
// DRAWING FUNCTIONS
//
// The following functions are for your use in Modeler.  You don't *need* to
// use these functions; however, if you desire to output your model for
// the raytracer project (in .ray file format), you must either call these
// functions or implement the appropriate functionality so that the raytracer
// can handle it.
//
// Note:  Depending on whether a ray file is open or closed, these functions
//        will either output to a ray file or make OpenGL calls.
// ****************************************************************************

// Set the current material properties
void setAmbientColor(float r, float g, float b);
void setDiffuseColor(float r, float g, float b);
void setSpecularColor(float r, float g, float b);
void setEmissiveColor(float r, float g, float b);
void setShininess(float s);

// Set the current draw mode (see DrawModeSetting_t for valid values
void setDrawMode(DrawModeSetting_t drawMode);

// Set the current quality mode (See QualityModeSetting_t for valid values
void setQuality(QualitySetting_t quality);

// Opens a .ray file for writing, returns false on error
bool openRayFile(const char rayFileName[]);
// Closes the current .ray file if one exists
void closeRayFile();

/////////////////////////////
// Raytraceable Primitives //
/////////////////////////////

// Draw a sphere of radius r
void drawSphere(double r);

typedef struct tag_POINT_2D {
	float x;
	float y;
} Point2d;

// load a list of 2d points from a file
int load_2dcurve_txt(char* filename,std::vector<Point2d>* pts, std::vector<Point2d>* pts_2, std::vector<Point2d>* pts_3, std::vector<Point2d>* pts_4);
// Surface of revolution
void drawRevolution(double scale, boolean showNormals);
void drawRevolution(std::vector<Point2d> *pts, int divisions, double scale);

// Draw an axis-aligned box from origin to (x,y,z)
void drawBox( double x, double y, double z );

// Draw a cylinder from z=0 to z=h with radius r1 at origin and r2 at z=h
void drawCylinder( double h, double r1, double r2 );

// Triangle with three given vertices.  Specify in counterclockwise direction.
void drawTriangle( double x1, double y1, double z1,
			       double x2, double y2, double z2,
			       double x3, double y3, double z3 );

void init_load_curve_file();
int reload_curve_file(const char* filename);

#endif
