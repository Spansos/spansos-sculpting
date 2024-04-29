#include "graphics/mesh.hpp"

Mesh::Mesh( const std::vector<glm::ivec3> &voxels ) {

    for ( auto i : voxels ) {
        positions.push_back( i );
        normals.push_back( {-1,0,0 } );
        positions.push_back( i+glm::ivec3{0,0,1} );
        normals.push_back( {-1,0,0 } );
        positions.push_back( i+glm::ivec3{0,1,0} );
        normals.push_back( {-1,0,0 } );
        
        positions.push_back( i+glm::ivec3(0,1,0) );
        normals.push_back( {-1,0,0 } );
        positions.push_back( i+glm::ivec3{0,0,1} );
        normals.push_back( {-1,0,0 } );
        positions.push_back( i+glm::ivec3{0,1,1} );
        normals.push_back( {-1,0,0 } );

        positions.push_back( i );
        normals.push_back( {0,-1,0 } );
        positions.push_back( i+glm::ivec3{1,0,0} );
        normals.push_back( {0,-1,0 } );
        positions.push_back( i+glm::ivec3{0,0,1} );
        normals.push_back( {0,-1,0 } );

        positions.push_back( i+glm::ivec3{0,0,1} );
        normals.push_back( {0,-1,0 } );
        positions.push_back( i+glm::ivec3{1,0,0} );
        normals.push_back( {0,-1,0 } );
        positions.push_back( i+glm::ivec3{1,0,1} );
        normals.push_back( {0,-1,0 } );

        positions.push_back( i );
        normals.push_back( { 0,0,-1 } );
        positions.push_back( i+glm::ivec3{0,1,0} );
        normals.push_back( { 0,0,-1 } );
        positions.push_back( i+glm::ivec3{1,0,0} );
        normals.push_back( { 0,0,-1 } );

        positions.push_back( i+glm::ivec3{1,0,0} );
        normals.push_back( { 0,0,-1 } );
        positions.push_back( i+glm::ivec3{0,1,0} );
        normals.push_back( { 0,0,-1 } );
        positions.push_back( i+glm::ivec3{1,1,0} );
        normals.push_back( { 0,0,-1 } );
        
        positions.push_back( i+glm::ivec3{1,0,0} );
        normals.push_back( {1,0,0 } );
        positions.push_back( i+glm::ivec3{1,1,0} );
        normals.push_back( {1,0,0 } );
        positions.push_back( i+glm::ivec3{1,0,1} );
        normals.push_back( {1,0,0 } );
        
        positions.push_back( i+glm::ivec3{1,0,1} );
        normals.push_back( {1,0,0 } );
        positions.push_back( i+glm::ivec3(1,1,0) );
        normals.push_back( {1,0,0 } );
        positions.push_back( i+glm::ivec3{1,1,1} );
        normals.push_back( {1,0,0 } );

        positions.push_back( i+glm::ivec3{0,1,0} );
        normals.push_back( {0,1,0} );
        positions.push_back( i+glm::ivec3{0,1,1} );
        normals.push_back( {0,1,0} );
        positions.push_back( i+glm::ivec3{1,1,0} );
        normals.push_back( {0,1,0} );

        positions.push_back( i+glm::ivec3{1,1,0} );
        normals.push_back( {0,1,0 } );
        positions.push_back( i+glm::ivec3{0,1,1} );
        normals.push_back( {0,1,0 } );
        positions.push_back( i+glm::ivec3{1,1,1} );
        normals.push_back( {0,1,0 } );

        positions.push_back( i+glm::ivec3{0,0,1} );
        normals.push_back( {0,0,1} );
        positions.push_back( i+glm::ivec3{1,0,1} );
        normals.push_back( {0,0,1} );
        positions.push_back( i+glm::ivec3{0,1,1} );
        normals.push_back( {0,0,1} );

        positions.push_back( i+glm::ivec3{0,1,1} );
        normals.push_back( {0,0,1} );
        positions.push_back( i+glm::ivec3{1,0,1} );
        normals.push_back( {0,0,1} );
        positions.push_back( i+glm::ivec3{1,1,1} );
        normals.push_back( {0,0,1} );
        
        for ( int i=0; i<36; i++ )
            colors.push_back( { 1, 0, 0 } );
    }
}