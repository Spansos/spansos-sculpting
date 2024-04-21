#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "feature.hpp"
#include <algorithm>

class Cylinder : public Feature {
public:
    Cylinder( int length, float radius ) :
        Feature( "Cylinder" )
    {
        _settings["radius"] = radius;
        _settings["length"] = length;
    }
    std::vector< glm::ivec3 > get_voxels( std::vector<glm::ivec3> voxels = {} ) override {
        float radius = std::get<float>(_settings.at("radius"));
        int length = std::get<int>(_settings.at("length"));

        std::vector<glm::ivec3> new_voxels;

        float x = radius;
        int y = 0;
        while ( y <= x ) {
            new_voxels.push_back( {x, y, 0} );
            glm::vec3 mid_next = ( glm::vec3{x,y+1,0} + glm::vec3{x-1,y+1,0} ) / 2.0f;
            if (mid_next.x*mid_next.x + mid_next.y*mid_next.y > radius*radius )
                x--;
            y++;
        }
        
        for ( int i=new_voxels.size()-1; i>=0; i-- )
            new_voxels.push_back( {new_voxels[i].y, new_voxels[i].x, 0} );
        for ( int i=new_voxels.size()-2; i>=0; i-- )
            new_voxels.push_back( {-new_voxels[i].x, new_voxels[i].y, 0} );
        for ( int i=new_voxels.size()-2; i>=1; i-- )
            new_voxels.push_back( {new_voxels[i].x, -new_voxels[i].y, 0} );
        
        int voxel_c = new_voxels.size();
        for ( int j=0; j<length; j++ )
            for ( int i=0; i<voxel_c; i++ )
                new_voxels.push_back( {new_voxels[i].x, new_voxels[i].y, j} );
        

        // for ( auto voxel : voxels ) {
        //     std::cout << std::count( voxels.begin(), voxels.end(), voxel ) << std::endl;
        // }

        voxels.insert( voxels.end(), new_voxels.begin(), new_voxels.end() );
        return voxels;
    }
    std::unique_ptr<Feature> copy() override {
        auto out = std::make_unique<Cylinder>( 0, 0 );
        out->_settings = _settings;
        out->_parent = _parent;
        // out->_is_selected = _is_selected;
        for ( auto &feature : _sub_features )
            out->_sub_features.push_back( feature->copy() );
        return out;
    }
};