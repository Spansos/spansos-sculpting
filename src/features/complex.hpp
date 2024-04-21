#pragma once

#include "feature.hpp"

class Complex : public Feature {
public:
    Complex() : Feature( "Complex" ) {}
    void add_feature( std::unique_ptr<Feature> feature ) override {
        feature->_parent = this;
        _sub_features.push_back( std::move(feature) );
        get_root()->generate();
    }
    std::vector< glm::ivec3 > get_voxels( std::vector<glm::ivec3> voxels ) override {
        for ( auto &feature : _sub_features ) {
            voxels = feature->get_voxels( voxels );
        }
        return voxels;
    }
    std::unique_ptr<Feature> copy() override {
        auto out = std::make_unique<Complex>();
        out->_settings = _settings;
        out->_parent = _parent;
        for ( auto &feature : _sub_features )
            out->_sub_features.push_back( feature->copy() );
        return out;
    }
};