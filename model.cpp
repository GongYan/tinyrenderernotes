#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include "model.h"

Model::Model(const char * filename): _verts(), _faces() {    
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    char trash;
    float ftrash;
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        if(!line.compare(0, 2, "v ")){ //模型顶点列表
            iss >> trash;
            Vec3f v;
            for(int i = 0; i < 3; i++) iss >> v.raw[i];
            _verts.push_back(v);
        }else if(!line.compare(0, 2, "vn")){ //顶点法线列表
            iss >> trash >> trash;
            Vec3f vn;
            for(int i = 0; i < 3; i++) iss >> vn[i];
            _normals.push_back(vn);
        }else if(!line.compare(0, 2, "vt")){ //模型顶点的纹理坐标列表
            iss >> trash >> trash;
            Vec2f vt;
            for(int i = 0; i < 2; i++) iss >> vt[i];
            _uvs.push_back(vt);
        }else if(!line.compare(0, 2, "f ")){ //模型的三角面列表
            //顶点/纹理坐标/法线索引值
            std::vector<int> f;
            int poIdx, uvIdx, norIdx;
            iss >> trash;
            while (iss >> poIdx >> trash >> uvIdx >> trash >> norIdx) {
                poIdx--;
                uvIdx--;
                norIdx--;
                f.push_back(poIdx);
                f.push_back(uvIdx);
                f.push_back(norIdx);
            }
            _faces.push_back(f);
        }
    }
    in.close();
    std::cerr << "# v# " << _verts.size() << " f# " << _faces.size() << std::endl;
}

Model::~Model(){

}

int Model::nverts(){
    return (int)_verts.size();
}

int Model::nfaces(){
    return (int)_faces.size();
}

Vec3f Model::vert(int i){
    return _verts[i];
}

Vec3f Model::normal(int i)
{
    return _normals[i];
}

Vec2f Model::uv(int i)
{
    return _uvs[i];
}

std::vector<int> Model::face(int idx){
    return _faces[idx];
}