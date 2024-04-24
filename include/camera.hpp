#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

class Camera {
public:
    Camera( );
    void do_input_shit();
    glm::mat4 getMVP();
    void resize( int width, int height );
    static void resize_callback( GLFWwindow * window, int width, int height );

private:
    static Camera * active_camera;
    glm::vec3 _point_of_intereset = {0.0f, 0.0f, 0.0f};
    glm::vec3 _position = {30.0f,0.0f,0.0f};
    glm::vec2 _prev_mouse_pos;
    float _FoV = 45.0f;
    float _orbit_speed = .25f;
    float _pan_speed = .1f;
    float _zoom_speed = .5f;
    glm::mat4 _projection;
    glm::mat4 _view;
};