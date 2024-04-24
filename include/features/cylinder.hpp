#pragma once

#include "feature.hpp"

class Cylinder : public Feature {
public:
    Cylinder( int length, float radius );
    std::vector< glm::ivec3 > get_voxels( std::vector<glm::ivec3> voxels = {} ) override;
    std::unique_ptr<Feature> copy() override;
};