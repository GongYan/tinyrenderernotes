/**
 * 画三角形：利用重心坐标
 * 
 */
#include <iostream>

#include "../geometry.h"
#include "../tgaimage.h"

const TGAColor red = TGAColor(255,0,0,255);
const int width = 200;
const int height = 200;

/**
 * x向量 = (Bx - Ax, Cx - Ax, Ax - Px)
 * y向量 = (By - Ay, Cy - Ay, Ay - Py)
 * (u,v,1) = x向量 x y向量
 */
Vec3f barycentric(Vec2i* pts, Vec2i P)
{
    Vec3f xVec = Vec3f( pts[1][0] - pts[0][0],
                        pts[2][0] - pts[0][0],
                        pts[0][0] - P.x );
    Vec3f yVec = Vec3f( pts[1][1] - pts[0][1],
                        pts[2][1] - pts[0][1],
                        pts[0][1] - P.y );
    Vec3f ret = xVec ^ yVec;
    if(std::abs(ret[2]) < 1) return Vec3f(-1, 1, 1);
    return Vec3f(1.0 - (ret.x + ret.y)/ret.z, ret.x/ret.z, ret.y/ret.z );
}

void triangle(Vec2i* pts, TGAImage& image, const TGAColor& color)
{
    //找到包围盒
    Vec2i boxmin(image.get_width() - 1, image.get_height() - 1);
    Vec2i boxmax(0, 0);
    Vec2i clamp(image.get_width() - 1, image.get_height() - 1);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            boxmin[j] = std::max(0, std::min(boxmin[j], pts[i][j]));
            boxmax[j] = std::min(clamp[j], std::max(boxmax[j], pts[i][j]));
        }
    }

    Vec2i P;
    for(P.x = boxmin.x; P.x <= boxmax.x; P.x++){
        for(P.y = boxmin.y; P.y <= boxmax.y; P.y++){
            Vec3f screen = barycentric(pts, P);
            // std::cout << " x=> " << screen.x << " y=> " << screen.y << " z=> " << screen.z << std::endl;
            if(screen.x < 0 || screen.y < 0 || screen.z < 0) continue;
            image.set(P.x, P.y, color);
        }
    }
}


int main()
{
    TGAImage image(width, height, TGAImage::RGB);
    Vec2i pts[3] = {Vec2i(10,10), Vec2i(100, 30), Vec2i(190, 160)}; 
    triangle(pts, image, red);
    image.write_tga_file("output.tga");
    return 0;
}