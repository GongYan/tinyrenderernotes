/**
 * 光照头像
 * g++ -std=c++11 light.cpp ../tgaimage.cpp ../draw.cpp ../model.cpp -o main
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
    //光的位置
    Vec3f light_dir(0, 0, -1);
    for(int i = 0; i < model->nfaces(); i++){
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for(int j = 0; j < 3; j++){
            Vec3f v = model->vert(face[j]);
            screen_coords[j] = Vec2i((v.x + 1.0) * width * 0.5,
                                    (v.y + 1.0) * height * 0.5);
            world_coords[j] = v;
        }
        //求三角形法向量
        Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
        n.normalize();
        float intensity = n * light_dir;
        if(intensity > 0){
            Draw::triangle(screen_coords, image, TGAColor(255 * intensity, 255 * intensity, 255 * intensity, 255));
        }
    }

    image.write_tga_file("output.tga");

    return 0;
}