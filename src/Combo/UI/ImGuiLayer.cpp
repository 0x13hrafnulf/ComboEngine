
#include "ImGuiLayer.h"
#include "imgui.h"
#include "examples/imgui_impl_sdl.h"
#include "examples/imgui_impl_opengl3.h"



#include "Engine.h"

namespace Combo
{
    
    ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
    {
        
    }

    void ImGuiLayer::Attach() 
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Engine& app = Engine::Get();
        m_Window = static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow());
        m_Context =  SDL_GL_GetCurrentContext();

        // Setup Platform/Renderer bindings
        ImGui_ImplSDL2_InitForOpenGL(m_Window, m_Context);
        ImGui_ImplOpenGL3_Init("#version 450");
    }
    void ImGuiLayer::Detach() 
    {
        // Cleanup  
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::ImGuiRender()
    {
        static bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);
    }
    
    void ImGuiLayer::Start()
    {
         // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(m_Window);
        ImGui::NewFrame();
    }
    void ImGuiLayer::Stop()
    {
        
        ImGuiIO& io = ImGui::GetIO();
        Engine& app = Engine::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetWindowWidth(), (float)app.GetWindow().GetWindowHeight());

         // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(m_Window);
    }


} 
