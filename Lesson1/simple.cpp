/**
 * 简单画线
 * g++ -std=c++11 simple.cpp ../tgaimage.cpp -o main
 */

#include "../tgaimage.h"
const int width = 500;
const int height = 500;
const TGAColor white = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255,0,0,255);

void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color)
{
    bool steep = false;
    if(std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if(x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (size_t x = x0; x <= x1; x++)
    {
        float t = (x - x0) / (float)(x1 - x0);
        int y = y0 * (1 - t) + y1 * t;
        if(steep)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }
    }
}

int main()
{
    TGAImage image = TGAImage(width, height, TGAImage::RGB);

    line(400, 350, 20, 10, image, white); 
    // line(20, 10, 400, 350, image, red); 
    line(80, 40, 13, 20, image, red);

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}