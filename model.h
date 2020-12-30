/**
 * 解析obj文件
 */

#ifndef __MODEL_H__
#define __MODEL_H__

#include "geometry.h"
#include <vector>

class Model
{
private:
    std::vector<Vec3f> _normals;            //法向量
    std::vector<Vec2f> _uvs;                //纹理坐标
    std::vector<Vec3f> _verts;              //顶点
    std::vector< std::vector<int> > _faces; //面：记录顶点/纹理坐标/法线索引值
public:
    Model(const char * filename);
    ~Model();
    int nverts();
    int nfaces();
    Vec3f vert(int i);
    Vec3f normal(int i);
    Vec2f uv(int i);
    std::vector<int> face(int idx);
};

#endif