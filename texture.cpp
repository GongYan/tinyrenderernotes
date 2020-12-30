#include "texture.h"

void Texture::load_diffuse(const char* filename)
{
    _diffuseTex.read_tga_file(filename);
    _diffuseTex.flip_vertically();
}

TGAColor Texture::get_diffuse_color(Vec2f uv)
{
    int width = _diffuseTex.get_width();
    int height = _diffuseTex.get_height();
    int posX = (int)(width * uv.x);
    int posY = (int)(height * uv.y);
    return _diffuseTex.get(posX, posY);
}