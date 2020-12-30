/**
 * 贴图
 * g++ -std=c++11 texture.cpp ../tgaimage.cpp ../texture.cpp draw.cpp ../model.cpp -o main
 */
#include <iostream>
#include "draw.h"
#include "../tgaimage.h"
#include "../model.h"
#include "../texture.h"

Model* model = nullptr;
Texture* texture = nullptr;

const int width = 600;
const int height = 600;

Vec3f world2screen(const Vec3f& v){
    return Vec3f( int((v.x + 1.0) * width * 0.5 + 0.5),
                  int((v.y + 1.0) * height * 0.5 + 0.5), v.z);
}

int main()
{
    //模型
    model = new Model("obj/african_head.obj");
    //纹理
    texture = new Texture();
    texture->load_diffuse("obj/african_head_diffuse.tga");
    //zbuffer
    float* zbuffer = new float[width*height];
    for(int i = 0; i < width*height; i++)
        zbuffer[i] = -std::numeric_limits<float>::max();

    TGAImage image(width, height, TGAImage::RGB);

    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3f world_coords[3];
        Vec3f screen_coords[3];
        Vec2f uvs[3];
        for (int j = 0; j < 3; j++) {
            world_coords[j] = model->vert(face[3*j]);
            screen_coords[j] = world2screen(world_coords[j]);
            uvs[j] = model->uv(face[3*j+1]);
        }
        Draw::triangle(screen_coords, uvs,zbuffer,image, texture );
    }

    image.write_tga_file("output.tga");
    return 0;
}