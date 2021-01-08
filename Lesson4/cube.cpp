/**
 * 缩放
 * g++ -std=c++11 cube.cpp ../tgaimage.cpp ../texture.cpp draw.cpp ../model.cpp -o main
 */

#include <vector>
#include <iostream>
#include <cmath>
#include "../tgaimage.h"
#include "../model.h"
#include "../geometry.h"
#include "draw.h"

const TGAColor white  = TGAColor(255, 255, 255, 255);
const TGAColor red    = TGAColor(255, 0,   0,   255);
const TGAColor green  = TGAColor(0,   255, 0,   255);
const TGAColor blue   = TGAColor(0,   0,   255, 255);
const TGAColor yellow = TGAColor(255, 255, 0,   255);

Model* model = nullptr;

int main()
{
    model = new Model("obj/cube.obj");

    TGAImage image(width, height, TGAImage::RGB);
    Matrix vp = Matrix::viewport(width * 0.25, height * 0.25, width * 0.5, height * 0.5);
    Vec3f x(1.f, 0.f, 0.f), y(0.f, 1.f, 0.f), o(0.f, 0.f, 0.f);
    o = Matrix::m2v(vp * Matrix::v2m(o));
    x = Matrix::m2v(vp * Matrix::v2m(x));
    y = Matrix::m2v(vp * Matrix::v2m(y));
    Draw::line(Vec2i((int)o.x, (int)o.y), Vec2i((int)x.x, (int)x.y), image, red);
    Draw::line(Vec2i((int)o.x, (int)o.y), Vec2i((int)y.x, (int)y.y), image, green);

    for(int i = 0; i < model->nfaces(); i++)
    {
        std::vector<int> face = model->face(i);
        for(int j = 0; j < 3; j++)
        {
            Vec3f p0 = model->vert(face[3 * j]);
            Vec3f p1 = model->vert(face[(3 * (j+1))%face.size()]);
            {
                // 原始模型
                Vec3f sp0 = Matrix::m2v(vp * Matrix::v2m(p0));
                Vec3f sp1 = Matrix::m2v(vp * Matrix::v2m(p1));
                Draw::line(Vec2i((int)sp0.x, (int)sp0.y), Vec2i((int)sp1.x, (int)sp1.y), image, white);
            }

            {
                // 转换后
                // Matrix t = Matrix::zoom(1.5);
                Matrix t = Matrix::translation(Vec3f(.33, .5, 0))* Matrix::rotation_z(cos(10.*M_PI/180.), sin(10.*M_PI/180.));
                Vec3f sp0 = Matrix::m2v(vp * t * Matrix::v2m(p0));
                Vec3f sp1 = Matrix::m2v(vp * t * Matrix::v2m(p1));
                Draw::line(Vec2i((int)sp0.x, (int)sp0.y), Vec2i((int)sp1.x, (int)sp1.y), image, yellow);
            }
        }
    }

    image.write_tga_file("output.tga");
    delete model;
    return 0;
}
