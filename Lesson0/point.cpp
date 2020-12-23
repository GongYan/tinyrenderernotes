/**
 * 画一个点
 * g++ -std=c++11 point.cpp ../tgaimage.cpp -o main
 */

#include "../tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const int width = 100;
const int height = 100;

int main()
{
    TGAImage image(width, height, TGAImage::RGB);
    image.set(50, 50, red);
    image.set(60, 60, white);
    image.write_tga_file("output.tga");
    return 0;
}