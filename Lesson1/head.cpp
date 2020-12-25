/**
 * 读取obj画线
 * g++ -std=c++11 head.cpp ../tgaimage.cpp ../draw.cpp ../model.cpp -o main
 */

#include "../tgaimage.h"
#include "../model.h"
#include "../draw.h"

const int width = 500;
const int height = 500;
const TGAColor white = TGAColor(255,255,255,255);
const TGAColor red = TGAColor(255,0,0,255);

int main()
{
    Model* model = new Model("obj/african_head.obj");
    TGAImage image(width, height, TGAImage::RGB);
    for(int i = 0; i < model->nfaces(); i++){
        std::vector<int> face = model->face(i);
        for(int j = 0; j < 3; j++){
            Vec3f v1 = model->vert(face[j]);
            Vec3f v2 = model->vert(face[(j + 1) % 3]);

            Vec2i p1;
            Vec2i p2;
            p1.x = (int)((v1.x + 1.0) * width /2);
            p1.y = (int)((v1.y + 1.0) * height /2);
            p2.x = (int)((v2.x + 1.0) * width /2);
            p2.y = (int)((v2.y + 1.0) * height /2);

            Draw::line(p1, p2, image, white);
        }
    }

//    Vec2i p1(10, 10);
//    Vec2i p2(100, 100);
//    Draw::line(p1, p2, image, white);

    image.write_tga_file("output.tga");
    return 0;
}