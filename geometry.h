#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <ostream>
#include <cmath>

template<class T>
struct Vec2
{
    union
    {
        struct { T u, v; };
        struct { T x, y; };
        T raw[2];
    };
    Vec2():u(0),v(0) {}
    Vec2(T _u, T _v):u(_u),v(_v) {}

    inline T& operator [](int index){
        if (index == 0) return x;
        else if(index == 1) return y;
        throw;
    }

    inline Vec2<T> operator +(const Vec2<T> &V) const{
        return Vec2<T>(u + V.u, v + V.v);
    }
    inline Vec2<T> operator -(const Vec2<T> &V) const{
        return Vec2<T>(u - V.u, v - V.v);
    }
    inline Vec2<T> operator *(float f) const{
        return Vec2<T>(u * f, v * f);
    }

    template<class> friend std::ostream& operator <<(std::ostream& s, Vec2<T>& v);
};

template<class T> 
struct Vec3
{
    union
    {
        struct {T x, y, z;};
        struct {T ivert, iuv, inorm;};
        T raw[3];
    };
    Vec3():x(0), y(0), z(0) {}
    Vec3(T _x, T _y, T _z): x(_x), y(_y), z(_z) {}

    inline T& operator [](int index) {
        if(index == 0) return x;
        else if(index == 1) return y;
        else if(index == 2) return z;
        throw;
    }

    //叉乘：公式 （a.y*b.z-b.y*a.z , b.x*a.z-a.x*b.z  , a.x*b.y-b.x*a.y）
    inline Vec3<T> operator ^(const Vec3<T> &V) const {
        return Vec3<T>(y * V.z - V.y * z, V.x * z - x * V.z, x * V.y - V.x * y);
    }
    inline Vec3<T> operator +(const Vec3<T> &V) const {
        return Vec3(x + V.x, y + V.y, z + V.z);
    }
    inline Vec3<T> operator -(const Vec3<T> &V) const {
        return Vec3(x - V.x, y - V.y, z - V.z);
    }
    inline Vec3<T> operator *(float f) const {
        return Vec3<T>(x * f, y * f, z * f);
    }
    //点乘 
    inline T operator *(const Vec3<T> &V) const {
        return x * V.x + y * V.y + z * V.z;
    }
    float norm() const {
        return std::sqrt(x * x + y * y + z * z);
    }
    //归一
    Vec3<T>& normalize(T V = 1) {
        *this = (*this) * (V / norm());
        return *this;
    }

    template<class> friend std::ostream& operator <<(std::ostream& s, Vec3<T>& v);
};

template<class T> 
std::ostream& operator <<(std::ostream& s, Vec2<T>& v){
    s << "(" << v.x << ", " << v.y << ")\n";
    return s;
}

template<class T>
std::ostream& operator <<(std::ostream& s, Vec3<T>& v){
    s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
    return s;
}

//常用的类型
typedef Vec2<float> Vec2f;
typedef Vec2<int>   Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int>   Vec3i;


#endif