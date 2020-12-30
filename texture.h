/**
 * 纹理
 */

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "tgaimage.h"
#include "geometry.h"

class Texture
{
private:
    TGAImage _diffuseTex; //漫反射贴图
public:
    void load_diffuse(const char* filename);
    TGAColor get_diffuse_color(Vec2f uv);
};

#endif