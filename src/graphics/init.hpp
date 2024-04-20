#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <optional>

#include <iostream>

std::optional<GLFWwindow *> init() {
    glewExperimental = true; // Needed for core profile
    if( !glfwInit() ) {
        // std::cerr << "Failed to initialize GLFW\n";
        return {};
    }

    // make window
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // We want OpenGL 4.0
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We want core functionality (instead of older something-something (which is higher level))

    GLFWwindow* window = glfwCreateWindow( 1024, 768, "Spansos Voxel Sculpting", NULL, NULL);
    if( !window ) {
        std::cout << "window no window" << std::endl;
        // std::cerr << "Failed to open GLFW window.\n";
        glfwTerminate();
        return {};
    }

    // Initialize GLEW
    glfwMakeContextCurrent(window);
    glewExperimental=true;
    if (glewInit() != GLEW_OK) {
        // std::cerr << "Failed to initialize GLEW\n";
        return {};
    }
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}