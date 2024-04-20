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

#include <iostream>

class Feature {
public:
    friend class Complex;
    Feature( std::string name ) {
        _settings["name"] = name;
    }

    void generate( ) {
        generate_vertices( get_voxels( ) );
    }

    void set_buffers( GLuint position_buffer, GLuint normal_buffer, GLuint color_buffer );

    void set_vertex_attributes(
        GLuint position_buffer, GLuint normal_buffer, GLuint color_buffer,
        GLuint position_index, GLuint normal_index, GLuint color_index
    );

    virtual std::vector< glm::ivec3 > get_voxels( std::vector<glm::ivec3> voxels = {} ) = 0;

    void render_tree() {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
        if ( _is_selected )
            flags |= ImGuiTreeNodeFlags_Selected;
        if ( _sub_features.empty() )
            flags |= ImGuiTreeNodeFlags_Leaf;
        if ( ImGui::TreeNodeEx( std::get<std::string>(_settings.at("name")).c_str(), flags ) ) {
            if ( ImGui::IsItemClicked() ) {
                get_root()->disable_all();
                _is_selected = true;
            }
            for ( size_t i=0; i<_sub_features.size(); i++ ) {
                ImGui::PushID(i);
                _sub_features[i]->render_tree();
                ImGui::PopID();
            }
            ImGui::TreePop( );
        }
    }

    void render_settings() {
        for ( auto &setting : _settings ) {
            switch ( setting.second.index() ) {
                case ( 0 ): {
                    if ( ImGui::DragInt( setting.first.c_str(), &std::get<int>(setting.second) ) )
                        get_root()->generate();
                    break;
                }
                case ( 1 ): {
                    if (ImGui::DragFloat( setting.first.c_str(), &std::get<float>(setting.second) ))
                        get_root()->generate();
                    break;
                }
                case ( 2 ): {
                    if ( ImGui::Checkbox( setting.first.c_str(), &std::get<bool>(setting.second) ) )
                        get_root()->generate();
                    break;
                }
                case ( 3 ): {
                    static char buffer[64];
                    std::strncpy(buffer, std::get<std::string>(setting.second).c_str(), 64);
                    ImGui::InputText( setting.first.c_str(), buffer, 64 );
                    setting.second = std::string{ buffer };
                    break;
                }
            }
        }
    }
    
    Feature * get_root() {
        if ( _parent )
            return _parent->get_root();
        return this;
    }

    Feature * get_selected() {
        if ( _is_selected )
            return this;
        for ( auto &feature : _sub_features ) {
            Feature * selected = feature->get_selected();
            if ( selected )
                return selected;
        }
        return nullptr;
    }

    void disable_all() {
        _is_selected = false;
        for ( auto &feature : _sub_features )
            feature->disable_all();
    }

    GLsizei get_vertex_count( );

    glm::mat4 matrix = glm::mat4{ 1.0f };

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