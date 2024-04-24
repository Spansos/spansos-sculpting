#include "features/feature.hpp"


Feature::Feature( std::string name ) {
    _settings["name"] = name;
}

void Feature::generate( ) {
    generate_vertices( get_voxels( ) );
}

void Feature::render_tree() {
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

void Feature::render_settings() {
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

void Feature::add_feature( std::unique_ptr<Feature> feature ) {
    if ( !_parent )
        return;
    _parent->add_feature( std::move(feature) );
}

void Feature::remove_feature( Feature * feature ) {
    auto as_unique = std::unique_ptr<Feature>(feature);
    auto i = std::remove( _sub_features.begin(), _sub_features.end(), as_unique );
    _sub_features.erase( i, _sub_features.end() );
    as_unique.release();
    get_root()->generate();
}

Feature * Feature::get_parent() {
    return _parent;
}
    
Feature * Feature::get_root() {
    if ( _parent )
        return _parent->get_root();
    return this;
}

Feature * Feature::get_selected() {
    if ( _is_selected )
        return this;
    for ( auto &feature : _sub_features ) {
        Feature * selected = feature->get_selected();
        if ( selected )
            return selected;
    }
    return nullptr;
}

void Feature::select() {
    _is_selected = true;
}

void Feature::disable_all() {
    _is_selected = false;
    for ( auto &feature : _sub_features )
        feature->disable_all();
}

void Feature::set_buffers( GLuint position_buffer, GLuint normal_buffer, GLuint color_buffer ) {
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, _positions.size() * sizeof(glm::vec3), _positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), _normals.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, _colors.size() * sizeof(glm::vec3), _colors.data(), GL_STATIC_DRAW);
}

void Feature::set_vertex_attributes(
    GLuint position_buffer, GLuint normal_buffer, GLuint color_buffer,
    GLuint position_index, GLuint normal_index, GLuint color_index
) {
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glVertexAttribPointer( position_index, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glVertexAttribPointer( normal_index, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glVertexAttribPointer( color_index, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
}

GLsizei Feature::get_vertex_count( ) {
    return _positions.size();
}

void Feature::generate_vertices( std::vector< glm::ivec3 > voxels ) {
    _positions.clear();
    _normals.clear();
    _colors.clear();

    for ( auto i : voxels ) {
        _positions.push_back( i );
        _normals.push_back( {-1,0,0 } );
        _positions.push_back( i+glm::ivec3{0,0,1} );
        _normals.push_back( {-1,0,0 } );
        _positions.push_back( i+glm::ivec3{0,1,0} );
        _normals.push_back( {-1,0,0 } );
        
        _positions.push_back( i+glm::ivec3(0,1,0) );
        _normals.push_back( {-1,0,0 } );
        _positions.push_back( i+glm::ivec3{0,0,1} );
        _normals.push_back( {-1,0,0 } );
        _positions.push_back( i+glm::ivec3{0,1,1} );
        _normals.push_back( {-1,0,0 } );

        _positions.push_back( i );
        _normals.push_back( {0,-1,0 } );
        _positions.push_back( i+glm::ivec3{1,0,0} );
        _normals.push_back( {0,-1,0 } );
        _positions.push_back( i+glm::ivec3{0,0,1} );
        _normals.push_back( {0,-1,0 } );

        _positions.push_back( i+glm::ivec3{0,0,1} );
        _normals.push_back( {0,-1,0 } );
        _positions.push_back( i+glm::ivec3{1,0,0} );
        _normals.push_back( {0,-1,0 } );
        _positions.push_back( i+glm::ivec3{1,0,1} );
        _normals.push_back( {0,-1,0 } );

        _positions.push_back( i );
        _normals.push_back( { 0,0,-1 } );
        _positions.push_back( i+glm::ivec3{0,1,0} );
        _normals.push_back( { 0,0,-1 } );
        _positions.push_back( i+glm::ivec3{1,0,0} );
        _normals.push_back( { 0,0,-1 } );

        _positions.push_back( i+glm::ivec3{1,0,0} );
        _normals.push_back( { 0,0,-1 } );
        _positions.push_back( i+glm::ivec3{0,1,0} );
        _normals.push_back( { 0,0,-1 } );
        _positions.push_back( i+glm::ivec3{1,1,0} );
        _normals.push_back( { 0,0,-1 } );
        
        _positions.push_back( i+glm::ivec3{1,0,0} );
        _normals.push_back( {1,0,0 } );
        _positions.push_back( i+glm::ivec3{1,1,0} );
        _normals.push_back( {1,0,0 } );
        _positions.push_back( i+glm::ivec3{1,0,1} );
        _normals.push_back( {1,0,0 } );
        
        _positions.push_back( i+glm::ivec3{1,0,1} );
        _normals.push_back( {1,0,0 } );
        _positions.push_back( i+glm::ivec3(1,1,0) );
        _normals.push_back( {1,0,0 } );
        _positions.push_back( i+glm::ivec3{1,1,1} );
        _normals.push_back( {1,0,0 } );

        _positions.push_back( i+glm::ivec3{0,1,0} );
        _normals.push_back( {0,1,0} );
        _positions.push_back( i+glm::ivec3{0,1,1} );
        _normals.push_back( {0,1,0} );
        _positions.push_back( i+glm::ivec3{1,1,0} );
        _normals.push_back( {0,1,0} );

        _positions.push_back( i+glm::ivec3{1,1,0} );
        _normals.push_back( {0,1,0 } );
        _positions.push_back( i+glm::ivec3{0,1,1} );
        _normals.push_back( {0,1,0 } );
        _positions.push_back( i+glm::ivec3{1,1,1} );
        _normals.push_back( {0,1,0 } );

        _positions.push_back( i+glm::ivec3{0,0,1} );
        _normals.push_back( {0,0,1} );
        _positions.push_back( i+glm::ivec3{1,0,1} );
        _normals.push_back( {0,0,1} );
        _positions.push_back( i+glm::ivec3{0,1,1} );
        _normals.push_back( {0,0,1} );

        _positions.push_back( i+glm::ivec3{0,1,1} );
        _normals.push_back( {0,0,1} );
        _positions.push_back( i+glm::ivec3{1,0,1} );
        _normals.push_back( {0,0,1} );
        _positions.push_back( i+glm::ivec3{1,1,1} );
        _normals.push_back( {0,0,1} );
        
        for ( int i=0; i<36; i++ )
            _colors.push_back( { 1, 0, 0 } );
    }
}