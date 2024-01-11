#ifndef MATH_H
#define MATH_H

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

#undef M_PI_2
#define M_PI_2 (M_PI * 2.0)

#undef M_PI_H
#define M_PI_H (M_PI * 0.5)

// not "math" but works best here
#define INT_TO_VOID(x) (void *)(size_t)(x)
#define VOID_TO_INT(x) (int)(size_t)(x)

#define MIN(a, b)                      ((a) < (b) ? (a) : (b))
#define MAX(a, b)                      ((a) > (b) ? (a) : (b))
#define CLAMP(value, minimum, maximum) (((value) < (minimum)) ? (minimum) : (((value) > (maximum)) ? (maximum) : (value)))

#define TO_FIXED(x)   ((x) << 16)
#define FROM_FIXED(x) ((x) >> 16)

// M_PI is *too* accurate, so use this instead
#define RSDK_PI (3.1415927f)

struct Vector2 {
    int x;
    int y;
};

#define MEM_ZERO(x)  memset(&(x), 0, sizeof((x)))
#define MEM_ZEROP(x) memset((x), 0, sizeof(*(x)))

extern int sin1024LookupTable[0x400];
extern int cos1024LookupTable[0x400];
extern int tan1024LookupTable[0x400];
extern int asin1024LookupTable[0x400];
extern int acos1024LookupTable[0x400];

extern int sinM7LookupTable[0x200];
extern int cosM7LookupTable[0x200];

extern int sin512LookupTable[0x200];
extern int cos512LookupTable[0x200];
extern int tan512LookupTable[0x200];
extern int asin512LookupTable[0x200];
extern int acos512LookupTable[0x200];

extern int sin256LookupTable[0x100];
extern int cos256LookupTable[0x100];
extern int tan256LookupTable[0x100];
extern int asin256LookupTable[0x100];
extern int acos256LookupTable[0x100];

extern byte arcTan256LookupTable[0x100 * 0x100];

// Setup Angles
void ClearTrigLookupTables();
void CalculateTrigAngles();

inline int Sin1024(int angle) { return sin1024LookupTable[angle & 0x3FF]; }
inline int Cos1024(int angle) { return cos1024LookupTable[angle & 0x3FF]; }
inline int Tan1024(int angle) { return tan1024LookupTable[angle & 0x3FF]; }
inline int ASin1024(int angle)
{
    if (angle > 0x3FF)
        return 0;
    if (angle < 0)
        return -asin1024LookupTable[-angle];
    return asin1024LookupTable[angle];
}
inline int ACos1024(int angle)
{
    if (angle > 0x3FF)
        return 0;
    if (angle < 0)
        return -acos1024LookupTable[-angle];
    return acos1024LookupTable[angle];
}

inline int Sin512(int angle) { return sin512LookupTable[angle & 0x1FF]; }
inline int Cos512(int angle) { return cos512LookupTable[angle & 0x1FF]; }
inline int Tan512(int angle) { return tan512LookupTable[angle & 0x1FF]; }
inline int ASin512(int angle)
{
    if (angle > 0x1FF)
        return 0;
    if (angle < 0)
        return -asin512LookupTable[-angle];
    return asin512LookupTable[angle];
}
inline int ACos512(int angle)
{
    if (angle > 0x1FF)
        return 0;
    if (angle < 0)
        return -acos512LookupTable[-angle];
    return acos512LookupTable[angle];
}

inline int Sin256(int angle) { return sin256LookupTable[angle & 0xFF]; }
inline int Cos256(int angle) { return cos256LookupTable[angle & 0xFF]; }
inline int Tan256(int angle) { return tan256LookupTable[angle & 0xFF]; }
inline int ASin256(int angle)
{
    if (angle > 0xFF)
        return 0;
    if (angle < 0)
        return -asin256LookupTable[-angle];
    return asin256LookupTable[angle];
}
inline int ACos256(int angle)
{
    if (angle > 0xFF)
        return 0;
    if (angle < 0)
        return -acos256LookupTable[-angle];
    return acos256LookupTable[angle];
}

// Get Arc Tan value
byte ArcTanLookup(int x, int y);

extern uint randSeed;

inline void SetRandSeed(int key) { randSeed = key; }
inline int Rand(int min, int max)
{
    int seed1 = 1103515245 * randSeed + 12345;
    int seed2 = 1103515245 * seed1 + 12345;
    randSeed  = 1103515245 * seed2 + 12345;

    int result = ((randSeed >> 16) & 0x7FF) ^ ((((seed1 >> 6) & 0x1FFC00) ^ ((seed2 >> 16) & 0x7FF)) << 10);
    int size   = abs(max - min);

    if (min > max)
        return (result - result / size * size + max);
    else if (min < max)
        return (result - result / size * size + min);
    else
        return max;
}
inline int RandSeeded(int min, int max, int *randSeed)
{
    if (!randSeed)
        return 0;

    int seed1 = 1103515245 * *randSeed + 12345;
    int seed2 = 1103515245 * seed1 + 12345;
    *randSeed = 1103515245 * seed2 + 12345;

    int result = ((*randSeed >> 16) & 0x7FF) ^ ((((seed1 >> 6) & 0x1FFC00) ^ ((seed2 >> 16) & 0x7FF)) << 10);
    int size   = abs(max - min);

    if (min > max)
        return (result - result / size * size + max);
    else if (min < max)
        return (result - result / size * size + min);
    else
        return max;
}

inline double DegreesToRad(float degrees) { return (M_PI / 180) * degrees; }

#endif // !MATH_H
