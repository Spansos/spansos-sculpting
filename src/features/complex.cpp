#include "features/complex.hpp"

Complex::Complex() : Feature( "Complex" ) { }

void Complex::add_feature( std::unique_ptr<Feature> feature ) {
    feature->_parent = this;
    _sub_features.push_back( std::move(feature) );
    get_root()->generate();
}

std::vector< glm::ivec3 > Complex::get_voxels( std::vector<glm::ivec3> voxels ) {
    for ( auto &feature : _sub_features ) {
        voxels = feature->get_voxels( voxels );
    }
    return voxels;
}

std::unique_ptr<Feature> Complex::copy() {
    auto out = std::make_unique<Complex>();
    out->_settings = _settings;
    out->_parent = _parent;
    for ( auto &feature : _sub_features )
        out->_sub_features.push_back( feature->copy() );
    return out;
}