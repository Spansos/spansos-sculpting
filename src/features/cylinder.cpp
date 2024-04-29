#include "features/cylinder.hpp"

Cylinder::Cylinder( int length, float radius ) :
    Feature( "Cylinder" )
{
    _settings["radius"] = radius;
    _settings["length"] = length;
}

void Cylinder::generate_voxels( ) {
    _voxels.clear();

    float radius = std::get<float>(_settings.at("radius"));
    int length = std::get<int>(_settings.at("length"));

    float x = radius;
    int y = 0;
    while ( y <= x ) {
        _voxels.push_back( {x, y, 0} );
        glm::vec3 mid_next = ( glm::vec3{x,y+1,0} + glm::vec3{x-1,y+1,0} ) / 2.0f;
        if (mid_next.x*mid_next.x + mid_next.y*mid_next.y > radius*radius )
            x--;
        y++;
    }
    
    for ( int i=_voxels.size()-1; i>=0; i-- )
        _voxels.push_back( {_voxels[i].y, _voxels[i].x, 0} );
    for ( int i=_voxels.size()-2; i>=0; i-- )
        _voxels.push_back( {-_voxels[i].x, _voxels[i].y, 0} );
    for ( int i=_voxels.size()-2; i>=1; i-- )
        _voxels.push_back( {_voxels[i].x, -_voxels[i].y, 0} );
    
    int voxel_c = _voxels.size();
    for ( int j=0; j<length; j++ )
        for ( int i=0; i<voxel_c; i++ )
            _voxels.push_back( {_voxels[i].x, _voxels[i].y, j} );
}

std::unique_ptr<Feature> Cylinder::copy() {
    auto out = std::make_unique<Cylinder>( 0, 0 );
    out->_settings = _settings;
    out->_parent = _parent;
    // out->_is_selected = _is_selected;
    for ( auto &feature : _sub_features )
        out->_sub_features.push_back( feature->copy() );
    return out;
}