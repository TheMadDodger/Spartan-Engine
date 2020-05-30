#version 420

layout(vertices = 3) out;
in vec3 vPosition[];
out vec3 tcPosition[];

const float MaxTessLevel = 10;

#define ID gl_InvocationID

void main()
{
    tcPosition[ID] = vPosition[ID];
    if (ID == 0)
    {
        gl_TessLevelInner[0] = MaxTessLevel;
        gl_TessLevelOuter[0] = MaxTessLevel;
        gl_TessLevelOuter[1] = MaxTessLevel;
        gl_TessLevelOuter[2] = MaxTessLevel;
    }
}
