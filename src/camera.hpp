#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

class Camera {
public:
    Camera( ) {
        if ( !active_camera )
            active_camera = this;
    }

    void do_input_shit() {
        auto *window = glfwGetCurrentContext( );

        // get mouse movement
        double xpos, ypos;
        glfwGetCursorPos( window, &xpos, &ypos );
        glm::vec2 delta_mouse = glm::vec2{ xpos, ypos } - _prev_mouse_pos;
        _prev_mouse_pos = { xpos, ypos };

        // right and up vectors
        glm::vec3 dpoi = _position - _point_of_intereset;
        glm::vec3 right = glm::normalize(glm::cross( dpoi, glm::vec3{0, 1, 0} ));
        glm::vec3 up = glm::normalize(glm::cross( right, dpoi ));

        // orbit view
        if ( glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_PRESS ) {
            float length = glm::length( dpoi );
            _position += (right*delta_mouse.x + up*delta_mouse.y) * _orbit_speed;
            _position = _point_of_intereset + glm::normalize( _position-_point_of_intereset )*length;
        }
        // zoom
        if ( glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_MIDDLE ) == GLFW_PRESS ) {
            glm::vec3 forward = glm::normalize( glm::cross( up, right ) );
            _position += forward * delta_mouse.y * _zoom_speed;
        }
        // pan poi
        if ( glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_LEFT ) == GLFW_PRESS ) {
            _point_of_intereset += (right*delta_mouse.x + up*delta_mouse.y) * _pan_speed;
            _position += (right*delta_mouse.x + up*delta_mouse.y) * _pan_speed;
        }

        // update view matrix
        _view = glm::lookAt(
            _position,
            _point_of_intereset,
            up
        );
    }

    glm::mat4 getMVP(glm::mat4 model) {
        return _projection * _view * model;
    }

    void resize( int width, int height ) {
        glViewport( 0, 0, width, height );
        _projection = glm::perspective(
            glm::radians(_FoV),
            (float)width/height,
            0.1f,
            250.0f
        );
    }

    static void resize_callback( GLFWwindow * window, int width, int height ) {
        Camera::active_camera->resize( width, height );
    }

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

Camera * Camera::active_camera;