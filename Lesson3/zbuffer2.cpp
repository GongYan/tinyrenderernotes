/**
 * z缓冲
 * g++ -std=c++11 zbuffer2.cpp ../tgaimage.cpp ../draw.cpp ../model.cpp -o main
 */

#include "../tgaimage.h"
#include "../model.h"
#include "../draw.h"

const int width = 500;
const int height = 500;

Vec3f world2screen(const Vec3f& v){
    return Vec3f( int((v.x + 1.0) * width * 0.5 + 0.5),
                  int((v.y + 1.0) * height * 0.5 + 0.5), v.z);
}

int main()
{
    Model* model = new Model("obj/african_head.obj");
    TGAImage image(width, height, TGAImage::RGB);
    float* zbuffer = new float[width * height];
    for(int i = 0; i < width * height; i++)
        zbuffer[i] = -std::numeric_limits<float>::max();
    for(int i = 0; i < model->nfaces(); i++){
        std::vector<int> face = model->face(i);
        Vec3f pts[3];
        for(int i = 0; i < 3; i++) pts[i] = world2screen(model->vert(face[i]));
        Draw::triangle(pts, zbuffer, image,  TGAColor(rand()%255, rand()%255,rand()%255, 255));
    }
    image.write_tga_file("output.tga");
    return 0;
}