#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "graphics/window.hpp"
#include "graphics/load_shader.hpp"
#include "graphics/camera.hpp"
#include "graphics/renderer.hpp"
#include "graphics/mesh.hpp"

#include "features/complex.hpp"
#include "features/cylinder.hpp"

#include <iostream>

int main() {
    Window window{ {1024, 768}, "Spansos Voxel Sculpting" };

    Camera camera{&window};
    camera.resized( &window, glm::ivec2{1024, 768} );

    Renderer renderer{ "resources/fragment.glsl", "resources/vertex.glsl" };

    Complex root;
    root.select();
    root.generate_voxels();

    // imgui setup
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // ImGuiIO& io = ImGui::GetIO();
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui_ImplGlfw_InitForOpenGL( window.raw(), true );
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
        renderer.set_mvp( camera.getMVP() );
        
        window.clear( .4, .5, .6 );
        renderer.draw( window, Mesh{ root.get_voxels() } );
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
        ImGui::PushID("Feature Tree");
        root.render_tree();
        ImGui::PopID();
        ImGui::EndChild();
        if ( selected ) {
            ImGui::BeginChild( "Feature settings", ImVec2(0,0), ImGuiChildFlags_AutoResizeY|ImGuiChildFlags_Border );
            selected->render_settings();
            ImGui::EndChild();
        }
        ImGui::End( );
        ImGui::Render( );
        ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

        window.update();
    }
    while(
        glfwGetKey(window.raw(), GLFW_KEY_ESCAPE ) != GLFW_PRESS
        &&
        !window.should_close()
    );

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  
    return 0;
}