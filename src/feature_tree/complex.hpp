#pragma once

#include "feature.hpp"

class Complex : public Feature {
public:
    void add_feature( std::unique_ptr<Feature> feature ) {
        _sub_features.push_back( std::move(feature) );
    }
    std::vector< glm::ivec3 > get_voxels( std::vector<glm::ivec3> voxels ) override {
        for ( auto &feature : _sub_features ) {
            voxels = feature->get_voxels( voxels );
        }
        return voxels;
    }
private:
    std::vector<std::unique_ptr<Feature>> _sub_features;
};