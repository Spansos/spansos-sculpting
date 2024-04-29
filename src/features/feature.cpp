#include "features/feature.hpp"


Feature::Feature( std::string name ) {
    _settings["name"] = name;
}

const std::vector< glm::ivec3 > & Feature::get_voxels( ) {
    return _voxels;
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
                    get_root()->generate_voxels();
                break;
            }
            case ( 1 ): {
                if (ImGui::DragFloat( setting.first.c_str(), &std::get<float>(setting.second) ))
                    get_root()->generate_voxels();
                break;
            }
            case ( 2 ): {
                if ( ImGui::Checkbox( setting.first.c_str(), &std::get<bool>(setting.second) ) )
                    get_root()->generate_voxels();
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
    get_root()->generate_voxels();
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