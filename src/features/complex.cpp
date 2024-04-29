#include "features/complex.hpp"

Complex::Complex() : Feature( "Complex" ) { }

void Complex::add_feature( std::unique_ptr<Feature> feature ) {
    feature->_parent = this;
    _sub_features.push_back( std::move(feature) );
    get_root()->generate_voxels();
}

void Complex::generate_voxels() {
    _voxels.clear();
    for ( auto &feature : _sub_features ) {
        feature->generate_voxels();
        _voxels.insert( _voxels.end(), feature->get_voxels().begin(), feature->get_voxels().end() );
    }
}

std::unique_ptr<Feature> Complex::copy() {
    auto out = std::make_unique<Complex>();
    out->_settings = _settings;
    out->_parent = _parent;
    for ( auto &feature : _sub_features )
        out->_sub_features.push_back( feature->copy() );
    return out;
}