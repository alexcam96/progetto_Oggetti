#ifndef FACE_H_
#define FACE_H_

#include "../OpenGL.h"
#include "../internal.h"
#include "Material.h"

namespace game {

class Face {
private:
    int nVertex_;
    GLuint vao_, vbo_[3], drawMode_;
public:
    Face(int vertexCount, glm::vec3 *vertex, glm::vec2 *uvmap,
         glm::vec3 *normal, GLint mode);
    int getVertexCount();
    void render();
    virtual ~Face();


	//**************************** MODIFICHE ****************************
	/*bool operator==(const Face& right) const {
		if(right.drawMode_ == drawMode_ and right.nVertex_ == nVertex_ and right.vao_ == vao_ and right.vbo_ == vbo_)
			return true;
		else return false;
	}*/
/*	std::string toString() {
		std::string s = std::to_string(nVertex_) + ' ' + std::to_string(vao_);
		s += ' ' + std::to_string(vbo_[0]) + ' ' + std::to_string(vbo_[1]) + ' ' + std::to_string(vbo_[2]) + ' ' + std::to_string(drawMode_);
		return s;
	}*/
	//*******************************************************************
};

}

#endif
