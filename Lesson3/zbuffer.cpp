/**
 * z缓冲
 * 
 */

#include "../tgaimage.h"
#include "../model.h"


const int width = 500;
const int height = 500;

Vec3f barycentric(Vec3f A, Vec3f B, Vec3f C, Vec3f P)
{
    Vec3f s[2];
    for( int i = 1; i >= 0; i--){
        s[i][0] = C[i] - A[i];
        s[i][1] = B[i] - A[i];
        s[i][2] = A[i] - P[i];
    }

    Vec3f u = s[0] ^ s[1];
    if(std::abs(u[2]) > 1e-2) 
        return Vec3f(1.0f - (u.x + u.y)/u.z, u.x/u.z, u.y/u.z);
    return Vec3f(-1, 1, 1);
}

void triangle(Vec3f* pts, float* zbuffer, TGAImage& image, const TGAColor& color)
{
    Vec2f boxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
    Vec2f boxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
    Vec2f clamp(image.get_width() -1, image.get_height() -1);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 2; j++){
            boxmin[j] = std::max(0.0f, std::min(boxmin[j], pts[i][j]));
            boxmax[j] = std::min(clamp[j], std::max(boxmax[j], pts[i][j]));
        }
    }

    Vec3f P;
    for(P.x = boxmin.x; P.x <= boxmax.x; P.x++){
        for(P.y = boxmin.y; P.y <= boxmax.y; P.y++){
            Vec3f screen = barycentric(pts[0], pts[1], pts[2], P);
            if(screen.x < 0 || screen.y < 0 || screen.z < 0) continue;
            P.z = 0;
            for(int i = 0; i < 3; i++) P.z += pts[i][2] * screen[i];
            if(zbuffer[int(P.x + P.y * width)] < P.z ){
                zbuffer[int(P.x + P.y * width)] = P.z;
                image.set(P.x, P.y, color);
            }
        }
    }
}

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
        triangle(pts, zbuffer, image, TGAColor(rand()%255, rand()%255,rand()%255, 255));
    }

    image.write_tga_file("output.tga");
    return 0;
}