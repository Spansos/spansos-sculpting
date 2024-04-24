#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <imgui.h>

#include <map>
#include <string>
#include <vector>
#include <array>
#include <variant>
#include <cstring>
#include <memory>
#include <algorithm>

class Feature {
public:
    Feature( std::string name );

    void generate( );

    virtual std::unique_ptr<Feature> copy() = 0;

    void render_tree();
    void render_settings();
    void select();
    void disable_all();
    virtual void add_feature( std::unique_ptr<Feature> feature );
    void remove_feature( Feature * feature );
    Feature * get_parent();
    Feature * get_root();
    Feature * get_selected();

    virtual std::vector< glm::ivec3 > get_voxels( std::vector<glm::ivec3> voxels = {} ) = 0;

    GLsizei get_vertex_count( );
    void set_buffers( GLuint position_buffer, GLuint normal_buffer, GLuint color_buffer );
    void set_vertex_attributes(
        GLuint position_buffer, GLuint normal_buffer, GLuint color_buffer,
        GLuint position_index, GLuint normal_index, GLuint color_index
    );

    virtual ~Feature() = default;

    friend class Complex;
protected:
    std::map<std::string, std::variant<int, float, bool, std::string>> _settings;
    Feature * _parent = nullptr;
    std::vector<std::unique_ptr<Feature>> _sub_features;
private:
    bool _is_selected = false;
    void generate_vertices( std::vector< glm::ivec3 > voxels );
    std::vector<glm::vec3> _positions;
    std::vector<glm::vec3> _normals;
    std::vector<glm::vec3> _colors;
};