// Fragment shader for per-pixel Phong interpolation and shading.

// The "varying" keyword means that the parameter's value is interpolated
// between the nearby vertices.
varying vec3 N;
varying vec3 v;

uniform float brightness;
uniform float xMag;
uniform float yMag;

#define M_PI 3.1415926535897932384626433832795

float specularFactor(vec3 L, vec3 V, vec3 N) {
	vec3 e = vec3(0.0,0.0,-1.0);
	vec3 T = normalize(cross(N, e));
	L = normalize(L);
	V = normalize(V);
	N = normalize(N);
	vec3 B = normalize(cross(N, T));
	vec3 H = normalize(L + V);
	float NdotL = max(0.0, dot(N, L));
	float NdotV = max(0.0, dot(N, V));
	float HdotN = dot(N, H);
	float HdotT = dot(T, H);
	float HdotB = dot(B, H);
	if (NdotL == 0.0 || NdotV == 0.0) {
		return 0.0;
	} else {
		float den = sqrt(NdotL * NdotV) * (4.0 * M_PI * xMag * yMag);
		float beta = -2.0 * (pow(HdotT / xMag, 2.0) + pow(HdotB / yMag, 2.0)) / (1.0 + HdotN);
		return (1.0 / den) * exp(beta) * NdotL;
	}
}

void main()
{
    // The scene's ambient light.
    vec4 ambient = gl_LightModel.ambient * gl_FrontMaterial.ambient;

	// The normal vectors is generally not normalized after being
	// interpolated across a triangle.  Here we normalize it.
	vec3 Normal = normalize(N);

	// Since the vertex is in eye space, the direction to the
	// viewer is simply the normalized vector from v to the
	// origin.
	vec3 Viewer = -normalize(v);

	// Get the lighting direction and normalize it.
	vec3 Light  = normalize(gl_LightSource[0].position.xyz);

	// Compute halfway vector
	vec3 Half = normalize(Viewer+Light);

	// Compute factor to prevent light leakage from below the
	// surface
	float B = 1.0;
	if(dot(Normal, Light)<0.0) B = 0.0;

	// Compute geometric terms of diffuse and specular
	float diffuseShade = max(dot(Normal, Light), 0.0);
	float specularShade = specularFactor(Light, Viewer, Normal);

	// Compute product of geometric terms with material and
	// lighting values
	vec4 diffuse = diffuseShade * gl_FrontLightProduct[0].diffuse;
	vec4 specular = specularShade * gl_FrontLightProduct[0].specular;
	ambient += gl_FrontLightProduct[0].ambient;

	// ---- Point Light ----
	
	// L vector from light to pixel
	vec3 L = vec3(gl_LightSource[1].position.xyz - v);

	// Distance of light to pixel
	float dist = length(L);

	// Calculate the attenuation
	float constA = gl_LightSource[1].constantAttenuation;
	float linA = gl_LightSource[1].linearAttenuation;
	float quadA = gl_LightSource[1].quadraticAttenuation;
	float attn = 1.0/( constA + linA*dist + quadA*dist*dist );

	//calculate the ambient of the point light
	vec4 pointAmbient = attn * gl_FrontLightProduct[1].ambient;
	//add in the ambient of the point light
	ambient += pointAmbient;

	//calculate the diffuse of the point light
	vec4 pointDiffuse = attn * gl_FrontLightProduct[1].diffuse;
	float NdotL = max(dot(Normal, normalize(L)), 0.0);
	diffuse += pointDiffuse * NdotL;
	//Calculate the specular of the point light
	vec3 halfV = normalize(Viewer + normalize(L));
	float NdotHV = max(dot(Normal, halfV), 0.0);
	vec4 pointSpecular = attn * gl_FrontMaterial.specular * gl_LightSource[1].specular * specularFactor(L, Viewer, Normal);
	specular += pointSpecular;

	// Assign final color
	gl_FragColor = ambient + diffuse + specular + gl_FrontMaterial.emission;
	// Scale with brightness value
	gl_FragColor = gl_FragColor * brightness;
}

