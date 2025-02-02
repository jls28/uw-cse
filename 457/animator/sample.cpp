// The sample box model.  You should build a file
// very similar to this for when you make your model in
// order to plug in to the animator project.

#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning (disable : 4786)
#pragma warning (disable : 4312)


#include "modelerview.h"
#include "modelerdraw.h"
#include "modelerui.h"
#include "vault.h"
#include "FL/glut.h"
#include "model.h"
#include "cameras.h"
#include <cmath>
#include <time.h>
#include "Spider.h"

#define ADDITIONAL_SPIDERS 1


void ground(float h);
void base(float h);
void rotation_base(float h);
void lower_arm(float h);
void upper_arm(float h);
void claw(float h);
void y_box(float h);

class RobotArm : public Model
{
	RangeProperty baseRotation, lowerTilt, upperTilt, clawRotation, baseLength,
		lowerLength, upperLength;

public:
    RobotArm() :
		Model("Robot Arm"),
		baseRotation("base rotation (theta)", -180, 180, 0,0.1),
		lowerTilt("lower arm tilt (phi)", 15, 95, 55, .1),
		upperTilt("upper arm tilt (psi)", 0, 135, 30, .1),
		clawRotation("claw rotation (cr)", -30, 180, 0, .1),
		baseLength("base height (h1)", .5, 10, .8, .1),
		lowerLength("lower arm length (h2)", 1, 10, 3, .1),
		upperLength("upper arm length (h3)", 1, 10, 2.5, .1)
	{
		properties.add(&baseRotation)
				  .add(&lowerTilt)
				  .add(&upperTilt)
				  .add(&clawRotation)
				  .add(&baseLength)
				  .add(&lowerLength)
				  .add(&upperLength);
	}
	virtual void draw();
};


// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out RobotArm
void RobotArm::draw()
{
	/* pick up the slider values */
	float theta = baseRotation.getValue();
	float phi = lowerTilt.getValue();
	float psi = upperTilt.getValue();
	float cr = clawRotation.getValue();
	float h1 = baseLength.getValue();
	float h2 = lowerLength.getValue();
	float h3 = upperLength.getValue();




	static GLfloat lmodel_ambient[] = {0.4,0.4,0.4,1.0};

	// define the model
	glPushMatrix();
		ground(-0.2);

		base(0.8);

		glTranslatef( 0.0, 0.8, 0.0 );			// move to the top of the base
		glRotatef( theta, 0.0, 1.0, 0.0 );		// turn the whole assembly around the y-axis. 
		rotation_base(h1);						// draw the rotation base

		glTranslatef( 0.0, h1, 0.0 );			// move to the top of the base
		glRotatef( phi, 0.0, 0.0, 1.0 );		// rotate around the z-axis for the lower arm
		glTranslatef( -0.1, 0.0, 0.4 );
		lower_arm(h2);							// draw the lower arm

		glTranslatef( 0.0, h2, 0.0 );			// move to the top of the lower arm
		glRotatef( psi, 0.0, 0.0, 1.0 );		// rotate  around z-axis for the upper arm
		upper_arm(h3);							// draw the upper arm

		glTranslatef( 0.0, h3, 0.0 );
		glRotatef( cr, 0.0, 0.0, 1.0 );
		claw(1.0);

	glPopMatrix();
}

void ground(float h) 
{
	//glDisable(GL_LIGHTING);
	//glColor3f(0.65,0.45,0.2);
	setDiffuseColor(0.65,0.45,0.2);
	setAmbientColor(0.65,0.45,0.2);
	glPushMatrix();
		glScalef(30,0,30);
		y_box(h);
	glPopMatrix();
	//glEnable(GL_LIGHTING);
}

void base(float h) {
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.25, 0.25, 0.25 );
	glPushMatrix();
		glPushMatrix();
			glTranslatef(1.0, h / 2.0, 0.75);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(1.0, h / 2.0, -1.0);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0, h / 2.0, 0.75);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.0, h / 2.0, -1.0);
			drawCylinder(0.25, h / 2.0, h / 2.0);
		glPopMatrix();
	glScalef(4.0f, h, 4.0f);
	y_box(1.0f);
	glPopMatrix();
}

void rotation_base(float h) {
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	glPushMatrix();
		glPushMatrix();
			glScalef(4.0, h, 4.0);
			y_box(1.0f); // the rotation base
		glPopMatrix();
		setDiffuseColor( 0.15, 0.15, 0.65 );
		setAmbientColor( 0.15, 0.15, 0.65 );
		glPushMatrix();
			glTranslatef(-0.5, h, -0.6);
			glScalef(2.0, h, 1.6);
			y_box(1.0f); // the console
		glPopMatrix();
		setDiffuseColor( 0.65, 0.65, 0.65 );
		setAmbientColor( 0.65, 0.65, 0.65 );
		glPushMatrix();
			glTranslatef( 0.5, h, 0.6 );
			glRotatef( -90.0, 1.0, 0.0, 0.0 );
			drawCylinder( h, 0.05, 0.05 ); // the pipe
		glPopMatrix();
	glPopMatrix();
}

void lower_arm(float h) {					// draw the lower arm
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	y_box(h);
}

void upper_arm(float h) {					// draw the upper arm
	setDiffuseColor( 0.85, 0.75, 0.25 );
	setAmbientColor( 0.95, 0.75, 0.25 );
	glPushMatrix();
	glScalef( 1.0, 1.0, 0.7 );
	y_box(h);
	glPopMatrix();
}

void claw(float h) {
	setDiffuseColor( 0.25, 0.25, 0.85 );
	setAmbientColor( 0.25, 0.25, 0.85 );

	glBegin( GL_TRIANGLES );

	glNormal3d( 0.0, 0.0, 1.0);		// +z side
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d(-0.5, 0.0, 0.5);
	glVertex3d( 0.5,   h, 0.5);

	glNormal3d( 0.0, 0.0, -1.0);	// -z side
	glVertex3d( 0.5, 0.0, -0.5);
	glVertex3d(-0.5, 0.0, -0.5);
	glVertex3d( 0.5,   h, -0.5);

	glEnd();

	glBegin( GL_QUADS );

	glNormal3d( 1.0,  0.0,  0.0);	// +x side
	glVertex3d( 0.5, 0.0,-0.5);
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d( 0.5,   h, 0.5);
	glVertex3d( 0.5,   h,-0.5);

	glNormal3d( 0.0,-1.0, 0.0);		// -y side
	glVertex3d( 0.5, 0.0, 0.5);
	glVertex3d( 0.5, 0.0,-0.5);
	glVertex3d(-0.5, 0.0,-0.5);
	glVertex3d(-0.5, 0.0, 0.5);

	glEnd();
}

void y_box(float h) {

	glBegin( GL_QUADS );

	glNormal3d( 1.0 ,0.0, 0.0);			// +x side
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d( 0.25,0.0,-0.25);
	glVertex3d( 0.25,  h,-0.25);
	glVertex3d( 0.25,  h, 0.25);

	glNormal3d( 0.0 ,0.0, -1.0);		// -z side
	glVertex3d( 0.25,0.0,-0.25);
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d(-0.25,  h,-0.25);
	glVertex3d( 0.25,  h,-0.25);

	glNormal3d(-1.0, 0.0, 0.0);			// -x side
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d(-0.25,  h, 0.25);
	glVertex3d(-0.25,  h,-0.25);

	glNormal3d( 0.0, 0.0, 1.0);			// +z side
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d( 0.25,  h, 0.25);
	glVertex3d(-0.25,  h, 0.25);

	glNormal3d( 0.0, 1.0, 0.0);			// top (+y)
	glVertex3d( 0.25,  h, 0.25);
	glVertex3d( 0.25,  h,-0.25);
	glVertex3d(-0.25,  h,-0.25);
	glVertex3d(-0.25,  h, 0.25);

	glNormal3d( 0.0,-1.0, 0.0);			// bottom (-y)
	glVertex3d( 0.25,0.0, 0.25);
	glVertex3d(-0.25,0.0, 0.25);
	glVertex3d(-0.25,0.0,-0.25);
	glVertex3d( 0.25,0.0,-0.25);

	glEnd();
}

/** The scene, which includes the lights and models. */


class Scene : public Model {
protected:
	///////////////////////////////// TEXTURES ////////////////////////////////////
	Texture2D texture;
	Texture2D particleTexture;

	///////////////////////////////// SHADERS /////////////////////////////////////
	ShaderProgram blinnPhong;
	ShaderProgram schlickShader;
	ShaderProgram anisotropicShader;
	ShaderProgram spotlightShader;
	ShaderProgram silhouetteShader;
	ShaderProgram cookTorrance;

	//////////////////////////////// PROPERTIES ///////////////////////////////////
	// Switches for spheres
	BooleanProperty useTexture;
	// Switch for showing/hiding reference unit sphere
	BooleanProperty showReferenceUnitSphere;

	// Lets you pick what shaders to use
	ChoiceProperty shaderChoice;

	// Some slider properties
	
	RangeProperty brightness;

	// Material color pickers
	RGBProperty diffuse;
	RGBProperty specular;
	RGBProperty ambient;
	RGBProperty emissive;

	// sliders for schlick shader
	RangeProperty schlickN1;
	RangeProperty schlickN2;

	//sliders for anisotropic shader
	RangeProperty anisotropicX;
	RangeProperty anisotropicY;

	//for silhouette shader
	RangeProperty edgeThickness;

	// for cook torrance shader
	RangeProperty ctGlossiness;

	// show surface of revolution normals
	BooleanProperty showNormals;

	// Scene lights
	PointLight pointLight;
	DirectionalLight directionalLight;
	SpotLight spotLight;

	// our added models
	Spider spider;

	Spider extraSpiders[ADDITIONAL_SPIDERS];
	RangeProperty shaderSlider;

	// A robot arm model
	RobotArm robotArm;

public:

	/** Modeler calls this to get our particle system. */
	ParticleSystem* getParticleSystem() {
		return spider.getParticleSystem();
	}

	RangeProperty sphereCenterX, sphereCenterY, sphereCenterZ;

	/** Construct the scene */
	Scene() :
		// You have to call the parent class's constructor, to provide a
		// name for the model.
		Model("Scene"),
		spider(),

		// Construct textures and shaders. 
		// They won't be loaded until the model is drawn for the first time.
		texture("checkers.png"),
		particleTexture("snow.jpg"),
		blinnPhong("shader.vert", "shader.frag", NULL),
		schlickShader("shader.vert", "schlick.frag", NULL),
		anisotropicShader("shader.vert", "anisotropic.frag", NULL),
		spotlightShader("spotlight.vert", "spotlight.frag", NULL),
		silhouetteShader("shader.vert", "silhouette.frag", NULL),
		cookTorrance("shader.vert", "cooktorrance.frag", NULL),
		// Call the constructors for the lights
		pointLight("Point Light", GL_LIGHT1, /**direction part**/ -5, 5, 5, /**diffuse part**/ 1.0, 0.5, 0.5,
		/**specular part**/ 1.0, 0.5, 0.5, /**ambient part**/ .2f, 0.1, 0.1 /**attenuation part**/, 0.4, 0.7, 0),
		directionalLight("Directional Light", GL_LIGHT0, /**direction part**/ 5, 5, 5, /**diffuse part**/ 0.0f, 0.5, 0.5f,
		/**specular part**/ 0.0f, 0.5f, 0.5f),
		spotLight("Spot Light", GL_LIGHT2, /**direction part**/ 0, 5, 5, /**diffuse part**/ 1.0f, 0.5, 0.5f,
		/**specular part**/ 1.0f, 0.5f, 0.5f)

		// Now, call the constructors for each Property:
		, useTexture("Use Checkered Texture", true),
		showReferenceUnitSphere("Show Reference Unit Sphere", false),
		shaderChoice("Shader To Use:", "Texture|Blinn-Phong Shader|Schlick Shader|Spotlight Shader|Ward Anisotropic Shader|Border Shader|Cook-Torrance w/ Schlick", 1),
		shaderSlider("Shader", 0.0f, 6.0f, 1.0f, 1.0f),
		brightness("Brightness", 0.0f, 1.0f, 1.0f, 0.1f),
		diffuse("Diffuse Color", 1.0, 0.7, .4),
		specular("Specular Color", 1.0, 1.0, 1.0),
		ambient("Ambient Color", 0.2, 0.2, 0.2),
		emissive("Emissive Color", 0.0, 0.0, 0.0),
		schlickN1("Schlick N1", 1.0, 10.0, 10.0, .1),
		schlickN2("Schlick N2", 1.0, 10.0, 0.0, .1),
		anisotropicX("Anisotropic X", 0.1, 2.0, 2.0, .1),
		anisotropicY("Anisotropic Y", 0.1, 2.0, 0.1, .1),
		edgeThickness("Silhouette Border Thickness", 0.05, 0.60, 0.30, 0.1),
		ctGlossiness("Cook-Torrance Glossiness", 0.01, 2.0, 2.0, 0.01),
		showNormals("Show Revolution Normals", false),
		sphereCenterX("Collision Sphere Center (X)", -6.0, 6.0, -5.0, 0.1),
		sphereCenterY("Collision Sphere Center (Y)", -6.0, 6.0, 0, 0.1),
		sphereCenterZ("Collision Sphere Center (Z)", -6.0, 6.0, 0, 0.1)
	{
		// If you have child Models, like the MobileLight model from model.h,
		// you can add their property groups, and they will appear in the list
		// in the top left corner of Modeler, under this model's entry:
		properties.add(pointLight.getProperties())
			.add(directionalLight.getProperties())
			.add(spotLight.getProperties())
			;
		properties.add(spider.getProperties());

		// Finally, add all the properties to this model's PropertyGroup.
		properties.add(&useTexture);
		
		for (int i = 0; i < ADDITIONAL_SPIDERS; i++) {
			properties.add(extraSpiders[i].getProperties());
		}
		properties.add(&showReferenceUnitSphere)
			.add(&showNormals)
			.add(&shaderChoice)
			.add(&shaderSlider);
		properties.add(&sphereCenterX)
			.add(&sphereCenterY)
			.add(&sphereCenterZ);
		properties.add(&spider.getParticleSystem()->restitutionSlider);
		properties.add(&spider.getParticleSystem()->dragSlider);
		properties.add(&spider.getParticleSystem()->gravSlider);
		properties.add(&brightness)
			.add(&diffuse)
			.add(&specular)
			.add(&ambient)
			.add(&emissive)
			.add(&schlickN1)
			.add(&schlickN2)
			.add(&anisotropicX)
			.add(&anisotropicY)
			.add(&edgeThickness)
			.add(&ctGlossiness)
			;
		
		//properties.add(robotArm.getProperties());

	}



	/**
	* Modeler calls this method once an OpenGL context becomes available,
	* (which happens before the first time draw() is called), and whenever
	* you click the "Reload Textures and Shaders" menu option.
	*
	* Make sure you call the load() methods of each of your textures and
	* shaders here.
	*/
	void load() {
		texture.load();
		particleTexture.load();
		blinnPhong.load();
		schlickShader.load();
		anisotropicShader.load();
		spotlightShader.load();
		silhouetteShader.load();
		cookTorrance.load();
	}

	/**
	* Modeler calls this method many times a second when the Animate
	* checkbox is checked.
	*/
	void tick() {
		// You can put code here to increment animation counters for
		// extra credit.
		spider.tick();
	}

	/** Draw the model. */
	void drawModel() {

		int divisions = 16;
		switch (ModelerDrawState::Instance()->m_quality)
		{
		case HIGH:
			divisions = 64; break;
		case MEDIUM:
			divisions = 20; break;
		case LOW:
			divisions = 12; break;
		case POOR:
			divisions = 8; break;
		}

		// Remember our current modelview matrix, which is in world space.
		glPushMatrix();

		// Draw a spider at the origin.
		spider.draw();

		for (int i = 0; i < ADDITIONAL_SPIDERS; i++) {
			extraSpiders[i].draw();
		}

		if (showReferenceUnitSphere.getValue()) {
			// Now go 1 units in the +y direction,
			// and 1 units in the NEGATIVE x direction.
			glTranslated(-2, -1, 0);
			// Now go 1 units in the +y direction,
			// and 1 units in the NEGATIVE x direction.
			glRotatef(-90.f, 1.f, 0.f, 0.f);
			drawSphere(.5);
			glRotatef(90.f, 1.f, 0.f, 0.f);
			glPopMatrix();
		}

		// Go back to "world space"
		glPopMatrix();

		{

			// Draw the floor.  Here's a basic example of texture mapping.
			glBegin(GL_QUADS);
			glTexCoord2f(0, 1); // specify the texture coordinate
			glNormal3f(0, 1, 0); // specify the surface's normal at this vertex
			glVertex3f(-100, -2, -100); // both before its corresponding vertex

			glTexCoord2f(1, 1);
			glNormal3f(0, 1, 0);
			glVertex3f(100, -2, -100);

			glTexCoord2f(1, 0);
			glNormal3f(0, 1, 0);
			glVertex3f(100, -2, 100);

			glTexCoord2f(0, 0);
			glNormal3f(0, 1, 0);
			glVertex3f(-100, -2, 100);
			glEnd();
		}
	}


	/** Draw the scene. */
	void draw() {
		// The lights must be drawn FIRST, so the other scene elements
		// can get lit!
		pointLight.draw();
		directionalLight.draw();
		spotLight.draw();
		//reset colors
		setDiffuseColor(
			diffuse.getRed(),
			diffuse.getGreen(),
			diffuse.getBlue());

		setAmbientColor(
			ambient.getRed(),
			ambient.getGreen(),
			ambient.getBlue());

		setSpecularColor(
			specular.getRed(),
			specular.getGreen(),
			specular.getBlue());

		setEmissiveColor(
			emissive.getRed(),
			emissive.getGreen(),
			emissive.getBlue());

		setShininess(pow(2.71828183f, 3));

		// Use the texture if desired.
		if (useTexture.getValue()) {
			texture.use();
		}
		else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		shaderChoice.setValue(shaderSlider.getValue());

		// Use the chosen shader
		switch (shaderChoice.getValue()) {
		case 0: // Texture
			if (glUseProgram) { glUseProgram(0); } //don't use shader
			break;
		case 1: // point light blinn phong
		{
			blinnPhong.use();
			// glGetUniformLocation gets the memory location of a variable with the given char* name, in this case "brightness"
			// for the given shader program, identified by its ID.
			GLint brightnessVariableLocation = glGetUniformLocation(blinnPhong.getID(), "brightness");
			// glUniform1f sets the value of a particular uniform variable location with a single float value (hence the suffix "1f")
			glUniform1f(brightnessVariableLocation, brightness.getValue());
			break;
		}
		case 2:
		{
			schlickShader.use();
			GLint brightnessVariableLocation = glGetUniformLocation(schlickShader.getID(), "brightness");
			GLint schlickN1VarLocation = glGetUniformLocation(schlickShader.getID(), "n1");
			GLint schlickN2VarLocation = glGetUniformLocation(schlickShader.getID(), "n2");
			glUniform1f(brightnessVariableLocation, brightness.getValue());
			glUniform1f(schlickN1VarLocation, schlickN1.getValue());
			glUniform1f(schlickN2VarLocation, schlickN2.getValue());
			break;
		}
		case 3:
		{
			spotlightShader.use();
			GLint brightnessVariableLocation = glGetUniformLocation(blinnPhong.getID(), "brightness");
			glUniform1f(brightnessVariableLocation, brightness.getValue());
			break;
		}
		case 4:
		{
			anisotropicShader.use();
			GLint brightnessVariableLocation = glGetUniformLocation(anisotropicShader.getID(), "brightness");
			GLint xMagVarLocation = glGetUniformLocation(anisotropicShader.getID(), "xMag");
			GLint yMagVarLocation = glGetUniformLocation(anisotropicShader.getID(), "yMag");
			glUniform1f(brightnessVariableLocation, brightness.getValue());
			glUniform1f(xMagVarLocation, anisotropicX.getValue());
			glUniform1f(yMagVarLocation, anisotropicY.getValue());
			break;
		}
		case 5:
		{
			silhouetteShader.use();
			GLint brightnessVariableLocation = glGetUniformLocation(silhouetteShader.getID(), "brightness");
			GLint edgeThicknessLocation = glGetUniformLocation(silhouetteShader.getID(), "edgeThickness");
			glUniform1f(brightnessVariableLocation, brightness.getValue());
			glUniform1f(edgeThicknessLocation, edgeThickness.getValue());
			break;
		}
		case 6:
		{
			cookTorrance.use();
			GLint brightnessVariableLocation = glGetUniformLocation(cookTorrance.getID(), "brightness");
			GLint glossinessnessVariableLocation = glGetUniformLocation(cookTorrance.getID(), "glossiness");
			GLint schlickN1VarLocation = glGetUniformLocation(cookTorrance.getID(), "n1");
			GLint schlickN2VarLocation = glGetUniformLocation(cookTorrance.getID(), "n2");
			glUniform1f(brightnessVariableLocation, brightness.getValue());
			glUniform1f(glossinessnessVariableLocation, ctGlossiness.getValue());
			glUniform1f(schlickN1VarLocation, schlickN1.getValue());
			glUniform1f(schlickN2VarLocation, schlickN2.getValue());
			break;
		}


		}

		// Draw the default sphere for collision
		double collisionSphereRadius = 1.0;

		// give camera transforms to spider before rotations are performed
		Mat4f modelViewMatrix = getModelViewMatrix();
		spider.setCameraTransforms(modelViewMatrix);

		glPushMatrix();
		spider.getParticleSystem()->collisionSpherePosition =
			Vec3d(sphereCenterX.getValue(), sphereCenterY.getValue(), sphereCenterZ.getValue());
		spider.getParticleSystem()->collisionSphereRadius = collisionSphereRadius;
		glTranslatef(sphereCenterX.getValue(), sphereCenterY.getValue(), sphereCenterZ.getValue());
		//glutSolidSphere(collisionSphereRadius, 20, 20); // the 20's are arbitary
		glPopMatrix();

		// Draw robot arm
		//robotArm.draw();

		// give texture to particle system
		spider.getParticleSystem()->texture = particleTexture;

		// Call a class method that draws our model.
		drawModel();
		// Stop applying shaders to objects.
		// This if-statement makes sure that glUseProgram is not a null
		// function pointer (which it will be if GLEW couldn't initialize).
		if (glUseProgram) {
			glUseProgram(0);
		}

	}
};

/**
* The program starts here.
*/

int main()
{
	// Tell the FLTK library to let us use OpenGL
	Fl::gl_visual(FL_RGB);

	init_load_curve_file();

	// Instantiate Modeler
	ModelerUserInterface ui;

	// Give Modeler your scene.
	// Modeler will free this pointer when it exits.
	ui.setModel(new Scene());


	// Run the application
	return ui.run();
}