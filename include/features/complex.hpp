#pragma once

#include "feature.hpp"

class Complex : public Feature {
public:
    Complex();
    void add_feature( std::unique_ptr<Feature> feature ) override;
    void generate_voxels( ) override;
    std::unique_ptr<Feature> copy() override;
};