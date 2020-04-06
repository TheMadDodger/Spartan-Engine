#version 450

layout(vertices = 3) out;
in vec3 vPosition[];
out vec3 tcPosition[];

uniform vec3 CameraPosition;
uniform mat4 WorldMatrix;

const float MaxDistance = 256;
const float MaxTessLevel = 20;
const float Intensity = 5;

#define ID gl_InvocationID

void main()
{
    tcPosition[ID] = vPosition[ID];
    if (ID == 0)
    {
        vec3 worldPosition = (WorldMatrix * vec4(vPosition[0], 1.0)).xyz;
        float dst = distance(CameraPosition, worldPosition);
        float factor = dst / MaxDistance;

        factor = clamp(factor, 0.0, 1.0);
        factor = 1.0 - factor;
        float tessLevel = MaxTessLevel * pow(factor, Intensity);
        tessLevel = clamp(tessLevel, 1.0, MaxTessLevel);

        gl_TessLevelInner[0] = tessLevel;
        gl_TessLevelOuter[0] = tessLevel;
        gl_TessLevelOuter[1] = tessLevel;
        gl_TessLevelOuter[2] = tessLevel;
    }
}
