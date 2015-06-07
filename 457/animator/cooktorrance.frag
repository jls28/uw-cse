// Fragment shader for per-pixel Phong interpolation and shading.

// The "varying" keyword means that the parameter's value is interpolated
// between the nearby vertices.
varying vec3 N;
varying vec3 v;

uniform float brightness;
uniform float glossiness;
uniform float n1;
uniform float n2;

#define M_PI 3.1415926535897932384626433832795

float specularFactor(vec3 L, vec3 V, vec3 N) {
	L = normalize(L);
	V = normalize(V);
	N = normalize(N);
	vec3 H = normalize(L + V);
	float NdotL = abs(dot(N, L));
	float NdotV = abs(dot(N, V));
	float HdotN = abs(dot(N, H));
	float HdotV = abs(dot(H, V));
	if (NdotL == 0.0 || HdotV == 0.0 || HdotN == 0.0 || NdotV == 0.0) {
		return 0.0;
	} else {
		float geoPart = 2.0 * HdotN / HdotV;
		float geometric = min(1.0, geoPart * NdotV);
		geometric = min(geometric, geoPart * NdotL);
		float roughness = 1.0 / (pow(glossiness, 2.0) * pow(HdotN, 4.0));
		roughness *= exp((pow(HdotN, 2.0) - 1.0) / (pow(glossiness, 2.0) * pow(HdotN, 2.0)));
		float f0 = pow((n1 - n2) / (n1 + n2), 2.0);
		float w = pow(1.0 - HdotV, 5.0);
		float fresnel = f0 + (1.0 - f0) * w;
		return geometric * roughness * fresnel / (4.0 * NdotV * NdotL);
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
	vec4 pointSpecular = attn * gl_FrontMaterial.specular * gl_LightSource[1].specular * specularFactor(normalize(L), Viewer, Normal);
	specular += pointSpecular;

	// Assign final color
	gl_FragColor = ambient + diffuse + specular + gl_FrontMaterial.emission;
	// Scale with brightness value
	gl_FragColor = gl_FragColor * brightness;
}

