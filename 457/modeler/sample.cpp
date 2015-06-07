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
#include <cmath>
#include <time.h>
#include "evilSpongebob.h"
#include "spider.h"


/** The scene, which includes the lights and models. */


class Scene : public Model {
protected:
///////////////////////////////// TEXTURES ////////////////////////////////////
	Texture2D texture;

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

	// Lets you pick what shapes to use for the default model!
	ChoiceProperty shapeChoice;

	// Lets you pick what shaders to use
	ChoiceProperty shaderChoice;

	// Some slider properties
	RangeProperty rotateX, rotateY;
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
	EvilSpongebob evilSpongebob;
	Spider spider;

public:
	
	

	/** Construct the scene */
	Scene() :
		// You have to call the parent class's constructor, to provide a
		// name for the model.
		Model("Scene"),

		evilSpongebob(),
		spider(),

		// Construct textures and shaders. 
		// They won't be loaded until the model is drawn for the first time.
		texture("checkers.png"),
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
		shapeChoice("Model Shape:", "Sphere|Cube|Cylinder|Torus|Icosahedron|Teapot|Revolution|Spongebob's Evil Twin|Spider", 0), //457 animator UI only allows shapes
		shaderChoice("Shader To Use:", "Texture|Blinn-Phong Shader|Schlick Shader|Spotlight Shader|Ward Anisotropic Shader|Border Shader|Cook-Torrance w/ Schlick", 1),
		rotateX("Rotate Basic Shape X", -180, 180, 0, 1),
		rotateY("Rotate Basic Shape Y", -180, 180, 0, 1),
		brightness("Brightness", 0.0f, 1.0f, 1.0f, 0.1f),
		diffuse("Diffuse Color", 1.0, 0.7, .4),
		specular("Specular Color", 1.0, 1.0, 1.0),
		ambient("Ambient Color", 0.2, 0.2, 0.2),
		emissive("Emissive Color", 0.0, 0.0, 0.0),
		schlickN1("Schlick N1", 1.0, 10.0, 10.0, .1),
		schlickN2("Schlick N2", 1.0, 10.0, 10.0, .1),
		anisotropicX("Anisotropic X", 0.1, 2.0, 2.0, .1),
		anisotropicY("Anisotropic Y", 0.1, 2.0, 0.1, .1),
		edgeThickness("Silhouette Border Thickness", 0.05, 0.60, 0.30, 0.1),
		ctGlossiness("Cook-Torrance Glossiness", 0.01, 2.0, 0.3, 0.01),
		showNormals("Show Revolution Normals", false)
	{
		// If you have child Models, like the MobileLight model from model.h,
		// you can add their property groups, and they will appear in the list
		// in the top left corner of Modeler, under this model's entry:
		properties.add(pointLight.getProperties())
				  .add(directionalLight.getProperties())
				  .add(spotLight.getProperties())
				  ;
		properties.add(spider.getProperties());
		properties.add(evilSpongebob.getProperties());

		// Finally, add all the properties to this model's PropertyGroup.
		properties.add(&useTexture);
		properties.add(&showReferenceUnitSphere)
			.add(&showNormals)
			.add(&shapeChoice)
			.add(&shaderChoice);
		properties.add(&rotateX)
				.add(&rotateY);
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

		int divisions=16; 		
        switch(ModelerDrawState::Instance()->m_quality)
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

		    // Rotate around the X-axis
			glRotatef(rotateX.getValue(), 1, 0, 0);

			// Rotate around the Y-axis
			glRotatef(rotateY.getValue(), 0, 1, 0);


			// Draw some object at the origin.
			switch (shapeChoice.getValue()) {
			case 0: // sphere
				glRotatef(-90.f,1.f,0.f,0.f);
				glutSolidSphere(1.0, divisions, divisions);
				glRotatef(90.f,1.f,0.f,0.f);
				break;
			case 1: // box
				glRotatef(-45.f,0.f,1.f,0.f);
				glutSolidCube(2);
				glRotatef(45.f,0.f,1.f,0.f);
				break;
			case 2: // cylinder
				glRotatef(90.f,1.f,0.f,0.f);
				drawCylinder(1.8,1.0,1.8);
				glRotatef(-90.f,1.f,0.f,0.f);
				break;
			case 3: // torus
				glutSolidTorus(.5,1,divisions,divisions);
				break;
			case 4: // icosahedron
				glutSolidIcosahedron();
				break;
			case 5: // teapot
				glutSolidTeapot(1);
				break;
			case 6:
				drawRevolution(1, showNormals.getValue());
				break;
			case 7:
				evilSpongebob.draw();
				break;
			case 8:
				spider.draw();
				break;
			}

			if (showReferenceUnitSphere.getValue() ) {
			    // Now go 1 units in the +y direction,
				// and 1 units in the NEGATIVE x direction.
				glTranslated(-2, -1, 0);
			    // Now go 1 units in the +y direction,
				// and 1 units in the NEGATIVE x direction.
					glRotatef(-90.f,1.f,0.f,0.f);
					drawSphere(.5);
					glRotatef(90.f,1.f,0.f,0.f);
				glPopMatrix();
			}
			
			// Go back to "world space"
			glPopMatrix();

		{

			// Draw the floor.  Here's a basic example of texture mapping.
			glBegin(GL_QUADS);
			glTexCoord2f(0, 1); // specify the texture coordinate
			glNormal3f(0, 1, 0); // specify the surface's normal at this vertex
			glVertex3f(-10, -2, -10); // both before its corresponding vertex

			glTexCoord2f(1, 1);
			glNormal3f(0, 1, 0);
			glVertex3f(10, -2, -10);

			glTexCoord2f(1, 0);
			glNormal3f(0, 1, 0);
			glVertex3f(10, -2, 10);

			glTexCoord2f(0, 0);
			glNormal3f(0, 1, 0);
			glVertex3f(-10, -2, 10);
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
		} else {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

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

		// Call a class method that draws our model.
		drawModel();
		// Stop applying shaders to objects.
		// This if-statement makes sure that glUseProgram is not a null
		// function pointer (which it will be if GLEW couldn't initialize).
		if (glUseProgram) {
			glUseProgram(0);
		}

		// Stop applying textures to objects
		glBindTexture(GL_TEXTURE_2D, 0);
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