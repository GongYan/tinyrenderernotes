#ifndef __DRAW_H__
#define __DRAW_H__

#include <cmath>
#include "tgaimage.h"
#include "geometry.h"

class Draw
{
public:
    static void line(Vec2i, Vec2i, TGAImage&, const TGAColor&);

    static Vec3f barycentric(Vec3f*, Vec3f);
    static void triangle(Vec3f*, float*, TGAImage&, const TGAColor&);
};

#endif