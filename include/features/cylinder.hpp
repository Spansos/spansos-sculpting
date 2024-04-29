#pragma once

#include "feature.hpp"

class Cylinder : public Feature {
public:
    Cylinder( int length, float radius );
    void generate_voxels() override;
    std::unique_ptr<Feature> copy() override;
};