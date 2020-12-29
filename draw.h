#ifndef __DRAW_H__
#define __DRAW_H__

#include <cmath>
#include "tgaimage.h"
#include "geometry.h"

class Draw
{
public:
    static void line(Vec2i, Vec2i, TGAImage&, const TGAColor&);

    static Vec3f barycentric(Vec2i*, Vec2i);
    static void triangle(Vec2i*, TGAImage&, const TGAColor&);
};

#endif