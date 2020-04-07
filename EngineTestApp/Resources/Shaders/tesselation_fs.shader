#version 450

out vec4 FragColor;
in vec3 gNormal;
in vec3 gTriDistance;
in vec3 gPatchDistance;
in float gPrimitive;
in float gElevation;
uniform vec3 LightPosition;
uniform vec3 DiffuseMaterial;
uniform vec3 AmbientMaterial;
uniform mat4 WorldViewProjection;
uniform mat3 NormalMatrix;

float amplify(float d, float scale, float offset)
{
	d = scale * d + offset;
	d = clamp(d, 0, 1);
	d = 1 - exp2(-2 * d * d);
	return d;
}

vec3 lightDirection = vec3(-0.7, -0.7, -0.7);

void main()
{
	/*vec3 N = normalize(gFacetNormal);
	vec3 L = LightPosition;
	float df = abs(dot(N, L));
	vec3 color = AmbientMaterial + df * DiffuseMaterial;

	float d1 = min(min(gTriDistance.x, gTriDistance.y), gTriDistance.z);
	float d2 = min(min(gPatchDistance.x, gPatchDistance.y), gPatchDistance.z);
	color = amplify(d1, 40, -0.5) * amplify(d2, 60, -0.5) * color;
	FragColor = vec4(color, 1.0);*/

	float diffuse = dot(normalize(lightDirection), -gNormal);
	FragColor = vec4(gElevation, gElevation, gElevation, 1.0);
}
