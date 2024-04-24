#pragma once

#include "feature.hpp"

class Complex : public Feature {
public:
    Complex();
    void add_feature( std::unique_ptr<Feature> feature ) override;
    std::vector< glm::ivec3 > get_voxels( std::vector<glm::ivec3> voxels ) override;
    std::unique_ptr<Feature> copy() override;
};