#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <vector>
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

class Matrix{
private:
    std::vector<std::vector<float> > m;
    int rows, cols;
public:
    Matrix(int r = 4, int c = 4):m(std::vector<std::vector<float> >(r, std::vector<float>(c, 0.0f))), 
        rows(r),cols(c){};

    inline int nrows() { return rows; };
    inline int ncols() { return cols; };

    static Matrix identity(int dimensions){
        Matrix mat(dimensions, dimensions);
        for (int i = 0; i < dimensions; i++)
        {
            for (int j = 0; j < dimensions; j++)
            {
                mat[i][j] = (i == j ? 1.0f : 0.0f);
            }
        }
        return mat;
    };

    std::vector<float>& operator[] (const int i){
        assert(i >= 0 && i < rows);
        return m[i];
    };
    //左向右乘
    Matrix operator* (const Matrix& a){
        assert(cols == a.rows);
        Matrix mat(rows, a.cols);
        for (int i = 0; i < rows; i++)
        {
            for(int j = 0; j < a.cols; j++)
            {
                mat.m[i][j] = 0.0f;
                for(int k = 0; k < cols; k++)
                {
                    mat.m[i][j] += mat.m[i][k] * a.m[k][j];
                }
            }
        }
        return mat;
    };

    //转置阵
    Matrix transpose(){
        Matrix mat(cols, rows);
        for (int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                mat.m[j][i] = m[i][j];
            }
        }
        return mat;
    };

    //逆
    Matrix inverse(){
        assert(rows==cols);
        // augmenting the square matrix with the identity matrix of the same dimensions A => [AI]
        Matrix result(rows, cols*2);
        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++)
                result[i][j] = m[i][j];
        for(int i=0; i<rows; i++)
            result[i][i+cols] = 1;
        // first pass
        for (int i=0; i<rows-1; i++) {
            // normalize the first row
            for(int j=result.cols-1; j>=0; j--)
                result[i][j] /= result[i][i];
            for (int k=i+1; k<rows; k++) {
                float coeff = result[k][i];
                for (int j=0; j<result.cols; j++) {
                    result[k][j] -= result[i][j]*coeff;
                }
            }
        }
        // normalize the last row
        for(int j=result.cols-1; j>=rows-1; j--)
            result[rows-1][j] /= result[rows-1][rows-1];
        // second pass
        for (int i=rows-1; i>0; i--) {
            for (int k=i-1; k>=0; k--) {
                float coeff = result[k][i];
                for (int j=0; j<result.cols; j++) {
                    result[k][j] -= result[i][j]*coeff;
                }
            }
        }
        // cut the identity matrix back
        Matrix truncate(rows, cols);
        for(int i=0; i<rows; i++)
            for(int j=0; j<cols; j++)
                truncate[i][j] = result[i][j+cols];
        return truncate;
    };

    friend std::ostream& operator<<(std::ostream& s, Matrix& m){
        for(int i = 0; i < m.nrows(); i++)
        {
            for(int j = 0; j < m.ncols(); j++)
            {
                s << m[i][j];
                if(j < m.ncols() - 1) s << "\t";
            }
            s << "\n";
        }
        return s;
    };
};

#endif