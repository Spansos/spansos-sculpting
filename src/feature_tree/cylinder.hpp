#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "feature.hpp"
#include <algorithm>

class Cylinder : public Feature {
public:
    Cylinder( int length, float radius ) :
        length(length),
        radius(radius)
    { }
    std::vector< glm::ivec3 > get_voxels( std::vector<glm::ivec3> voxels = {} ) override {
        float x = radius;
        int y = 0;
        while ( y <= x ) {
            voxels.push_back( {x, y, 0} );
            glm::vec3 mid_next = ( glm::vec3{x,y+1,0} + glm::vec3{x-1,y+1,0} ) / 2.0f;
            if (mid_next.x*mid_next.x + mid_next.y*mid_next.y > radius*radius )
                x--;
            y++;
        }
        
        for ( int i=voxels.size()-1; i>=0; i-- )
            voxels.push_back( {voxels[i].y, voxels[i].x, 0} );
        for ( int i=voxels.size()-2; i>=0; i-- )
            voxels.push_back( {-voxels[i].x, voxels[i].y, 0} );
        for ( int i=voxels.size()-2; i>=1; i-- )
            voxels.push_back( {voxels[i].x, -voxels[i].y, 0} );
        
        int voxel_c = voxels.size();
        for ( int j=0; j<length; j++ )
            for ( int i=0; i<voxel_c; i++ )
                voxels.push_back( {voxels[i].x, voxels[i].y, j} );
        

        // for ( auto voxel : voxels ) {
        //     std::cout << std::count( voxels.begin(), voxels.end(), voxel ) << std::endl;
        // }

        return voxels;
    }
private:
    int length;
    float radius;
};