#ifndef __DRAW_H__
#define __DRAW_H__

#include <cmath>
#include "tgaimage.h"
#include "geometry.h"

class Draw
{
public:
    static void line(Vec2i& p1, Vec2i& p2, TGAImage&, const TGAColor&);
};

#endif