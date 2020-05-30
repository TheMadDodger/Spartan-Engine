const int RandomSize = 256;
const float Sqrt3 = 1.7320508075688772935;
const float Sqrt5 = 2.2360679774997896964;

layout(std140) uniform RandomBlock
{
    int Data[512];
} _random;

/// Skewing and unskewing factors for 2D, 3D and 4D, 
/// some of them pre-multiplied.
const float F2 = 0.5 * (Sqrt3 - 1.0);
const float G2 = (3.0 - Sqrt3) / 6.0;
const float G22 = G2 * 2.0 - 1;
const float F3 = 1.0 / 3.0;
const float G3 = 1.0 / 6.0;
const float F4 = (Sqrt5 - 1.0) / 4.0;
const float G4 = (5.0 - Sqrt5) / 20.0;
const float G42 = G4 * 2.0;
const float G43 = G4 * 3.0;
const float G44 = G4 * 4.0 - 1.0;

/// <summary>
/// Gradient vectors for 3D (pointing to mid points of all edges of a unit
/// cube)
/// </summary>
const int[] Grad3 =
{
    1, 1, 0, -1, 1, 0, 1, -1, 0,
    -1, -1, 0, 1, 0, 1, -1, 0, 1,
    1, 0, -1, -1, 0, -1, 0, 1, 1,
    0, -1, 1, 0, 1, -1, 0, -1, -1
};

float Dot(int index, float x, float y, float z)
{
    return Grad3[index] * x + Grad3[index + 1] * y + Grad3[index + 2] * z;
}

float Dot(int index, float x, float y)
{
    return Grad3[index] * x + Grad3[index + 1] * y;
}

int FastFloor(float x)
{
    return int(x) >= 0 ? int(x) : int(x) - 1;
}

///// <summary>
///// Generates value, typically in range [-1, 1]
///// </summary>
float Evaluate(vec3 p)
{
    float x = p.x;
    float y = p.y;
    float z = p.z;
    float n0 = 0.0, n1 = 0.0, n2 = 0.0, n3 = 0.0;

    // Noise contributions from the four corners
    // Skew the input space to determine which simplex cell we're in
    float s = (x + y + z) * F3;

    // for 3D
    int i = FastFloor(x + s);
    int j = FastFloor(y + s);
    int k = FastFloor(z + s);

    float t = (i + j + k) * G3;

    // The x,y,z distances from the cell origin
    float x0 = x - (i - t);
    float y0 = y - (j - t);
    float z0 = z - (k - t);

    // For the 3D case, the simplex shape is a slightly irregular tetrahedron.
    // Determine which simplex we are in.
    // Offsets for second corner of simplex in (i,j,k)
    int i1, j1, k1;

    // coords
    int i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords

    if (x0 >= y0)
    {
        if (y0 >= z0)
        {
            // X Y Z order
            i1 = 1;
            j1 = 0;
            k1 = 0;
            i2 = 1;
            j2 = 1;
            k2 = 0;
        }
        else if (x0 >= z0)
        {
            // X Z Y order
            i1 = 1;
            j1 = 0;
            k1 = 0;
            i2 = 1;
            j2 = 0;
            k2 = 1;
        }
        else
        {
            // Z X Y order
            i1 = 0;
            j1 = 0;
            k1 = 1;
            i2 = 1;
            j2 = 0;
            k2 = 1;
        }
    }
    else
    {
        // x0 < y0
        if (y0 < z0)
        {
            // Z Y X order
            i1 = 0;
            j1 = 0;
            k1 = 1;
            i2 = 0;
            j2 = 1;
            k2 = 1;
        }
        else if (x0 < z0)
        {
            // Y Z X order
            i1 = 0;
            j1 = 1;
            k1 = 0;
            i2 = 0;
            j2 = 1;
            k2 = 1;
        }
        else
        {
            // Y X Z order
            i1 = 0;
            j1 = 1;
            k1 = 0;
            i2 = 1;
            j2 = 1;
            k2 = 0;
        }
    }

    // A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
    // a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z),
    // and
    // a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z),
    // where c = 1/6.

    // Offsets for second corner in (x,y,z) coords
    float x1 = x0 - i1 + G3;
    float y1 = y0 - j1 + G3;
    float z1 = z0 - k1 + G3;

    // Offsets for third corner in (x,y,z)
    float x2 = x0 - i2 + F3;
    float y2 = y0 - j2 + F3;
    float z2 = z0 - k2 + F3;

    // Offsets for last corner in (x,y,z)
    float x3 = x0 - 0.5;
    float y3 = y0 - 0.5;
    float z3 = z0 - 0.5;

    // Work out the hashed gradient indices of the four simplex corners
    int ii = i & 0xff;
    int jj = j & 0xff;
    int kk = k & 0xff;

    // Calculate the contribution from the four corners
    float t0 = 0.6 - x0 * x0 - y0 * y0 - z0 * z0;

    if (t0 > 0)
    {
        t0 *= t0;
        int gi0 = _random.Data[ii + _random.Data[jj + _random.Data[kk]]] % 12;
        n0 = t0 * t0 * Dot(gi0 * 3, x0, y0, z0);
    }

    float t1 = 0.6 - x1 * x1 - y1 * y1 - z1 * z1;
    if (t1 > 0)
    {
        t1 *= t1;
        int gi1 = _random.Data[ii + i1 + _random.Data[jj + j1 + _random.Data[kk + k1]]] % 12;
        n1 = t1 * t1 * Dot(gi1 * 3, x1, y1, z1);
    }

    float t2 = 0.6 - x2 * x2 - y2 * y2 - z2 * z2;
    if (t2 > 0)
    {
        t2 *= t2;
        int gi2 = _random.Data[ii + i2 + _random.Data[jj + j2 + _random.Data[kk + k2]]] % 12;
        n2 = t2 * t2 * Dot(gi2 * 3, x2, y2, z2);
    }

    float t3 = 0.6 - x3 * x3 - y3 * y3 - z3 * z3;
    if (t3 > 0)
    {
        t3 *= t3;
        int gi3 = _random.Data[ii + 1 + _random.Data[jj + 1 + _random.Data[kk + 1]]] % 12;
        n3 = t3 * t3 * Dot(gi3 * 3, x3, y3, z3);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to stay just inside [-1,1]
    return float(n0 + n1 + n2 + n3) * 32;
}

float Evaluate(vec3 p, float strength, float roughness, vec3 centre)
{
    float noise = (Evaluate(p * roughness + centre) + 1.0) * 0.5;
    return noise * strength;
}

float SimpleEvaluate(vec3 p, int numLayers, float baseRoughness, float roughness, float persistance, vec3 centre, float minValue, float strength)
{
    float noiseValue = 0.0;
    float frequency = baseRoughness;
    float amplitude = 1.0;

    for (int i = 0; i < numLayers; i++)
    {
        float v = Evaluate(p * frequency + centre);
        noiseValue += (v + 1) * 0.5 * amplitude;
        frequency *= roughness;
        amplitude *= persistance;
    }

    //noiseValue = max(0.0, noiseValue - minValue);
    return (noiseValue - minValue) * strength;
}

float RigidEvaluate(vec3 p, int numLayers, float baseRoughness, float roughness, float persistance, vec3 centre, float minValue, float strength, float weight)
{
    float noiseValue = 0.0;
    float frequency = baseRoughness;
    float amplitude = 1.0;
    weight = 1.0;

    for (int i = 0; i < numLayers; i++)
    {
        float v = 1.0 - abs(Evaluate(p * frequency + centre));
        v *= v;
        v *= weight;
        weight = v;
        noiseValue += v * amplitude;
        frequency *= roughness;
        amplitude *= persistance;
    }

    //noiseValue = max(0.0, noiseValue - minValue);
    return (noiseValue - minValue) * strength;
}
