#include "feature.hpp"


void Feature::set_buffers( GLuint position_buffer, GLuint normal_buffer, GLuint color_buffer ) {
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glBufferData(GL_ARRAY_BUFFER, _positions.size() * sizeof(glm::vec3), _positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glBufferData(GL_ARRAY_BUFFER, _normals.size() * sizeof(glm::vec3), _normals.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, _colors.size() * sizeof(glm::vec3), _colors.data(), GL_STATIC_DRAW);
}

void Feature::set_vertex_attributes(
    GLuint position_buffer, GLuint normal_buffer, GLuint color_buffer,
    GLuint position_index, GLuint normal_index, GLuint color_index
) {
    glBindBuffer(GL_ARRAY_BUFFER, position_buffer);
    glVertexAttribPointer( position_index, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glVertexAttribPointer( normal_index, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glVertexAttribPointer( color_index, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
}

GLsizei Feature::get_vertex_count( ) {
    return _positions.size();
}

void Feature::generate_vertices( std::vector< glm::ivec3 > voxels ) {
    _positions.clear();
    _normals.clear();
    _colors.clear();

    for ( auto i : voxels ) {
        _positions.push_back( i );
        _normals.push_back( {-1,0,0 } );
        _positions.push_back( i+glm::ivec3{0,0,1} );
        _normals.push_back( {-1,0,0 } );
        _positions.push_back( i+glm::ivec3{0,1,0} );
        _normals.push_back( {-1,0,0 } );
        
        _positions.push_back( i+glm::ivec3(0,1,0) );
        _normals.push_back( {-1,0,0 } );
        _positions.push_back( i+glm::ivec3{0,0,1} );
        _normals.push_back( {-1,0,0 } );
        _positions.push_back( i+glm::ivec3{0,1,1} );
        _normals.push_back( {-1,0,0 } );

        _positions.push_back( i );
        _normals.push_back( {0,-1,0 } );
        _positions.push_back( i+glm::ivec3{1,0,0} );
        _normals.push_back( {0,-1,0 } );
        _positions.push_back( i+glm::ivec3{0,0,1} );
        _normals.push_back( {0,-1,0 } );

        _positions.push_back( i+glm::ivec3{0,0,1} );
        _normals.push_back( {0,-1,0 } );
        _positions.push_back( i+glm::ivec3{1,0,0} );
        _normals.push_back( {0,-1,0 } );
        _positions.push_back( i+glm::ivec3{1,0,1} );
        _normals.push_back( {0,-1,0 } );

        _positions.push_back( i );
        _normals.push_back( { 0,0,-1 } );
        _positions.push_back( i+glm::ivec3{0,1,0} );
        _normals.push_back( { 0,0,-1 } );
        _positions.push_back( i+glm::ivec3{1,0,0} );
        _normals.push_back( { 0,0,-1 } );

        _positions.push_back( i+glm::ivec3{1,0,0} );
        _normals.push_back( { 0,0,-1 } );
        _positions.push_back( i+glm::ivec3{0,1,0} );
        _normals.push_back( { 0,0,-1 } );
        _positions.push_back( i+glm::ivec3{1,1,0} );
        _normals.push_back( { 0,0,-1 } );
        
        _positions.push_back( i+glm::ivec3{1,0,0} );
        _normals.push_back( {1,0,0 } );
        _positions.push_back( i+glm::ivec3{1,1,0} );
        _normals.push_back( {1,0,0 } );
        _positions.push_back( i+glm::ivec3{1,0,1} );
        _normals.push_back( {1,0,0 } );
        
        _positions.push_back( i+glm::ivec3{1,0,1} );
        _normals.push_back( {1,0,0 } );
        _positions.push_back( i+glm::ivec3(1,1,0) );
        _normals.push_back( {1,0,0 } );
        _positions.push_back( i+glm::ivec3{1,1,1} );
        _normals.push_back( {1,0,0 } );

        _positions.push_back( i+glm::ivec3{0,1,0} );
        _normals.push_back( {0,1,0} );
        _positions.push_back( i+glm::ivec3{0,1,1} );
        _normals.push_back( {0,1,0} );
        _positions.push_back( i+glm::ivec3{1,1,0} );
        _normals.push_back( {0,1,0} );

        _positions.push_back( i+glm::ivec3{1,1,0} );
        _normals.push_back( {0,1,0 } );
        _positions.push_back( i+glm::ivec3{0,1,1} );
        _normals.push_back( {0,1,0 } );
        _positions.push_back( i+glm::ivec3{1,1,1} );
        _normals.push_back( {0,1,0 } );

        _positions.push_back( i+glm::ivec3{0,0,1} );
        _normals.push_back( {0,0,1} );
        _positions.push_back( i+glm::ivec3{1,0,1} );
        _normals.push_back( {0,0,1} );
        _positions.push_back( i+glm::ivec3{0,1,1} );
        _normals.push_back( {0,0,1} );

        _positions.push_back( i+glm::ivec3{0,1,1} );
        _normals.push_back( {0,0,1} );
        _positions.push_back( i+glm::ivec3{1,0,1} );
        _normals.push_back( {0,0,1} );
        _positions.push_back( i+glm::ivec3{1,1,1} );
        _normals.push_back( {0,0,1} );
        
        for ( int i=0; i<36; i++ )
            _colors.push_back( { 1, 0, 0 } );
    }
}