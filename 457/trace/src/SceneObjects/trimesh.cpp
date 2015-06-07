#include <cmath>
#include <float.h>
#include "trimesh.h"

using namespace std;

Trimesh::~Trimesh()
{
	for( Materials::iterator i = materials.begin(); i != materials.end(); ++i )
		delete *i;
}

bool Trimesh::hasPerVertexNormals()
{
	return !(this->normals.empty());
}

bool Trimesh::hasPerVertexMaterials() {
	return !(this->materials.empty());
}

bool Trimesh::hasPerVertexTextureUVs(){
	return !(this->textureuvs.empty());
}

// must add vertices, normals, and materials IN ORDER
void Trimesh::addVertex( const Vec3d &v )
{
    vertices.push_back( v );
}

void Trimesh::addMaterial( Material *m )
{
    materials.push_back( m );
}

void Trimesh::addNormal( const Vec3d &n )
{
    normals.push_back( n );
}

void Trimesh::addTextureUV( const Vec2d &n )
{
    textureuvs.push_back( n );
}

// Returns false if the vertices a,b,c don't all exist
bool Trimesh::addFace( int a, int b, int c )
{
    int vcnt = vertices.size();

    if( a >= vcnt || b >= vcnt || c >= vcnt )
        return false;

    TrimeshFace *newFace = new TrimeshFace( scene, new Material(*this->material), this, a, b, c );
    newFace->setTransform(this->transform);
    faces.push_back( newFace );
    scene->add(newFace);
    return true;
}

char *
Trimesh::doubleCheck()
// Check to make sure that if we have per-vertex materials or normals
// they are the right number.
{
    if( !materials.empty() && materials.size() != vertices.size() )
        return "Bad Trimesh: Wrong number of materials.";
    if( !normals.empty() && normals.size() != vertices.size() )
        return "Bad Trimesh: Wrong number of normals.";

    return 0;
}

// Calculates and returns the normal of the triangle too.
bool TrimeshFace::intersectLocal( const ray& r, isect& i ) const
{
    // YOUR CODE HERE:
    // Add triangle intersection code here.
    // it currently ignores all triangles and just return false.
    //
    // Note that you are only intersecting a single triangle, and the vertices
    // of the triangle are supplied to you by the trimesh class.
    //
    // You should retrieve the vertices using code like this:
    //
    // const Vec3d& a = parent->vertices[ids[0]];
    // const Vec3d& b = parent->vertices[ids[1]];
    // const Vec3d& c = parent->vertices[ids[2]];
	//
	// TrimeshFace::parent->hasPerVertexNormals tells you if the triangle has per-vertex normals.
	// If it does, you should compute and return the interpolated normal at the intersection point.
	// If it does not, you should return the normal of the triangle's supporting plane.
	// 
	Vec3d p = r.getPosition();
	Vec3d d = r.getDirection();

	const Vec3d& a = parent->vertices[ids[0]];
	const Vec3d& b = parent->vertices[ids[1]];
	const Vec3d& c = parent->vertices[ids[2]];
	Vec3d planeNormal = (b - a) ^ (c - a);
	planeNormal.normalize();
	double den = planeNormal * d;
	if (den == 0.0) {
		return false;
	}
	double t = ((planeNormal * a) - (planeNormal * p)) / den;
	if (t <= RAY_EPSILON) {
		return false;
	}
	// point of intersection
	Vec3d q = p + t * d;
	bool insideTriangle = ((b - a) ^ (q - a)) * planeNormal >= 0
		&& ((c - b) ^ (q - b)) * planeNormal >= 0
		&& ((a - c) ^ (q - c)) * planeNormal >= 0;
	if (!insideTriangle) {
		return false;
	}
	i.setT(t);
	i.obj = this;
	double totalArea = ((b - a) ^ (c - b)).length() / 2;
	double qbcArea = ((b - q) ^ (c - b)).length() / 2;
	double aqcArea = ((q - a) ^ (c - q)).length() / 2;
	double alpha = qbcArea / totalArea;
	double beta = aqcArea / totalArea;
	double gamma = 1.0 - alpha - beta;
	if (TrimeshFace::parent->hasPerVertexNormals()) {
		const Vec3d& aNorm = parent->normals[ids[0]];
		const Vec3d& bNorm = parent->normals[ids[1]];
		const Vec3d& cNorm = parent->normals[ids[2]];
		Vec3d n = alpha * aNorm + beta * bNorm + gamma * cNorm;
		n.normalize();
		i.setN(n);
	}
	else {
		i.setN(planeNormal);
	}
	if (TrimeshFace::parent->hasPerVertexMaterials()) {
		const Material* aMat = parent->materials[ids[0]];
		const Material* bMat = parent->materials[ids[1]];
		const Material* cMat = parent->materials[ids[2]];
		Material m = alpha * (*aMat);
		m += beta * (*bMat);
		m += gamma * (*cMat);
		i.setMaterial(m);
	}
	return true;
}


void
Trimesh::generateNormals()
// Once you've loaded all the verts and faces, we can generate per
// vertex normals by averaging the normals of the neighboring faces.
{
    int cnt = vertices.size();
    normals.resize( cnt );
    int *numFaces = new int[ cnt ]; // the number of faces assoc. with each vertex
    memset( numFaces, 0, sizeof(int)*cnt );
    
    for( Faces::iterator fi = faces.begin(); fi != faces.end(); ++fi )
    {
        Vec3d a = vertices[(**fi)[0]];
        Vec3d b = vertices[(**fi)[1]];
        Vec3d c = vertices[(**fi)[2]];
        
        Vec3d faceNormal = ((b-a) ^ (c-a));
		faceNormal.normalize();
        
        for( int i = 0; i < 3; ++i )
        {
            normals[(**fi)[i]] += faceNormal;
            ++numFaces[(**fi)[i]];
        }
    }

    for( int i = 0; i < cnt; ++i )
    {
        if( numFaces[i] )
		{
            normals[i]  /= numFaces[i];
			if (normals[i].length() != 0)
			{
				normals[i].normalize();
			}
		}
    }

    delete [] numFaces;
}

