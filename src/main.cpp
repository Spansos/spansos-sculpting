#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <functional>
#include <iostream>

#include "graphics/init.hpp"
#include "graphics/load_shader.hpp"
#include "camera.hpp"
#include "features/complex.hpp"
#include "features/cylinder.hpp"


int main()
{
    auto window = init().value();

    Camera camera;
    glfwSetFramebufferSizeCallback(
        window,
        Camera::resize_callback
    );
    camera.resize(1024, 768);
    
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

    Complex root;
    root.select();
    root.generate();

    // set vertex attribs
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    root.set_vertex_attributes( buffers[0], buffers[1], buffers[2], 0, 1, 2 );

    // imgui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui_ImplGlfw_InitForOpenGL( window, true );
    ImGui_ImplOpenGL3_Init( );

    // last settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LESS);
    glEnable(GL_CULL_FACE);
    glClearColor( .2f, .4f, .7f, .0f );
    // int framec = 0;
    std::unique_ptr<Feature> clipboard = nullptr;
    do{
        glfwPollEvents( );

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // framec++;
        // if ( framec >= 60 ) {
        //     feature.radius -= .1;
        //     std::cout << feature.radius << std::endl;
        //     feature.generate();
        //     framec %= 60;
        // }
        camera.do_input_shit();
        
        // render
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        // render voxels
        glm::mat4 mvp_mat = camera.getMVP();
        glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp_mat[0][0]);
        root.set_buffers( buffers[0], buffers[1], buffers[2] );
        glDrawArrays( GL_TRIANGLES, 0, root.get_vertex_count() );
        // render ui
        ImGui::Begin( "Features", nullptr, ImGuiWindowFlags_MenuBar );
        Feature * selected = root.get_selected();
        if (ImGui::BeginMenuBar( )) {
            // add feature
            if ( ImGui::BeginMenu("Add feature") ) {
                if (ImGui::MenuItem( "Complex" ) && selected)
                    selected->add_feature( std::make_unique<Complex>() );
                if (ImGui::MenuItem( "Cylinder" ) && selected)
                    selected->add_feature( std::make_unique<Cylinder>(16, 16) );
                ImGui::EndMenu( );
            }
            // cut
            if (ImGui::MenuItem( "Cut" ) && selected) {
                clipboard = selected->copy();
                Feature * parent = selected->get_parent();
                if ( parent ) {
                    parent->remove_feature(selected);
                    selected = nullptr;
                }
            }
            // copy
            if (ImGui::MenuItem( "Copy" ) && selected) {
                clipboard = selected->copy();
            }
            // paste
            if (ImGui::MenuItem( "Paste" ) && selected && clipboard)
                selected->add_feature( clipboard->copy() );
            // delete
            if (ImGui::MenuItem( "Delete" ) && selected) {
                Feature * parent = selected->get_parent();
                if ( parent ) {
                    parent->remove_feature(selected);
                    selected = nullptr;
                }
            }

            ImGui::EndMenuBar( );
        }
        ImGui::BeginChild( "Feature tree", ImVec2(0,0), ImGuiChildFlags_ResizeY|ImGuiChildFlags_Border );
        root.render_tree();
        ImGui::EndChild();
        if ( selected ) {
            ImGui::BeginChild( "Feature settings", ImVec2(0,0), ImGuiChildFlags_AutoResizeY|ImGuiChildFlags_Border );
            selected->render_settings();
            ImGui::EndChild();
        }
        ImGui::End( );
        ImGui::Render( );
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

        glfwSwapBuffers(window);
    }
    while(
        glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS
        &&
        !glfwWindowShouldClose(window)
    );

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
	glDeleteBuffers(3, buffers);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

	glfwTerminate();
  
    return 0;
}