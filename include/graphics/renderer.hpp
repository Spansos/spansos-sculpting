#pragma once

#include <GL/glew.h>
#include <string>
#include "graphics/window.hpp"
#include "graphics/mesh.hpp"

class Renderer {
public:
    Renderer( std::string fragment_shader, std::string vertex_shader );
    ~Renderer();
    void draw( Window & window, const Mesh & mesh );
    void set_mvp( glm::mat4 mvp );
private:
    GLuint _vertex_array_id;
    GLuint _program_id;
    GLuint _position_buffer_id;
    GLuint _normal_buffer_id;
    GLuint _color_buffer_id;
    GLuint _mvp_id;
    glm::mat4 _mvp;
};