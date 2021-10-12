#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <math.h>
#include <functional>

#include "util/Macros.h"

template<class T>
class Vec2
{
public:
  T x, y;
  inline Vec2<T>() { this->x = -1; this->y = -1; }
  inline Vec2<T>(T x, T y) { this->x = x; this->y = y; }
  inline Vec2<T> operator + (const Vec2<T> &v) { return Vec2<T>(this->x + v.x, this->y + v.y); }
  inline Vec2<T> operator + (const Vec2<T> &v) const { return Vec2<T>(this->x + v.x, this->y + v.y); }
  inline Vec2<T> operator - (const Vec2<T> &v) { return Vec2<T>(this->x - v.x, this->y - v.y); }
  inline Vec2<T> operator - (const Vec2<T> &v) const { return Vec2<T>(this->x - v.x, this->y - v.y); }
  template<class T2> inline Vec2<T> operator * (const T2 &i) { return Vec2<T>(this->x * i, this->y * i); }
  template<class T2> inline Vec2<T> operator * (const T2 &i) const { return Vec2<T>(this->x * i, this->y * i); }
  inline Vec2<T> operator * (const Vec2<T> &v) { return Vec2<T>(this->x * v.x, this->y * v.y); }
  inline Vec2<T> operator * (const Vec2<T> &v) const { return Vec2<T>(this->x * v.x, this->y * v.y); }
  template<class T2> inline Vec2<T> operator / (const T2 &i) { return Vec2<T>(this->x / i, this->y / i); }
  template<class T2> inline Vec2<T> operator / (const T2 &i) const { return Vec2<T>(this->x / i, this->y / i); }
  inline Vec2<T> operator / (const Vec2<T> &v) { return Vec2<T>(this->x / v.x, this->y / v.y); }
  inline Vec2<T> operator / (const Vec2<T> &v) const { return Vec2<T>(this->x / v.x, this->y / v.y); }
  inline Vec2<T> operator += (const Vec2<T> &v) { return *this = *this + v; }
  inline Vec2<T> operator -= (const Vec2<T> &v) { return *this = *this - v; }
  inline Vec2<T> operator *= (const Vec2<T> &v) { return *this = *this * v; }
  template<class T2> inline Vec2<T> operator *= (const T2 &i) { return *this = *this * i; }
  inline Vec2<T> operator /= (const Vec2<T> &v) { return *this = *this / v; }
  template<class T2> inline Vec2<T> operator /= (const T2 &i) { return *this = *this / i; }
  inline bool operator == (const Vec2<T> &v) { return this->x == v.x && this->y == v.y; }
  inline bool operator == (const Vec2<T> &v) const { return this->x == v.x && this->y == v.y; }
  inline bool operator != (const Vec2<T> &v) { return this->x != v.x || this->y != v.y; }
  inline Vec2<int> Round()const { return Vec2<int>(round(x), round(y)); };
  inline int dist(const Vec2<T> &v) { return (abs(this->x - v.x) + abs(this->y - v.y)); };
  inline T dot(const Vec2<T> &v)const { return this->x * v.x + this->y * v.y; };
  inline T cross(const Vec2<T> &v)const { return this->x * v.y - this->y * v.x; };
  inline T lengthSq()const { return this->dot(*this); };
  inline float length()const { return sqrt(this->lengthSq()); };
  inline Vec2<float> normalize()const { return Vec2<float>(this->x, this->y) / this->length(); };
  inline Vec2<T> negate() const { return Vec2<T>(-this->x, -this->y); }
};
using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
template<class T> std::istream &operator >> (std::istream &is, Vec2<T> &v) { return is >> v.x >> v.y; };
template<class T> std::ostream &operator << (std::ostream &os, const Vec2<T> &v) { return os << v.x << " " << v.y; };
/* cantor pairing function */
template<class T>  bool operator < (const Vec2<T> &v, const Vec2<T> &w) { return (CantorPairing(v.x, v.y) < CantorPairing(w.x, w.y)); }

inline bool isClockwise(Vec2f a, Vec2f b) { return a.normalize().cross(b.normalize()) <= 0; }
inline float getCosAngle(Vec2f a, Vec2f b) { return a.normalize().dot(b.normalize()); }
inline float getAngle(Vec2f a, Vec2f b) { return acos(getCosAngle(a, b))*toDeg; }
inline float getSignedAngle(Vec2f a, Vec2f b) { return acos(cgclamp(getCosAngle(a, b), -1, 1))*(isClockwise(a, b) ? -1 : 1) * toDeg; }
inline float getAbsoluteAngle(Vec2f vec) { return acos(vec.normalize().dot(Vec2f(1, 0)))*sign(vec.y) * toDeg; }

namespace std
{
  template <class T>
  class hash<Vec2<T>>
  {
  public:
    size_t operator()(const Vec2<T> &v) const{
      return (hash<T>{}(v.x)^(hash<T>{}(v.y) << 1)); 
    }
  };
}

#endif
