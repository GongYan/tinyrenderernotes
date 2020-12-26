/**
 * 线框三角形
 * g++ -std=c++11 simple.cpp ../tgaimage.cpp ../draw.cpp -o main
 */

#include <cmath>
#include "../tgaimage.h"
#include "../draw.h"
#include "../geometry.h"

const int width = 500;
const int height = 500;
const TGAColor white = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255,0,0,255);
const TGAColor green = TGAColor(0,255,0,255);

void triangle(Vec2i& p1, Vec2i& p2, Vec2i& p3, TGAImage& image, const TGAColor& color)
{
    Draw::line(p1, p2, image, color);
    Draw::line(p2, p3, image, color);
    Draw::line(p3, p1, image, color);
}

int main()
{
    TGAImage image(width, height, TGAImage::RGB);
    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)}; 
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)}; 
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)}; 

    triangle(t0[0], t0[1], t0[2], image, red); 
    triangle(t1[0], t1[1], t1[2], image, white); 
    triangle(t2[0], t2[1], t2[2], image, green);

    image.write_tga_file("output.tga");
    return 0;
}