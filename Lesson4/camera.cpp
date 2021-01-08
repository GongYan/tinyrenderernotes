/**
 * 透视投影
 * g++ -std=c++11 camera.cpp ../tgaimage.cpp ../texture.cpp draw.cpp ../model.cpp -o main
 */

#include <vector>
#include <cmath>
#include <limits>
#include "draw.h"
#include "../tgaimage.h"
#include "../model.h"
#include "../geometry.h"
#include "../texture.h"

Model* model = nullptr;
Texture* texture = nullptr;
float* zbuffer = nullptr;
Vec3f light_dir(0, 0, -1);
Vec3f camera(0, 0, 3);

int main()
{
    model = new Model("obj/african_head.obj");
    texture = new Texture();
    texture->load_diffuse("obj/african_head_diffuse.tga");

    zbuffer = new float[width * height];
    for(int i = 0; i < width * height; i++){
        zbuffer[i] = std::numeric_limits<float>::min();
    }

    {
        Matrix projection = Matrix::identity(4);
        Matrix vp = Matrix::viewport(width/8, height/8, width * 3/4, height * 3/4);
        projection[3][2] = -1.f/camera.z;
        
        TGAImage image(width, height, TGAImage::RGB);
        for(int i = 0; i < model->nfaces(); i++){
            std::vector<int> face = model->face(i);
            Vec3f screen_coords[3];
            Vec3f world_coords[3];
            for(int j = 0; j < 3; j++){
                Vec3f p = model->vert(face[3 * j]);
                screen_coords[j] = Matrix::m2v(vp * projection * Matrix::v2m(p));
                world_coords[j] = p;
            }

            Vec3f n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
            n.normalize();
            float intensity = n * light_dir;
            if(intensity > 0){
                Vec2f uv[3];
                for(int k = 0; k < 3; k++){
                    uv[k] = model->uv(face[ 3 * k + 1]);
                }
                Draw::triangle(screen_coords,uv, zbuffer, image, texture );
            }
        }
        image.write_tga_file("output.tga");
    }

    {
        //zbuffer texture
        TGAImage zbimage(width, height, TGAImage::RGB);
        for (int i = 0; i < width; i++)
        {
            for(int j = 0; j < height; j++)
            {
                float value = zbuffer[i + j * width];
                TGAColor color(value, value, value, 255);
                zbimage.set(i, j, color);
            }
        }
        zbimage.write_tga_file("zbuffer.tga");
    }

    delete model;
    delete [] zbuffer;
    return 0;
}