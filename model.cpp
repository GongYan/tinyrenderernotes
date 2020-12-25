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
    while (!in.eof())
    {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        if(!line.compare(0, 2, "v ")){
            iss >> trash;
            Vec3f v;
            for(int i = 0; i < 3; i++) iss >> v.raw[i];
            _verts.push_back(v);
        }else if(!line.compare(0, 2, "f ")){
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while (iss >> idx >> trash >> itrash >> trash >> itrash) {
                idx--;
                f.push_back(idx);
            }
            _faces.push_back(f);
        }
    }
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

std::vector<int> Model::face(int idx){
    return _faces[idx];
}