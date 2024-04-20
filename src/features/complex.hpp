#pragma once

#include "feature.hpp"

class Complex : public Feature {
public:
    Complex() : Feature( "Complex" ) {}
    void add_feature( std::unique_ptr<Feature> feature ) {
        feature->_parent = this;
        _sub_features.push_back( std::move(feature) );
    }
    std::vector< glm::ivec3 > get_voxels( std::vector<glm::ivec3> voxels ) override {
        for ( auto &feature : _sub_features ) {
            voxels = feature->get_voxels( voxels );
        }
        return voxels;
    }
};