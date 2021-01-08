#ifndef __DRAW_H__
#define __DRAW_H__

#include <cmath>
#include "../tgaimage.h"
#include "../geometry.h"
#include "../model.h"
#include "../texture.h"

class Draw
{
public:
    static void line(Vec2i, Vec2i, TGAImage&, const TGAColor&);

    static Vec3f barycentric(Vec3f*, Vec3f);
    static void triangle(Vec3f*, Vec2f*, float*, TGAImage&, Texture* );
};

#endif