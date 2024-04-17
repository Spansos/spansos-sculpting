#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "graphics/init.hpp"
#include "graphics/load_shader.hpp"
#include "camera.hpp"
#include "feature_tree/complex.hpp"
#include "feature_tree/cylinder.hpp"
#include <functional>

#include <iostream>


int main()
{
    auto window = init().value();
    Camera camera;
    glfwSetFramebufferSizeCallback(
        window,
        Camera::resize_callback
    );
    // vertex array
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // buffers
    GLuint buffers[3];
    glGenBuffers(3, buffers);

    // shaders
    GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");
    glUseProgram(programID);
    // uniform handles
    GLuint mvp_id = glGetUniformLocation( programID, "MVP" );


    Complex feature;
    feature.add_feature( std::make_unique<Cylinder>(12, 6) );
    feature.generate();

    // set vertex attribs
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    feature.set_vertex_attributes( buffers[0], buffers[1], buffers[2], 0, 1, 2 );

    // last settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LESS);
    glEnable(GL_CULL_FACE);
    glClearColor( .2f, .4f, .7f, .0f );
    // int framec = 0;
    do{
        // framec++;
        // if ( framec >= 60 ) {
        //     feature.radius -= .1;
        //     std::cout << feature.radius << std::endl;
        //     feature.generate();
        //     framec %= 60;
        // }
        camera.do_input_shit();
        // Clear the screen.
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // uniforms
        glm::mat4 mvp_mat = camera.getMVP(feature.matrix);
        glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp_mat[0][0]);
        // buffers
        feature.set_buffers( buffers[0], buffers[1], buffers[2] );
        
        glDrawArrays( GL_TRIANGLES, 0, feature.get_vertex_count() );
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    while(
        glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
        &&
        glfwWindowShouldClose(window) == 0
    );

    // Cleanup
	glDeleteBuffers(3, buffers);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

	glfwTerminate();
  
    return 0;
}