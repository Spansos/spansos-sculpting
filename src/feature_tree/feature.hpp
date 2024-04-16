#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include <vector>


class Feature {
public:
    void generate( ) {
        generate_vertices( get_voxels( ) );
    }
    void set_buffers( GLuint position_buffer, GLuint normal_buffer, GLuint color_buffer );
    void set_vertex_attributes(
        GLuint position_buffer, GLuint normal_buffer, GLuint color_buffer,
        GLuint position_index, GLuint normal_index, GLuint color_index
    );
    GLsizei get_vertex_count( );
    virtual std::vector< glm::ivec3 > get_voxels( std::vector<glm::ivec3> voxels = {} ) = 0;
    glm::mat4 matrix = glm::mat4{ 1.0f };
private:
    void generate_vertices( std::vector< glm::ivec3 > voxels );
    std::vector<glm::vec3> _positions;
    std::vector<glm::vec3> _normals;
    std::vector<glm::vec3> _colors;
};