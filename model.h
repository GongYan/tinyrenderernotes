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
    std::vector<Vec3f> _verts;
    std::vector< std::vector<int> > _faces;
public:
    Model(const char * filename);
    ~Model();
    int nverts();
    int nfaces();
    Vec3f vert(int i);
    std::vector<int> face(int idx);
};

#endif