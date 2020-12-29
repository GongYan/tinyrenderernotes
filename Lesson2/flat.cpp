/**
 * 头像模型 填充随机色
 * g++ -std=c++11 flat.cpp ../tgaimage.cpp ../draw.cpp ../model.cpp -o main
 */

#include <iostream>
#include "../tgaimage.h"
#include "../model.h"
#include "../draw.h"

const TGAColor red = TGAColor(255,0,0,255);
const int width = 500;
const int height = 500;

int main()
{
    Model* model = new Model("obj/african_head.obj");
    TGAImage image(width, height, TGAImage::RGB);
    for(int i = 0; i < model->nfaces(); i++){
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        for(int j = 0; j < 3; j++){
            Vec3f world_coords = model->vert(face[j]);
            screen_coords[j] = 
            Vec2i((world_coords.x + 1.0 ) * width * 0.5,
                    (world_coords.y + 1.0) * height * 0.5);
        }
        Draw::triangle(screen_coords, image, TGAColor( rand()* 255, rand()* 255,rand()* 255));
    }

    image.write_tga_file("output.tga");
    return 0;
}