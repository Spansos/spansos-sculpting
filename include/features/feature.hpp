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
    virtual void generate_voxels() = 0;
    const std::vector< glm::ivec3 > &get_voxels( );
    void render_tree();
    void render_settings();
    void select();
    void disable_all();
    void remove_feature( Feature * feature );
    virtual void add_feature( std::unique_ptr<Feature> feature );
    Feature * get_parent();
    Feature * get_root();
    Feature * get_selected();
    virtual std::unique_ptr<Feature> copy() = 0;
    virtual ~Feature() = default;
    friend class Complex;
protected:
    std::map<std::string, std::variant<int, float, bool, std::string>> _settings;
    Feature * _parent = nullptr;
    std::vector<std::unique_ptr<Feature>> _sub_features;
    std::vector<glm::ivec3> _voxels;
private:
    bool _is_selected = false;
};