#ifndef MACROS_H
#define MACROS_H

#include <stdint.h>

#define TIMING true
#define DEBUG false
#define DEBUG_INPUT false
#define DEBUG_OUT false

/* MISRA type conversion */
#define BOOL(x) static_cast<bool_t>(x)
#define UINT8(x) static_cast<uint8_t>(x)
#define UINT16(x) static_cast<uint16_t>(x)
#define UINT32(x) static_cast<uint32_t>(x)

#define INF 2147483647

#define PI 3.14159265358979
#define toDeg 180/PI
#define toRad PI/180

#define sign(x) ((x)<0 ? -1 : ((x>0) ? 1 : 0))
#define cgclamp(x, a, b) ((x)<a ? a : ((x)>b ? b : (x)))
#define cground(x) (int)((x) + 0.5*sign(x))
#define shift(x, a, b) ( x < a ? x + b : ( x > b ? x - b : x))

inline int fastrand()
{
  static unsigned int g_seed = 42;
  g_seed = (214013 * g_seed + 2531011);
  return (g_seed >> 16) & 0x7FFF;
}

inline int rnd(int b)
{
  return fastrand() % b;
}

inline int rnd(int a, int b)
{
  return a + rnd(b - a + 1);
}

constexpr inline int CantorPairing(int a, int b)
{
  return (((a + b)*(a + b + 1)) / 2 + b);
}

#endif
