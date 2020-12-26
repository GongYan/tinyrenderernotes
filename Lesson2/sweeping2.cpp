/**
 * 优化后扫线法画三角形
 *  g++ -std=c++11 sweeping2.cpp ../tgaimage.cpp -o main
 */

#include <cmath>
#include "../tgaimage.h"
#include "../geometry.h"

const int width = 500;
const int height = 500;
const TGAColor white = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255,0,0,255);
const TGAColor green = TGAColor(0,255,0,255);

void triangle(Vec2i p1, Vec2i p2, Vec2i p3, TGAImage& image, const TGAColor& color)
{
    if(p1.y == p2.y && p1.y == p3.y)
        return;
    if(p1.y > p2.y) std::swap(p1, p2);
    if(p1.y > p3.y) std::swap(p1, p3);
    if(p2.y > p3.y) std::swap(p2, p3);
    int total_height = p3.y - p1.y;
    for(int i = 0; i < total_height; i++){
        bool second_half = i > (p2.y - p1.y) || p2.y == p1.y;
        int segment_height = second_half ? (p3.y - p2.y) : (p2.y - p1.y);
        float alpha = (float) i / total_height;
        float beta = (float)(i - ( second_half ? (p2.y - p1.y) : 0)) / segment_height;
        Vec2i A = p1 + (p3 - p1) * alpha;
        Vec2i B = second_half ? (p2 + (p3 - p2) * beta) : (p1 + (p2 - p1) * beta);
        if(A.x > B.x) std::swap(A, B);
        for(int j = A.x; j <= B.x; j++)
            image.set(j, p1.y + i, color);
    }
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