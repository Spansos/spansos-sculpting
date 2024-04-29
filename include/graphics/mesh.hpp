#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <bitset>

struct Mesh {
    Mesh( const std::vector<glm::ivec3> &voxels );
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> colors;
};