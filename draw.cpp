#include "draw.h"

//画线
void Draw::line(Vec2i p1, Vec2i p2, TGAImage& image, const TGAColor& color)
{
    bool steep = false;
    if(std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y))
    {
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
        steep = true;
    }
    if(p1.x > p2.x){
        std::swap(p1, p2);
    }

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int derror2 = std::abs(dy) * 2;
    int error = 0;
    int y = p1.y;
    for(int x = p1.x; x <= p2.x; x++)
    {
        if(steep)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }
        error += derror2;
        if(error > dx)
        {
            y += (p2.y > p1.y ? 1 : -1);
            error -= dx * 2;
        }
    }    
}

//画三角形
Vec3f Draw::barycentric(Vec2i* pts, Vec2i P)
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

void Draw::triangle(Vec2i* pts, TGAImage& image, const TGAColor& color)
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
            Vec3f screen = Draw::barycentric(pts, P);
            if(screen.x < 0 || screen.y < 0 || screen.z < 0) continue;
            image.set(P.x, P.y, color);
        }
    }
}